#include "gunEntity.h"
#include <iostream>
using namespace irr;
using namespace irr::core;

static vector3df previousPos;

gunEntity::gunEntity(irr::IrrlichtDevice *device, irr::scene::ICameraSceneNode *camera)
{
ready = true;
	this->device = device;

irr::scene::ISceneManager* smgr = device->getSceneManager();
Model GUN = createModel("../media/dreadus_shotgun.md2","../media/shotgun_map.png",device,1.0f);

 gun = smgr->addAnimatedMeshSceneNode(GUN.mesh);

gun->setRotation(vector3df(0,270,0));
gun->setPosition(
				 (vector3df(.0f,.0f,.0f)
				// +camera->getTarget()
				)//.normalize()
				);

gun->setMD2Animation(irr::scene::EMAT_STAND);
gun->setAnimationSpeed(60);
gun->setMaterialTexture(0,GUN.texture);
gun->setMaterialFlag(video::EMF_FOG_ENABLE, true);
gun->setLoopMode(false);

gun->setPosition(vector3df(0,-1000,0));

previousPos = camera->getPosition();
this->camera = camera;
basePosition = gun->getPosition();

}


void gunEntity::update(const irr::ITimer* timer){
vector3df t = (camera->getPosition() - previousPos);
t.Y = 0;
	if(t.getLength() > .05f){
	gun->setPosition(basePosition + 1.0f*(float)sin((double)timer->getTime()/125)*vector3df(.25,1,0));
	}else{gun->setPosition(basePosition);}
	
	previousPos = camera->getPosition();


	if(gun->getFrameNr() >= gun->getEndFrame()){
		ready = true;			
	}


}

bool gunEntity::processMessage(const Message* m){
	std::cout<<"got to gun processmessage\n";
	if(m == NULL)std::cout<<"WTF THIS IS NULL SOMEHOW\n";
	
	switch(m->messageType){
	
		case KTC_PLAYER_LEFT_MOUSE_CLICK:
			if(gun->getFrameNr() >= gun->getEndFrame()){
				
			ready = false;
				gun->setMD2Animation(irr::scene::EMAT_STAND);
			gun->setAnimationSpeed(60);
			}
			//std::cout<<"did stuff\n";\

		break;
		default:;//std::cout<<"Wrong message type\n";

	}

	return true;

}



void gunEntity::render(){

device->getVideoDriver()->clearZBuffer();

irr::core::matrix4 abc(irr::core::IdentityMatrix);
const float mdat[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,1000,0,1};
abc.setM(mdat);

device->getVideoDriver()->setTransform(video::ETS_WORLD,camera->getAbsoluteTransformation());// camera->getAbsoluteTransformation());
device->getVideoDriver()->setTransform(video::ETS_VIEW, abc);

gun->render();

}