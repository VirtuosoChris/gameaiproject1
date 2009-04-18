#include "ktcGame.h"
#include "player.h"
//todo code
//entities[1]->setPathList(this->generateDefenseArc(0,2*3.14, 120,8));

//#define COVER_OBJECT_GENERATOR

using namespace irr;
using namespace irr::scene;
using namespace irr::core;

using std::cout;

static const float PREDATOR_SPEED = .15f;
static const float PREY_SPEED = .3f;

//initializing the playerList
std::vector<GamePlayer *> ktcGame::playerList;

extern std::vector<irr::scene::ISceneNode*> specialWalls;

//plan for guard can behavior
//a* to the can
//do while(time)
//  generate path from a random one of the 8 compass directions to the one 180 degrees away --
//	that is, nodes in a circular arc of constant radius
//  go to center
//end while

std::list<irr::core::vector3df> ktcGame::generateDefenseArc(double startAngle, double endAngle, double radius, double nodeCount){
	std::list<irr::core::vector3df> result(nodeCount);

	const irr::core::vector3df& canPos = this->can.getSceneNode()->getPosition();

	double increment = (startAngle - endAngle) / nodeCount;

	for(int i = 0; i < nodeCount; i++){
		double currentAngle = endAngle + increment*i;
		result.push_back( 
			vector3df(0, -canPos.Y + this->spawnPointList[0].Y,0)+radius*vector3df( cos(currentAngle)  ,0,sin(currentAngle) ) + canPos);
		//irr::scene::ISceneNode* a = this->smgr->addSphereSceneNode(5);
		//a->setPosition(result.back());
	}
	
return result;
}



//#define NODE_MESH_GENERATOR //is the program in node mesh generation mode
//-442,351,-863
//-528.744751 0.024357 102.937782
ktcGame::ktcGame(IrrlichtDevice *device, irr::scene::ITriangleSelector* selector):can (device), graph (device, "NODE_LIST.txt","ADJACENCY_LIST.txt","EXCLUDE.txt"), 
agent2 (Model("../media/chuckie.MD2","../media/Chuckie.pcx", device), irr::core::vector3df(0,0,0), 300000, 10000, PREY, core::vector3df(-528.744751, 0.024357, 102.937782), device->getSceneManager(), &graph),
plyr(device, irr::core::vector3df(0,0,0), 300000, 0, PREY)
{
	
graph.selector = selector; 
graph.toggleDebugOutput(false);
	dMode = NONE;
	
	//Instantiate the Irrlicht Engine Device
	this->device = device;

	//Game now has their own timer
	round_time.setTime(500000);

	plyr.setCameraSpeed(PREY_SPEED);
	playerList.push_back(&plyr);
	
	//Instantiate the Irrlicht Engine Scene Manager
	smgr = device->getSceneManager();

	//Instantiate the GameHUD Device
	this->display = gameHUD::getInstance();

	CHUCKIE = agent2.getModel();



	
	FILE* fp = fopen("SPAWN_POINTS.txt", "r");
	if(fp){
		float a[3];
		while(!feof(fp)){
			fscanf(fp, "%f %f %f\n", a, &a[1], &a[2]);
			this->spawnPointList.push_back(irr::core::vector3df(a[0],a[1],a[2]));

			//irr::scene::ISceneNode* b;
			//b = smgr->addSphereSceneNode(1);
			//b->setMaterialFlag(irr::video::EMF_LIGHTING, true);
			//b->setPosition(irr::core::vector3df(a[0], a[1], a[2]));
		}
	
		fclose(fp);
}

fp = fopen("COVER_OBJECTS.txt", "r");
if(fp){
float a[3];
while(!feof(fp)){
	fscanf(fp, "%f %f %f\n", a, &a[1], &a[2]);
	this->coverObjectList.push_back(new coverObject(vector3df(a[0], a[1], a[2]), device));
	
	
}
fclose(fp);
}

else cout << "Bad pointer.\n";

	//can=(device);
	//gun = gunEntity(device, camera);
	
/****************LOAD IN MODELS*******************************/
 
 CARTMAN  = createModel("../media/ERIC.MD2","../media/ERIC.pcx",device, 1.0f);
 CYBERDEMON = createModel("../media/cyber.md2","../media/cyber.pcx",device,3.0f);


//agent2.setPosition(this->spawnPointList[2]);
//agent2.getSceneNode()->setPosition(this->spawnPointList[2]);



//Agent* agent3 = new Agent(CARTMAN, this->spawnPointList[2], device->getSceneManager(), PREY, &graph);

//agent3->setPosition(this->spawnPointList[2]);
//agent3->GetFSM()->ChangeState(Patrol::GetInstance());
//agent3->createCollisionAnimator(selector, smgr);
//entities.push_back(agent3);


Agent::setAgentList(&entities);
Agent::setCoverObjectList(&coverObjectList);

agent2.setIt(&plyr);
agent2.setSpotted(&plyr);

agent2.getSceneNode()->setPosition(spawnPointList[2]);
agent2.setPosition(spawnPointList[2]);

agent2.createCollisionAnimator(selector, smgr);
agent2.GetFSM()->ChangeState(Hide::GetInstance());

 entities.push_back(&agent2);
 playerList.push_back(&agent2);



 //camera = 
//	 smgr->addCameraSceneNodeFPS();// addCameraSceneNodeFPS();

 //CPTODO: REPLACE HARD CODED CONSTANT WITH SOMETHING BETTER
 //camera->setPosition(core::vector3df(-280,288,-830));

plyr.setSpawnPoint(spawnPointList[0]);
plyr.getSceneNode()->setPosition( spawnPointList[0] );

//agent2.createPatrolRoute(&graph);

scene::ISceneNodeAnimator *nodeAnimator = 
	smgr->createCollisionResponseAnimator(selector,//geometry for collision 
	plyr.getSceneNode(), //scene node to apply collision to/	
	CHUCKIE.mesh->getBoundingBox().getExtent(),
	core::vector3df(0,-10,0),//gravity 
	CHUCKIE.mesh->getBoundingBox().getCenter()//core::vector3df(0,30,0)
	); //collision volume position
if(!nodeAnimator){throw new std::string("Error creating node animator");}
plyr.getSceneNode()->addAnimator(nodeAnimator);
 nodeAnimator->drop();


 plyr.getSceneNode()->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(((irr::scene::IAnimatedMeshSceneNode*)agent2.getSceneNode())),plyr.getSceneNode(),((irr::scene::IAnimatedMeshSceneNode*)agent2.getSceneNode())->getBoundingBox().getExtent(), vector3df(0,0,0),((irr::scene::IAnimatedMeshSceneNode*)agent2.getSceneNode())->getBoundingBox().getCenter())
					);


