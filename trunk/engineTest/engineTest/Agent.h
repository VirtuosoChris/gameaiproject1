#ifndef AGENT
#define AGENT

#include "irrlicht.h"
#include "GameEntity.h"
#include "Sensors.h"
#include "Model.h"
#include <string>
#include <list>
#include "mapGraph.h"
#include "StateMachine.h"
#include "AgentStates.h"

enum Agent_Type{PREDATOR, PREY};

class Agent:public GameEntity{

private:
	
	irr::core::vector3df currentSeekTarget;
	std::list<irr::core::vector3df> pathList;
	irr::core::vector3df previousSeekTarget;
	//this delegates an agent to one of two types: PREDATOR or PREY
	Agent_Type type;

	//an object of the state machine that the agent uses to implement an FSM
	StateMachine<Agent> * AgentStateMachine;



public:
	
	mapGraph* graph;

	inline Agent_Type getAgentType(){
		return type;
	}


	inline void setAgentType(Agent_Type T){
		type = T;
	}
	inline StateMachine<Agent> * GetFSM() const{ return AgentStateMachine; }
	
	inline std::list<irr::core::vector3df>& getPathList(){
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
	virtual bool processMessage(const Message*);

	//Agent(irr::scene::IAnimatedMeshSceneNode* a, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f));

	virtual ~Agent();

	Agent(Model m, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f),irr::scene::ISceneManager* mgr = NULL, Agent_Type T=PREY, mapGraph* g=0);

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
void newTargetLocation(irr::core::vector3df,mapGraph* mg);
void createPatrolRoute(mapGraph* mg);};

#endif