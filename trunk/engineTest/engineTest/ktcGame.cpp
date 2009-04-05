#include "ktcGame.h"

using namespace irr;
using namespace irr::scene;
using namespace irr::core;


static const float PREDATOR_SPEED = .15f;
static const float PREY_SPEED = .3f;


//#define NODE_MESH_GENERATOR //is the program in node mesh generation mode


ktcGame::ktcGame(IrrlichtDevice *device, irr::scene::ITriangleSelector* selector):can (device),camera (device->getSceneManager()->addCameraSceneNodeFPS()) , gun (device, camera), graph (device, "NODE_LIST.txt","ADJACENCY_LIST.txt","EXCLUDE.txt"), 
agent2 (Model("../media/chuckie.MD2","../media/Chuckie.pcx",device), core::vector3df(-442,351,-863), device->getSceneManager())

{
	
	this->device = device;
	smgr = device->getSceneManager();

	CHUCKIE = agent2.model;
	//can=(device);
	//gun = gunEntity(device, camera);
	
/****************LOAD IN MODELS*******************************/
 
 CARTMAN  = createModel("../media/ERIC.MD2","../media/ERIC.pcx",device, 1.5f);
 CYBERDEMON = createModel("../media/cyber.md2","../media/cyber.pcx",device,3.0f);

 agent2.createCollisionAnimator(selector, smgr);

 GameEntity::setAgentList(&entities);

 entities.push_back(&agent2);

 //camera = 
//	 smgr->addCameraSceneNodeFPS();// addCameraSceneNodeFPS();

 //CPTODO: REPLACE HARD CODED CONSTANT WITH SOMETHING BETTER
 camera->setPosition(core::vector3df(-280,288,-830));

core::list<ISceneNodeAnimator*>::ConstIterator anims=camera->getAnimators().begin(); 
ISceneNodeAnimatorCameraFPS *anim=(ISceneNodeAnimatorCameraFPS*)*anims; 
anim->setMoveSpeed(PREY_SPEED);
anim->setVerticalMovement(false);

scene::ISceneNode *lightscenenode4 = smgr->addLightSceneNode(0, vector3df(0,0,0), irr::video::SColor(255, 175, 175, 0),200);

camera->addChild(lightscenenode4);

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
					smgr->createTriangleSelectorFromBoundingBox(can.cannode),camera,can.cannode->getBoundingBox().getExtent(), vector3df(0,0,0), can.cannode->getBoundingBox().getCenter())
					);

 
 can.cannode->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(camera),can.cannode,camera->getBoundingBox().getExtent(), vector3df(0,0,0), camera->getBoundingBox().getCenter())
					);


camera->addAnimator(
					smgr->createCollisionResponseAnimator(
					smgr->createTriangleSelectorFromBoundingBox(agent2.mynodep),camera,agent2.mynodep->getBoundingBox().getExtent(), vector3df(0,0,0),agent2.mynodep->getBoundingBox().getCenter())
					);


}




void ktcGame::update(irr::ITimer* timer){

device->getVideoDriver()->beginScene(true, true, video::SColor(255,100,101,140));
smgr->drawAll();  //draw 3d objects

graph.render(device->getVideoDriver());

device->getVideoDriver()->clearZBuffer();
gun.gun->render();
device->getVideoDriver()->endScene();//end drawing 

	if(InputHandler::getInstance()->unprocessedMouseMessageLMB){

		MessageHandler::getInstance()->postMessage(KTC_PLAYER_LEFT_MOUSE_CLICK, 0, this, &gun, timer);

#ifdef NODE_MESH_GENERATOR
			graph.addNode(camera->getPosition);
#endif	

			InputHandler::getInstance()->unprocessedMouseMessageLMB = false;
		}



	if(InputHandler::getInstance()->unprocessedMouseMessageRMB){
		InputHandler::getInstance()->unprocessedMouseMessageRMB = false;
	}


	//update all entities
		for(int i = 0; i < (int)entities.size();i++){
			if(entities[i]){
				entities[i]->update(timer);
			}
		}


	if(InputHandler::getInstance()->isTKeyPressed()){
		graph.toggleDebugOutput(!graph.isDebugOutput());
	}

	can.update(timer);
	gun.update(timer);

}


void ktcGame::processMessage(Message* m){
delete m;
}