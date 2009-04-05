#include "gunEntity.h"

using namespace irr;
using namespace irr::core;
gunEntity::gunEntity(irr::IrrlichtDevice *device, irr::scene::ICameraSceneNode *camera){

	irr::scene::ISceneManager* smgr = device->getSceneManager();
Model GUN = createModel("../media/dreadus_shotgun.md2","../media/shotgun_map.png",device,1.0f);
//Model GUN = createModel("../media/w_railgun.md2","../media/railgun.pcx",device,1.0f);
gun = smgr->addAnimatedMeshSceneNode(GUN.mesh);

camera->addChild(gun);
gun->setRotation(vector3df(0,270,0));
gun->setPosition(
				 (vector3df(.0f,.0f,.0f)
				// +camera->getTarget()
				)//.normalize()
				);


//gun->setPosition(vector3df(0, 0, gun->getPosition().Z));

//gun->setMaterialFlag(video::EMF_ZBUFFER, false);
gun->setMD2Animation(irr::scene::EMAT_STAND);
gun->setAnimationSpeed(60);
gun->setMaterialTexture(0,GUN.texture);
gun->setMaterialFlag(video::EMF_FOG_ENABLE, true);
gun->setLoopMode(false);

}


void gunEntity::update(irr::ITimer*){}

void gunEntity::processMessage(Message* m){

	switch(m->messageType){
	
		case KTC_PLAYER_LEFT_MOUSE_CLICK:
			if(gun->getFrameNr() >= gun->getEndFrame()){
				gun->setMD2Animation(irr::scene::EMAT_STAND);
			gun->setAnimationSpeed(60);
			}
		break;
		default:;

	}

	delete m;

}