//make the camera collide with cover
for(int i = 0; i < this->coverObjectList.size(); i++){

	
	plyr.getSceneNode()->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(
					coverObjectList[i]->getSceneNode()),
					plyr.getSceneNode(),CHUCKIE.mesh->getBoundingBox().getExtent(), 
					vector3df(0,0,0), 
					CHUCKIE.mesh->getBoundingBox().getCenter()
					)
					);

 agent2.getSceneNode()->addAnimator(
	 	smgr->createCollisionResponseAnimator(
	smgr->createTriangleSelectorFromBoundingBox(coverObjectList[i]->getSceneNode()),agent2.getSceneNode(),CHUCKIE.mesh->getBoundingBox().getExtent(), vector3df(0,0,0), CHUCKIE.mesh->getBoundingBox().getCenter())
					);

}


for(int i = 0; i < specialWalls.size(); i++){

	//std::cout<<"ASdkksjd\n";
	plyr.getSceneNode()->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(
					specialWalls[i]),
					plyr.getSceneNode(),CHUCKIE.mesh->getBoundingBox().getExtent(), 
					vector3df(0,0,0), 
					CHUCKIE.mesh->getBoundingBox().getCenter()
					)
					);

 agent2.getSceneNode()->addAnimator(
	 	smgr->createCollisionResponseAnimator(
	smgr->createTriangleSelectorFromBoundingBox(specialWalls[i]),agent2.getSceneNode(),CHUCKIE.mesh->getBoundingBox().getExtent(), vector3df(0,0,0), CHUCKIE.mesh->getBoundingBox().getCenter())
					);



 scene::ISceneNodeAnimator *nodeAnimator = 
	smgr->createCollisionResponseAnimator(selector,//geometry for collision 
	specialWalls[i], //scene node to apply collision to/	
	specialWalls[i]->getBoundingBox().getExtent()
	,
	core::vector3df(0,-10,0),//gravity 
	specialWalls[i]->getBoundingBox().getCenter()//core::vector3df(0,30,0)
	); //collision volume position
if(!nodeAnimator){throw new std::string("Error creating node animator");}
specialWalls[i]->addAnimator(nodeAnimator);
 nodeAnimator->drop();

}





//Initialize Player Scoresfor(int x=0 ; x<5 ; x++)	playerScores[x] = 0;}




}






