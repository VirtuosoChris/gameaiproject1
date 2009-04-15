#ifndef PLAYER
#define PLAYER
#include "irrlicht.h"
#include "gunEntity.h"
#include <string>

using namespace irr;
using namespace irr::scene;

class player:public physicsObject{


	//Camera Scene Node
	scene::ICameraSceneNode *camera;
	
	gunEntity gun;
	vector3df ppos; 
	double lastUpdate;


public:


	void setCameraSpeed(double ns){
	core::list<ISceneNodeAnimator*>::ConstIterator anims=camera->getAnimators().begin(); 
	ISceneNodeAnimatorCameraFPS *anim=(ISceneNodeAnimatorCameraFPS*)*anims; 
	anim->setMoveSpeed(ns);
	
	}

	void useSpectatorCamera(){
	
	core::list<ISceneNodeAnimator*>::ConstIterator anims=camera->getAnimators().begin(); 
	ISceneNodeAnimatorCameraFPS *anim=(ISceneNodeAnimatorCameraFPS*)*anims; 
	
	//anim->setVerticalMovement(true);
	throw std::string("Not done yet");
	

	
	}

	void useShooterCamera(){

	core::list<ISceneNodeAnimator*>::ConstIterator anims=camera->getAnimators().begin(); 
	ISceneNodeAnimatorCameraFPS *anim=(ISceneNodeAnimatorCameraFPS*)*anims; 
	anim->setVerticalMovement(false);

	}
	
	
	virtual void setPosition(irr::core::vector3df n){
		mynodep->setPosition(n);
		this->position = n;
		ppos = n;
	
	}

	
	player(irr::IrrlichtDevice* device):camera (device->getSceneManager()->addCameraSceneNodeFPS()) , gun (device, camera){
		
	this->mynodep = camera;
	lastUpdate = 0;
	
	scene::ISceneNode *lightscenenode4 = device->getSceneManager()->addLightSceneNode(0, vector3df(0,0,0), irr::video::SColor(255, 100, 100, 0),200);
	camera->addChild(lightscenenode4);
	
	useShooterCamera();
	}


	virtual void update(const irr::ITimer* timer){
		
		double timeElapsed = timer->getTime()- lastUpdate;
		lastUpdate = timer->getTime();
		velocity = mynodep->getPosition() - ppos / timeElapsed;
		this->setPosition(mynodep->getPosition());
		ppos = mynodep->getPosition();
		gun.update(timer);
	
	}


	virtual bool processMessage(const Message* msg){
	return false;
	}



	player(){}

	gunEntity& getGun(){return this->gun;}



};


#endif