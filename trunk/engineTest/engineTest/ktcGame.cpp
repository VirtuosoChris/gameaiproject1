#include "ktcGame.h"


//#define COVER_OBJECT_GENERATOR

using namespace irr;
using namespace irr::scene;
using namespace irr::core;

static const float PREDATOR_SPEED = .15f;
static const float PREY_SPEED = .3f;


vector3df ppos;



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
ktcGame::ktcGame(IrrlichtDevice *device, irr::scene::ITriangleSelector* selector, gameHUD* display):can (device),camera (device->getSceneManager()->addCameraSceneNodeFPS()) , gun (device, camera), graph (device, "NODE_LIST.txt","ADJACENCY_LIST.txt","EXCLUDE.txt"), 
agent2 (Model("../media/chuckie.MD2","../media/Chuckie.pcx",device), core::vector3df(-528.744751, 0.024357, 102.937782), device->getSceneManager(), PREY, &graph)

{
	//Instantiate the Irrlicht Engine Device
	this->device = device;
	
	//Instantiate the Irrlicht Engine Scene Manager
	smgr = device->getSceneManager();

	//Instantiate the GameHUD Device
	this->display = display;

	CHUCKIE = agent2.getModel();


	
	FILE* fp = fopen("SPAWN_POINTS.txt", "r");
	if(fp){
		float a[3];
		while(!feof(fp)){
			fscanf(fp, "%f %f %f\n", a, &a[1], &a[2]);
			this->spawnPointList.push_back(irr::core::vector3df(a[0],a[1],a[2]));

			irr::scene::ISceneNode* b;
			b = smgr->addSphereSceneNode(1);
			b->setMaterialFlag(irr::video::EMF_LIGHTING, true);
			b->setPosition(irr::core::vector3df(a[0], a[1], a[2]));
		}
	
		fclose(fp);
}

fp = fopen("COVER_OBJECTS.txt", "r");
if(fp){
float a[3];
while(!feof(fp)){
	fscanf(fp, "%f %f %f\n", a, &a[1], &a[2]);
	this->coverObjectList.push_back(new coverObject(vector3df(a[0], a[1], a[2]), device));
	//	irr::scene::ISceneNode* t= smgr->addCubeSceneNode(1);
	//	t->setPosition( irr::core::vector3df(a[0], a[1], a[2]) );
	//	t->setScale(vector3df(50,75,50));
	//	t->setMaterialTexture(0, device->getVideoDriver()->getTexture("../media/crate.jpg"));
	//		t->setMaterialTexture(1, device->getVideoDriver()->getTexture("../media/cratebump.jpg"));
	//		t->setMaterialFlag(video::EMF_LIGHTING, true);
	//		t->setMaterialFlag(video::EMF_FOG_ENABLE, true);
	//		t->setMaterialType(video::EMT_LIGHTMAP_LIGHTING_M4);
	
}
fclose(fp);
}


	//can=(device);
	//gun = gunEntity(device, camera);
	
/****************LOAD IN MODELS*******************************/
 
 CARTMAN  = createModel("../media/ERIC.MD2","../media/ERIC.pcx",device, 1.0f);
 CYBERDEMON = createModel("../media/cyber.md2","../media/cyber.pcx",device,3.0f);

agent2.createCollisionAnimator(selector, smgr);

 Agent::setAgentList(&entities);

 entities.push_back(&agent2);

 //camera = 
//	 smgr->addCameraSceneNodeFPS();// addCameraSceneNodeFPS();

 //CPTODO: REPLACE HARD CODED CONSTANT WITH SOMETHING BETTER
 //camera->setPosition(core::vector3df(-280,288,-830));

core::list<ISceneNodeAnimator*>::ConstIterator anims=camera->getAnimators().begin(); 
ISceneNodeAnimatorCameraFPS *anim=(ISceneNodeAnimatorCameraFPS*)*anims; 
anim->setMoveSpeed(PREDATOR_SPEED);
anim->setVerticalMovement(false);

scene::ISceneNode *lightscenenode4 = smgr->addLightSceneNode(0, vector3df(0,0,0), irr::video::SColor(255, 100, 100, 0),200);

camera->addChild(lightscenenode4);


camera->setPosition( spawnPointList[3] );//- vector3df(-1300,-144,-1249));

scene::ISceneNodeAnimator *nodeAnimator = 
	smgr->createCollisionResponseAnimator(selector,//geometry for collision 
	camera, //scene node to apply collision to/	
	CHUCKIE.mesh->getBoundingBox().getExtent(),
	core::vector3df(0,-10,0),//gravity 
	CHUCKIE.mesh->getBoundingBox().getCenter()//core::vector3df(0,30,0)
	); //collision volume position
if(!nodeAnimator){throw new std::string("Error creating node animator");}
 camera->addAnimator(nodeAnimator);
 nodeAnimator->drop();

 camera->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(can.getSceneNode()),camera,CHUCKIE.mesh->getBoundingBox().getExtent(), vector3df(0,0,0), CHUCKIE.mesh->getBoundingBox().getCenter())
					);

 