void ktcGame::update(const irr::ITimer* timer){

	//update round timer
	round_time.update(timer);

	//update HUD
	gameHUD::getInstance()->updateRoundTimer(plyr.pl_time.getMins(),
											 plyr.pl_time.getSecsSecond(),
											 plyr.pl_time.getSecsFirst());

	//if time is up, then round robin shit so that we get new predator and prey
	if(plyr.pl_time.getTime() <= 0){
		RoundRobin(playerList);
		for(int i = 0; i < playerList.size(); i++){
			(*playerList[i]).setInvTimer(5000);
			(*playerList[i]).setTimer(60000);
		}
	}

	/*
	if(agent2.getPlayerType() == PREY) 
		std::cout << "I'm an agent and i'm PREY\n";
	else std::cout << "I'm an agent and i'm a PREDATOR\n";
	
	if(plyr.getPlayerType() == PREY) 
		std::cout << "I'm a player and i'm PREY\n";
	else std::cout << "I'm a player and i'm a PREDATOR\n";
	*/


//	core::line3d<irr::f32> line;
//	line.start = plyr.getSceneNode()->getPosition();
	//line.end = //line.start +  vector3df(0,1000,0);
	
//	for(int i = 0; i < this->coverObjectList.size();i++){
//		line.end = this->coverObjectList[i]->getSceneNode()->getBoundingBox().getCenter();
//		
//		if(this->coverObjectList[i]->getSceneNode()->getBoundingBox().intersectsWithLine(line)){
//			std::cout<<"ZOMG INTERSECTED\n";
//
//			if(this->coverObjectList[i]->getSceneNode()->getBoundingBox().isEmpty()){
//				std::cout<<"WTFLOL\n";
//			}
//
//		//	this->coverObjectList[i]->getSceneNode()->getBoundingBox().
//		}
//	}



device->getVideoDriver()->beginScene(true, true, video::SColor(255,100,101,140));

smgr->drawAll();  //draw 3d objects
display->render();



		
//for(int i = 0; i < this->coverObjectList.size(); i++){
//	coverObjectList[i]->getCoverPosition(agent2.getIt());
//	}

plyr.getGun().render();

device->getVideoDriver()->endScene();//end drawing 

if(InputHandler::getInstance()->unprocessedMouseMessageLMB){


#ifdef NODE_MESH_GENERATOR
			graph.addNode(camera->getPosition());
#endif

#ifdef SPAWN_POINT_CREATOR
			this->spawnPointList.push_back(camera->getPosition());

			
			FILE *fp = fopen("SPAWN_POINTS.txt", "a");
	 
			fprintf(fp, "%f %f %f\n", this->camera->getPosition().X, this->camera->getPosition().Y, this->camera->getPosition().Z);
			
			fclose(fp);
#endif


#ifdef COVER_OBJECT_GENERATOR

			irr::scene::ISceneNode* t= smgr->addCubeSceneNode(1);
			t->setPosition(camera->getPosition());
			//irr::scene::ILightSceneNode *lightscenenode = smgr->addLightSceneNode(0, irr::core::vector3df(1.25,0,0), irr::video::SColor(255,255, 255, 255),100);
			//t->addChild(lightscenenode);
			//irr::scene::ILightSceneNode *lightscenenode2 = smgr->addLightSceneNode(0, irr::core::vector3df(0,0,-1.25), irr::video::SColor(255, 255, 255, 255),100);
			//t->addChild(lightscenenode2);
			//irr::scene::ISceneNode* a = smgr->addSphereSceneNode(1);
			//a->setPosition(irr::core::vector3df(1.1,1.1,1.1));
	//		t->addChild(a);
			t->setScale(vector3df(50,75,50));
			coverObjectList.push_back(camera->getPosition());
			t->setMaterialTexture(0, device->getVideoDriver()->getTexture("../media/crate.jpg"));
			t->setMaterialTexture(1, device->getVideoDriver()->getTexture("../media/cratebump.jpg"));
			t->setMaterialFlag(video::EMF_LIGHTING, true);
			t->setMaterialFlag(video::EMF_FOG_ENABLE, true);
			t->setMaterialType(video::EMT_LIGHTMAP_LIGHTING_M4);
		//	t->getMaterial(0).AmbientColor = video::SColor(255,25,25,25);
			//t->getMaterial(1).AmbientColor = video::SColor(255,25,25,25);
			
			
#endif

//Gun Mechanics - Make sure animation is complete
if(plyr.getGun().isReady())
{
	MessageHandler::getInstance()->postMessage(KTC_PLAYER_LEFT_MOUSE_CLICK, 0, this, &plyr.getGun(), timer);
	
	//Make sure gun has passed the firing time limitation
	if(display->getGunReady())
	{
		for(int i = 0; i < entities.size(); i++)
		{
			if(this->pointing() == entities[i]->getSceneNode())
			{
				MessageHandler::getInstance()->postMessage(KTC_KILL, 0, this, entities[i], device->getTimer());
				break;
			}
		}
	}
}


if(this->pointing() == can.getSceneNode() && (plyr.getSceneNode()->getPosition() - can.getSceneNode()->getPosition()).getLength() <= 100.0f){
	for(int i = 0; i < entities.size(); i++){
	
		MessageHandler::getInstance()->postMessage(KTC_REVIVE, 0, this, entities[i], device->getTimer());
	}
}


			InputHandler::getInstance()->unprocessedMouseMessageLMB = false;
		}



	if(InputHandler::getInstance()->unprocessedMouseMessageRMB){
		//graph.output();


#ifdef COVER_OBJECT_GENERATOR
 FILE *fp = fopen("COVER_OBJECTS.txt", "w");
 for(int i = 0; i < this->coverObjectList.size(); i++){
		 fprintf(fp, "%f %f %f\n", coverObjectList[i].X, coverObjectList[i].Y, coverObjectList[i].Z);
	 }
	fclose(fp);
#endif


		InputHandler::getInstance()->unprocessedMouseMessageRMB = false;
	}



	//Toggle the render output of the Debug visible objects
	if(InputHandler::getInstance()->isTKeyPressed()){
		graph.toggleDebugOutput(!graph.isDebugOutput());
	}

	//Toggle the render output of the GUI scoring mechanism
	//if(InputHandler::getInstance()->isTabKeyPressed()){
	//	graph.toggleScoreOutput(!graph.isScoreOutput());
	//}

	can.update(timer);
	plyr.update(timer);

	


#ifndef NODE_MESH_GENERATOR
static mapGraph* mintree = graph.minimumSpanningTree(0);
//graph.minimumSpanningTree(0)->render(device->getVideoDriver());

switch(this->dMode){
case NONE:break;
case FULLGRAPH: graph.render(device->getVideoDriver());break;
case MINSPANNINGTREE: mintree->render(device->getVideoDriver());break;
}


for(int i = 0; i < (int)entities.size();i++){
			if(entities[i]){
				entities[i]->update(timer);
				
				if(graph.isDebugOutput()){
			//	entities[i]->drawPieSlices(device->getVideoDriver());
				}
			}
		}


#endif

	//update all entities

	//agent2.walk(agent2.followPath(timer));
	//agent2.walk(agent2.seek(agent2.getCurrentSeekTarget()) + agent2.wallAvoidance());
		
	//agent2.walk(2*agent2.avoid(&plyr)+ 10*agent2.wallAvoidance());

	//agent2.walk(agent2.pursue(&plyr));//);+ agent2.wallAvoidance());
	//agent2.walk(2*agent2.seek(plyr.getPosition())+ agent2.wallAvoidance());
	
	///gun.gun->setPosition(camera->getPosition());	
	//gun.gun->setRotation(camera->getRotation() + vector3df(0,270,0));

	//scene::ISceneNode* SceneNodeSeen;
	//SceneNodeSeen = ktcGame::pointing();
	//if(SceneNodeSeen == agent2.getSceneNode()){
	//	std::cout << "I'm looking at Chuckie;\n";
	//}

	


}

