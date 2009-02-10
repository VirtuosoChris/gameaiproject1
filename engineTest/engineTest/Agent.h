#include "irrlicht.h"
#include "GameEntity.h"

#include "Sensors.h"

#include "Model.h"

class Agent:public GameEntity{
protected:
	irr::scene::IAnimatedMeshSceneNode* mynodep;
	irr::core::vector3df position;
	irr::u32 LASTUPDATE;
	Model model;

	Sensor1Data s1d;
	Sensor2Data s2d;
	Sensor3Data s3d;
	

public:
virtual void update(irr::ITimer*);
virtual void processMessage(Message*);

Agent(irr::scene::IAnimatedMeshSceneNode* a, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f));
virtual ~Agent();

Agent(Model m, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f),irr::scene::ISceneManager* mgr = NULL);

void createCollisionAnimator(irr::scene::ITriangleSelector* selector ,irr::scene::ISceneManager* mgr);


};