// can.getSceneNode()->addAnimator(
//					smgr->createCollisionResponseAnimator(
//					smgr->createTriangleSelectorFromBoundingBox(camera),can.getSceneNode(),CHUCKIE.mesh->getBoundingBox().getExtent(), vector3df(0,0,0), CHUCKIE.mesh->getBoundingBox().getCenter())
//					);


camera->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(((irr::scene::IAnimatedMeshSceneNode*)agent2.getSceneNode())),camera,((irr::scene::IAnimatedMeshSceneNode*)agent2.getSceneNode())->getBoundingBox().getExtent(), vector3df(0,0,0),((irr::scene::IAnimatedMeshSceneNode*)agent2.getSceneNode())->getBoundingBox().getCenter())
					);



//make the camera collide with cover
for(int i = 0; i < this->coverObjectList.size(); i++){
/*
	coverObjectList[i]->getSceneNode()->addAnimator(
smgr->createCollisionResponseAnimator(
									  smgr->createTriangleSelectorFromBoundingBox(
									  agent2.getSceneNode()),
									  coverObjectList[i]->getSceneNode(), 
									  coverObjectList[i]->getSceneNode()->getBoundingBox().getExtent(),
									  vector3df(0,0,0), 
									  coverObjectList[i]->getSceneNode()->getBoundingBox().getCenter()
									  )
					);*/


 camera->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(
					coverObjectList[i]->getSceneNode()),
					camera,CHUCKIE.mesh->getBoundingBox().getExtent(), 
					vector3df(0,0,0), 
					CHUCKIE.mesh->getBoundingBox().getCenter()
					)
					);

 agent2.getSceneNode()->addAnimator(
	 	smgr->createCollisionResponseAnimator(
		smgr->createTriangleSelectorFromBoundingBox(coverObjectList[i]->getSceneNode()),agent2.getSceneNode(),CHUCKIE.mesh->getBoundingBox().getExtent(), vector3df(0,0,0), CHUCKIE.mesh->getBoundingBox().getCenter())
					);
}


#ifndef NODE_MESH_GENERATOR
agent2.createPatrolRoute(&graph);
#endif

graph.selector = selector;

ppos = camera->getPosition();


//shit, needs to be relative to map
//camera->setPosition(this->spawnPointList[0]);

Agent* agent3 = new Agent(CARTMAN, spawnPointList[0], smgr, PREY, &this->graph);
agent3->createCollisionAnimator(selector, smgr);
#ifndef NODE_MESH_GENERATOR
//agent3->createPatrolRoute(this->graph.minimumSpanningTree(0));


agent3->setPathList(this->generateDefenseArc(0,2*3.14159, 120, 8));

#endif
entities.push_back(agent3);

//Agent agent1(CYBERDEMON, spawnPointList[1], smgr, PREY, &this->graph);
//agent1.createCollisionAnimator(selector, smgr);

