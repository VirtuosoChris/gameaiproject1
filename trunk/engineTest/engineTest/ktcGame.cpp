#include "ktcGame.h"

using namespace irr;
using namespace irr::scene;
using namespace irr::core;


static const float PREDATOR_SPEED = .15f;
static const float PREY_SPEED = .3f;


//#define NODE_MESH_GENERATOR //is the program in node mesh generation mode
//-442,351,-863
//-528.744751 0.024357 102.937782
ktcGame::ktcGame(IrrlichtDevice *device, irr::scene::ITriangleSelector* selector):can (device),camera (device->getSceneManager()->addCameraSceneNodeFPS()) , gun (device, camera), graph (device, "NODE_LIST.txt","ADJACENCY_LIST.txt","EXCLUDE.txt"), 
agent2 (Model("../media/chuckie.MD2","../media/Chuckie.pcx",device), core::vector3df(-528.744751, 0.024357, 102.937782), device->getSceneManager(), PREY, &graph)

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



agent2.createPatrolRoute(&graph);


graph.selector = selector;

/*std::list<irr::core::vector3df>::const_iterator iter = agent2.getPathList().begin();
for(int i = 0; i < agent2.getPathList().size()-1; i++){

 core::line3d<f32> line;
 core::vector3df intersection;
 core::triangle3df triangle;
 line.start = *iter;
 iter++;
 line.end = *iter;

 if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle)){
	 std::cout<<"WTF SOMEHOW THE PATH IS WRONG\n";///exit(0);
	 break;
	}

}*/

std::cout<<"....................................................";
std::list<vector3df>::const_iterator iter2 = agent2.getPathList().begin();
for(int i = 0; i < agent2.getPathList().size(); i++){
	std::cout<<graph.getClosestNode( (*iter2) ) <<" ";

		iter2++;
}std::cout<<std::endl;


//std::cout<<"ASLJDjkashd\n"<<graph.minimumSpanningTree(0)->adjacencyList[43][0]<<std::endl;

}




void ktcGame::update(irr::ITimer* timer){

device->getVideoDriver()->beginScene(true, true, video::SColor(255,100,101,140));
smgr->drawAll();  //draw 3d objects
agent2.drawPieSlices(device->getVideoDriver());


//graph.minimumSpanningTree(0)->render(device->getVideoDriver());
graph.render(device->getVideoDriver());

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


		//MessageHandler::getInstance()->postMessage(KTC_PLAYER_LEFT_MOUSE_CLICK, 2000, this, &gun, timer);

	//	MessageHandler::getInstance()->postMessage(KTC_KILL, 2000, this, &agent2, timer);

	//agent2.newTargetLocation(camera->getPosition(), &graph);

#ifdef NODE_MESH_GENERATOR
			graph.addNode(camera->getPosition);
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