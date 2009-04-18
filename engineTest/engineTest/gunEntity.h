#ifndef GUNENTITY
#define GUNENTITY
#include "GameEntity.h"
#include "gameHUD.h"
#include "Model.h"
#include "Message.h"

class gunEntity : public GameEntity{

//irr::u32 LASTUPDATE;
private:
	irr::u32 lastFired;

public:
	irr::scene::IAnimatedMeshSceneNode* gun;
	irr::scene::ICameraSceneNode *camera;
	irr::core::vector3df basePosition;
	irr::IrrlichtDevice *device;
	bool animationReady; 

	//gunEntity(){};
	gunEntity(irr::IrrlichtDevice *device, irr::scene::ICameraSceneNode *camera);
	virtual void update(const irr::ITimer*);
	virtual bool processMessage(const Message*);
	void render();
	bool isReady(){return animationReady;}


	gunEntity(){}

};

#endif