//Initialize Player Scoresfor(int x=0 ; x<5 ; x++)	playerScores[x] = 0;}


}

void ktcGame::update(irr::ITimer* timer){
	//graph.toggleDebugOutput(false);

//	camera->setPosition(ppos);

	//cam2->setPosition(agent2.getPosition());
	//std::cout<<float(agent2.getPosition().X)<<":"<<float(agent2.getPosition().Y)<<":"<<float(agent2.getPosition().Z)<<"\n";
device->getVideoDriver()->beginScene(true, true, video::SColor(255,100,101,140));

smgr->drawAll();  //draw 3d objects

display->render();



#ifndef NODE_MESH_GENERATOR
static mapGraph* mintree = graph.minimumSpanningTree(0);
//graph.minimumSpanningTree(0)->render(device->getVideoDriver());
mintree->render(device->getVideoDriver());
//graph.render(device->getVideoDriver());
//agent2.drawPieSlices(device->getVideoDriver());

//agent2.update(timer);
//update all entities
		for(int i = 0; i < (int)entities.size();i++){
			if(entities[i]){
				entities[i]->update(timer);
				
				if(graph.isDebugOutput()){
			//	entities[i]->drawPieSlices(device->getVideoDriver());
				}
			}
		}
#endif
device->getVideoDriver()->clearZBuffer();

irr::core::matrix4 abc(irr::core::IdentityMatrix);
const float mdat[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,1000,0,1};
abc.setM(mdat);

//abc.setTranslation(vector3df(1,1000,10));

//abc.setTranslation(vector3df(0,100,0));

device->getVideoDriver()->setTransform(video::ETS_WORLD,camera->getAbsoluteTransformation());// camera->getAbsoluteTransformation());
device->getVideoDriver()->setTransform(video::ETS_VIEW, abc);

//gun.gun->setRotation(camera->getAbsoluteTransformation().getRotationDegrees()+ vector3df(0,270,0));
//gun.gun->setPosition(camera->getAbsoluteTransformation().getTranslation());
//gun.gun->setScale(camera->getAbsoluteTransformation().getScale());

gun.gun->render();
device->getVideoDriver()->endScene();//end drawing 

if(InputHandler::getInstance()->unprocessedMouseMessageLMB){

	entities[1]->setPathList(this->generateDefenseArc(0,2*3.14, 120,8));
		MessageHandler::getInstance()->postMessage(KTC_PLAYER_LEFT_MOUSE_CLICK, 0, this, &gun, timer);

	//	MessageHandler::getInstance()->postMessage(KTC_KILL, 2000, this, &agent2, timer);

	//agent2.newTargetLocation(camera->getPosition(), &graph);

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


	//update all entities
		for(int i = 0; i < (int)entities.size();i++){
			if(entities[i]){
				//entities[i]->update(timer);
			//	entities[i]->drawPieSlices(device->getVideoDriver());
			}
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
	gun.update(timer);


	///gun.gun->setPosition(camera->getPosition());	
	//gun.gun->setRotation(camera->getRotation() + vector3df(0,270,0));

	scene::ISceneNode* SceneNodeSeen;
	SceneNodeSeen = ktcGame::pointing();
	if(SceneNodeSeen == agent2.getSceneNode()){
		std::cout << "I'm looking at Chuckie;\n";
	}

}


bool ktcGame::processMessage(const Message* m){
	delete m;
	return true;
}

ISceneNode* ktcGame::pointing(){
	ISceneNode* selectedSceneNode;
	ISceneNode* returnedSceneNode;

	//get the scene node that the camera is looking at
	selectedSceneNode = smgr->getSceneCollisionManager()->getSceneNodeFromCameraBB(camera);

	returnedSceneNode = ktcGame::GetCan(selectedSceneNode);
	if(returnedSceneNode){
		std::cout << "I'm looking at the can.\n";
		return returnedSceneNode;
	}

	returnedSceneNode = ktcGame::GetAgent(selectedSceneNode);
	if(returnedSceneNode){
		std::cout << "I'm looking at an agent.\n";
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