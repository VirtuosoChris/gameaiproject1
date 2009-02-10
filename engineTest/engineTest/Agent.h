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
	
	scene::ISceneManager* smgr;

	Sensor1Data *s1d;
	Sensor2Data *s2d;
	Sensor3Data *s3d;
	

public:
virtual void update(irr::ITimer*);
virtual void processMessage(Message*);

//Agent(irr::scene::IAnimatedMeshSceneNode* a, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f));

virtual ~Agent();

Agent(Model m, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f),irr::scene::ISceneManager* mgr = NULL);

double agentProximity(Agent *nearAgent);

double agentBearing(Agent *nearAgent);

std::vector<Sensor2Data*> *proximitySensor(std::vector<Agent*> globalAgentList, double sensorRange);

void createCollisionAnimator(irr::scene::ITriangleSelector* selector ,irr::scene::ISceneManager* mgr);


};