#include "irrlicht.h"
#include "GameEntity.h"

class Agent:public GameEntity{
private:
	irr::scene::IAnimatedMeshSceneNode* mynodep;
	irr::core::vector3df position;

public:
	virtual void update(irr::ITimer*);
virtual void processMessage(Message*);

Agent(irr::scene::IAnimatedMeshSceneNode* a, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f));
virtual ~Agent();



};