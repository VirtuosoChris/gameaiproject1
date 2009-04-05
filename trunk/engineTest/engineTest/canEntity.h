#ifndef CANENTITY
#define CANENTITY
#include "irrlicht.h"
#include "GameEntity.h"

using namespace irr;
using namespace irr::core;
class canEntity:public GameEntity{

public:

	irr::scene::ISceneNode* cannode;
	canEntity(IrrlichtDevice *device);
	virtual void update(irr::ITimer* timer);
	virtual void processMessage(Message*);
	//canEntity(){};

};

#endif