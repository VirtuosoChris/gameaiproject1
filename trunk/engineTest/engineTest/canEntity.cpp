#include "canEntity.h"
using namespace irr;
using namespace irr::core;

canEntity::canEntity(IrrlichtDevice *device){


	irr::scene::ISceneManager* smgr = device->getSceneManager();
	video::IVideoDriver* driver = device->getVideoDriver();


cannode = smgr->addSphereSceneNode();
cannode->setScale(irr::core::vector3df(5,5,5));

//CPTODO::replace constant with something better
cannode->setPosition(irr::core::vector3df(107,5,93));
cannode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
cannode->setMaterialTexture(0,driver->getTexture("../media/spheremap.jpg"));
cannode->setMaterialType(irr::video::EMT_SPHERE_MAP);


irr::scene::ILightSceneNode *lightscenenode = smgr->addLightSceneNode(0,  irr::core::vector3df(25,25,25), irr::video::SColor(255, 255, 0, 0),500);
irr::scene::ILightSceneNode *lightscenenode2 = smgr->addLightSceneNode(0, irr::core::vector3df(-25,-25,-25), irr::video::SColor(255, 255, 0, 0),500);
cannode->addChild(lightscenenode);
cannode->addChild(lightscenenode2);

}


void canEntity::update(irr::ITimer* timer){
cannode->setPosition(vector3df(107.0f,5.0f,93.0f) + 2.0f*(float)sin((double)timer->getTime()/500)*vector3df(0,1,0));
}


void canEntity::processMessage(Message* m){


	delete m;
}