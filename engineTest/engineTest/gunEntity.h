#ifndef GUNENTITY
#define GUNENTITY
#include "GameEntity.h"
#include "Model.h"
#include "Message.h"

class gunEntity:public GameEntity{

//irr::u32 LASTUPDATE;

public:
	irr::scene::IAnimatedMeshSceneNode* gun;

	//gunEntity(){};
	gunEntity(IrrlichtDevice *device,irr::scene::ICameraSceneNode *camera);
	virtual void update(irr::ITimer*);
	virtual void processMessage(Message*);

};

#endif