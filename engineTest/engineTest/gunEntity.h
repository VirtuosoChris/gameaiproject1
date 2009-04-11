#ifndef GUNENTITY
#define GUNENTITY
#include "GameEntity.h"
#include "Model.h"
#include "Message.h"

class gunEntity:public GameEntity{

//irr::u32 LASTUPDATE;

public:
	irr::scene::IAnimatedMeshSceneNode* gun;
	irr::scene::ICameraSceneNode *camera;
	irr::core::vector3df basePosition;

	//gunEntity(){};
	gunEntity(IrrlichtDevice *device,irr::scene::ICameraSceneNode *camera);
	virtual void update(irr::ITimer*);
	virtual bool processMessage(const Message*);

};

#endif