void ktcGame::RoundRobin(std::vector<GamePlayer *> plst){
	for(int i = 0; i < plst.size(); i++){
		if( ( (*plst[i]).getPlayerType() == PREDATOR) && (i+1 != plst.size()) ){
			(*plst[i]).setPlayerType(PREY);
			//change state to init of pred and prey
			(*plst[i+1]).setPlayerType(PREDATOR);
			break;
		}

		else if( ((*plst[i]).getPlayerType() == PREDATOR) && ( (i+1) == plst.size() ) ){
			//change state to init of pred and prey
			(*plst[i]).setPlayerType(PREY);
			(*plst[i% (plst.size() - 1) ]).setPlayerType(PREDATOR);
			break;
		}
	}
}

bool ktcGame::processMessage(const Message* m){
	return true;
}

ISceneNode* ktcGame::pointing(){
	ISceneNode* selectedSceneNode;
	ISceneNode* returnedSceneNode;

	//get the scene node that the camera is looking at
	selectedSceneNode = smgr->getSceneCollisionManager()->getSceneNodeFromCameraBB((irr::scene::ICameraSceneNode*)plyr.getSceneNode());

	returnedSceneNode = ktcGame::GetCan(selectedSceneNode);
	if(returnedSceneNode){
		//std::cout << "I'm looking at the can.\n";
		return returnedSceneNode;
	}

	returnedSceneNode = ktcGame::GetAgent(selectedSceneNode);
	if(returnedSceneNode){
		//std::cout << "I'm looking at an agent.\n";
		return returnedSceneNode;
	}

	return 0;

	
}

ISceneNode* ktcGame::GetCan(ISceneNode * node){
	if(node == can.getSceneNode())
		return node;
	else 
		return 0;
}


ISceneNode* ktcGame::GetAgent(ISceneNode * node){
	for(int i = 0; i < entities.size(); i++){
		if(node == entities[i]->getSceneNode())
			return node;
	}

	return 0;

}

ktcGame::~ktcGame(){


}