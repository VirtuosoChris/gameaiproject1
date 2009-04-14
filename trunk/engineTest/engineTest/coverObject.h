#ifndef COVEROBJECT
#define COVEROBJECT

#include "irrlicht.h"
#include "physicsObject.h"

class coverObject:public physicsObject{

private:

public:
	
	static double getRadius(){return 50;}

	coverObject(irr::core::vector3df p, irr::IrrlichtDevice* device){
	
		setPosition(p);
		mynodep = device->getSceneManager()->addCubeSceneNode(1);
		mynodep->setPosition(p);
		mynodep->setScale(vector3df(50,75,50));
		mynodep->setMaterialTexture(0, device->getVideoDriver()->getTexture("../media/crate.jpg"));
		mynodep->setMaterialTexture(1, device->getVideoDriver()->getTexture("../media/cratebump.jpg"));
		mynodep->setMaterialFlag(video::EMF_LIGHTING, true);
		mynodep->setMaterialFlag(video::EMF_FOG_ENABLE, true);
		mynodep->setMaterialType(video::EMT_LIGHTMAP_LIGHTING_M4);
	}

	~coverObject(){
		if(mynodep){
		mynodep->drop();
		}
	}



	
virtual bool processMessage(const Message*){
return false;}
virtual void update(const irr::ITimer* t){;}

};






#endif