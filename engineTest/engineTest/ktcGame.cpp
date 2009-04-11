#include "ktcGame.h"

using namespace irr;
using namespace irr::scene;
using namespace irr::core;


static const float PREDATOR_SPEED = .15f;
static const float PREY_SPEED = .3f;


vector3df ppos;

//#define NODE_MESH_GENERATOR //is the program in node mesh generation mode
//-442,351,-863
//-528.744751 0.024357 102.937782
ktcGame::ktcGame(IrrlichtDevice *device, irr::scene::ITriangleSelector* selector):can (device),camera (device->getSceneManager()->addCameraSceneNodeFPS()) , gun (device, camera), graph (device, "NODE_LIST.txt","ADJACENCY_LIST.txt","EXCLUDE.txt"), 
agent2 (Model("../media/chuckie.MD2","../media/Chuckie.pcx",device), core::vector3df(-528.744751, 0.024357, 102.937782), device->getSceneManager(), PREY, &graph)

{
	
	this->device = device;
	smgr = device->getSceneManager();

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

scene::ISceneNode *lightscenenode4 = smgr->addLightSceneNode(0, vector3df(0,0,0), irr::video::SColor(255, 175, 175, 0),200);

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
					smgr->createTriangleSelectorFromBoundingBox(can.getSceneNode()),camera,can.getSceneNode()->getBoundingBox().getExtent(), vector3df(0,0,0), can.getSceneNode()->getBoundingBox().getCenter())
					);

 
 can.getSceneNode()->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(camera),can.getSceneNode(),camera->getBoundingBox().getExtent(), vector3df(0,0,0), camera->getBoundingBox().getCenter())
					);


camera->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(((irr::scene::IAnimatedMeshSceneNode*)agent2.getSceneNode())),camera,((irr::scene::IAnimatedMeshSceneNode*)agent2.getSceneNode())->getBoundingBox().getExtent(), vector3df(0,0,0),((irr::scene::IAnimatedMeshSceneNode*)agent2.getSceneNode())->getBoundingBox().getCenter())
					);


#ifndef NODE_MESH_GENERATOR
agent2.createPatrolRoute(&graph);
#endif

graph.selector = selector;

ppos = camera->getPosition();

}

//shit, needs to be relative to map
//camera->setPosition(this->spawnPointList[0]);

Agent* agent3 = new Agent(CARTMAN, spawnPointList[0], smgr, PREY, &this->graph);
agent3->createCollisionAnimator(selector, smgr);
#ifndef NODE_MESH_GENERATOR
agent3->createPatrolRoute(this->graph.minimumSpanningTree(0));
#endif
entities.push_back(agent3);

//Agent agent1(CYBERDEMON, spawnPointList[1], smgr, PREY, &this->graph);
//agent1.createCollisionAnimator(selector, smgr);

}




void ktcGame::update(irr::ITimer* timer){
	//graph.toggleDebugOutput(false);

//	camera->setPosition(ppos);

	//cam2->setPosition(agent2.getPosition());
	//std::cout<<float(agent2.getPosition().X)<<":"<<float(agent2.getPosition().Y)<<":"<<float(agent2.getPosition().Z)<<"\n";
device->getVideoDriver()->beginScene(true, true, video::SColor(255,100,101,140));



smgr->drawAll();  //draw 3d objects



static mapGraph* mintree = graph.minimumSpanningTree(0);
//graph.minimumSpanningTree(0)->render(device->getVideoDriver());
mintree->render(device->getVideoDriver());
//graph.render(device->getVideoDriver());
//agent2.drawPieSlices(device->getVideoDriver());

//update all entities
		for(int i = 0; i < (int)entities.size();i++){
			if(entities[i]){
				//entities[i]->update(timer);
				
				if(graph.isDebugOutput()){
			//	entities[i]->drawPieSlices(device->getVideoDriver());
				}
			}
		}

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



			InputHandler::getInstance()->unprocessedMouseMessageLMB = false;
		}



	if(InputHandler::getInstance()->unprocessedMouseMessageRMB){
		//graph.output();
		InputHandler::getInstance()->unprocessedMouseMessageRMB = false;
	}


	//update all entities
		for(int i = 0; i < (int)entities.size();i++){
			if(entities[i]){
				entities[i]->update(timer);
			//	entities[i]->drawPieSlices(device->getVideoDriver());
			}
		}


	if(InputHandler::getInstance()->isTKeyPressed()){
		graph.toggleDebugOutput(!graph.isDebugOutput());
	}

	can.update(timer);
	gun.update(timer);


	///gun.gun->setPosition(camera->getPosition());	
	//gun.gun->setRotation(camera->getRotation() + vector3df(0,270,0));

}


bool ktcGame::processMessage(const Message* m){
delete m;
return true;
}

ktcGame::~ktcGame(){


}