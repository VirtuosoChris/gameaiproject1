#include "gunEntity.h"
#include <iostream>
using namespace irr;
using namespace irr::core;

static vector3df previousPos;

gunEntity::gunEntity(irr::IrrlichtDevice *device, irr::scene::ICameraSceneNode *camera)
{

	this->device = device;

irr::scene::ISceneManager* smgr = device->getSceneManager();
Model GUN = createModel("../media/dreadus_shotgun.md2","../media/shotgun_map.png",device,1.0f);
//Model GUN = createModel("../media/w_railgun.md2","../media/railgun.pcx",device,1.0f);
 gun = smgr->addAnimatedMeshSceneNode(GUN.mesh);
//camera->addChild(gun);
gun->setRotation(vector3df(0,270,0));
gun->setPosition(
				 (vector3df(.0f,.0f,.0f)
				// +camera->getTarget()
				)//.normalize()
				);

//gun2->remove();
//gun->setPosition(vector3df(0, 0, gun->getPosition().Z));

//gun->setMaterialFlag(video::EMF_ZBUFFER, false);
gun->setMD2Animation(irr::scene::EMAT_STAND);
gun->setAnimationSpeed(60);
gun->setMaterialTexture(0,GUN.texture);
gun->setMaterialFlag(video::EMF_FOG_ENABLE, true);
gun->setLoopMode(false);
//gun->setPosition(vector3df(-1000,-1000,-1000));//HACKHACKHACK
//gun->setRenderFromIdentity(true);
gun->setPosition(vector3df(0,-1000,0));
//gun->setMaterialFlag(video::EMF_ZBUFFER, false);
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

}

bool gunEntity::processMessage(const Message* m){
	std::cout<<"got to gun processmessage\n";
	if(m == NULL)std::cout<<"WTF THIS IS NULL SOMEHOW\n";
	
	switch(m->messageType){
	
		case KTC_PLAYER_LEFT_MOUSE_CLICK:
			if(gun->getFrameNr() >= gun->getEndFrame()){
				gun->setMD2Animation(irr::scene::EMAT_STAND);
			gun->setAnimationSpeed(60);
			}
			std::cout<<"did stuff\n";
		break;
		default:std::cout<<"Wrong message type\n";

	}

	return true;

}



void gunEntity::render(){

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

gun->render();

}