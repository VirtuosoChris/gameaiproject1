#define AGENT

#include "irrlicht.h"

#ifndef GAMEENTITY
#include "GameEntity.h"
#endif

#ifndef SENSORS
#include "Sensors.h"
#endif

#ifndef MODEL
#include "Model.h"
#endif

#include <string>

class Agent:public GameEntity{
public:
	irr::scene::IAnimatedMeshSceneNode* mynodep;
	irr::core::vector3df position;
	irr::u32 LASTUPDATE;
	Model model;
	
	scene::ISceneManager* smgr;
	irr::scene::ITriangleSelector* selector;

	void drawPieSlices(irr::video::IVideoDriver*);


	WallSensorData *s1d;
	std::vector<ProximitySensorData*> s2d;
	PieSensor *pie;

virtual void update(irr::ITimer*);
virtual void processMessage(Message*);

//Agent(irr::scene::IAnimatedMeshSceneNode* a, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f));

virtual ~Agent();

Agent(Model m, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f),irr::scene::ISceneManager* mgr = NULL);

double hypo(double opp, double adj);

double agentProximity(Agent *nearAgent);

double agentBearing(Agent *nearAgent);

void proximitySensor(double sensorRange);

void PieDetect();

void showPieSensor();

void createCollisionAnimator(irr::scene::ITriangleSelector* selector ,irr::scene::ISceneManager* mgr);

virtual void updateWallSensor();

void updateProximitySensor();

std::string WallSensorToString();

void updatePieSensor();


};