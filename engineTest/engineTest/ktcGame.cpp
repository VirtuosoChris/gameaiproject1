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

	//set up state machine
	GameStateMachine = new StateMachine<ktcGame>(*this);

	plyr.setCameraSpeed(PREY_SPEED);
	playerList.push_back(&plyr);
	
	//Instantiate the Irrlicht Engine Scene Manager
	smgr = device->getSceneManager();

	//Instantiate the GameHUD Device
	this->display = gameHUD::getInstance();
	//display->setGameContext(this);

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

 //Initialize game into Pre-Play State and sync the clock
   this->GetFSM()->SetCurrentState(PrePlay::getInstance());
   this->GetFSM()->StartCurrentState();
   this->setLastTime(device->getTimer()->getTime());



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

}

void ktcGame::update(const irr::ITimer* timer){
	//running update() on the state machine
	GameStateMachine->update(timer);
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