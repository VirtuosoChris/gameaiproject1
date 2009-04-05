#ifndef AGENT
#define AGENT

#include "irrlicht.h"
#include "GameEntity.h"
#include "Sensors.h"
#include "Model.h"
#include <string>
#include <list>

class Agent:public GameEntity{

	irr::core::vector3df currentSeekTarget;
	std::list<irr::core::vector3df> pathList;

public:
	
	inline std::list<irr::core::vector3df> getPathList(){
	return pathList;
	}

	inline void setPathList(std::list<irr::core::vector3df> pl){
	 pathList = pl;
	}

	inline irr::core::vector3df getSeekTarget(){
	return currentSeekTarget;
	}

	inline void setSeekTarget(irr::core::vector3df pl){
	 currentSeekTarget = pl;
	}


	irr::scene::IAnimatedMeshSceneNode* mynodep;
	irr::core::vector3df position;
	irr::u32 LASTUPDATE;
	Model model;

	bool MOVING;
	
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

irr::core::vector3df seek(irr::core::vector3df);
void newTargetLocation(irr::core::vector3df);




};

#endif