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
#include "physicsObject.h"

enum Agent_Type{PREDATOR, PREY};

class Agent:public physicsObject{

private:

	
	//this delegates an agent to one of two types: PREDATOR or PREY
	Agent_Type type;

	//an object of the state machine that the agent uses to implement an FSM
	StateMachine<Agent> * AgentStateMachine;

	//pathfinding information
	irr::core::vector3df currentSeekTarget;
	std::list<irr::core::vector3df> pathList;
	irr::core::vector3df previousSeekTarget;
	mapGraph* graph;


	//sensor data
	WallSensorData *s1d;
	std::vector<ProximitySensorData*> s2d;
	PieSensor *pie;

	//list of all the agents other agents can "see"
	static std::vector<Agent*>* agentList;
	
	//data structure representing the 3d model
	Model model;

	//engine related stuff
	scene::ISceneManager* smgr;
	irr::scene::ITriangleSelector* selector;

public:
	
	//pathfinding functions
	irr::core::vector3df seek(irr::core::vector3df);
	void newTargetLocation(irr::core::vector3df,mapGraph* mg);
	void createPatrolRoute(mapGraph* mg);

	//gameEntity functionality
	virtual void update(irr::ITimer*);
	virtual bool processMessage(const Message*);

	//model getter/setter
	inline void setModel(Model m){model = m;}
	inline Model& getModel(){return model;} 

	//agentlist getter/setter
	inline static void setAgentList(std::vector<Agent*>* abc){agentList = abc;}
	inline static std::vector<Agent*>* getAgentList(){return agentList;}

	//agent type getter/setter
	inline Agent_Type getAgentType(){return type;}
	inline void setAgentType(Agent_Type T){	type = T;}

	//seek target getter/setter
	inline irr::core::vector3df getSeekTarget(){return currentSeekTarget;}
	inline void setSeekTarget(irr::core::vector3df pl){ currentSeekTarget = pl;}
	inline irr::core::vector3df getPreviousSeekTarget(){return previousSeekTarget;}
	
	//pathlist getter/setter
	inline std::list<irr::core::vector3df>& getPathList(){return pathList;}
	inline void setPathList(std::list<irr::core::vector3df> pl){pathList = pl;}

	//fsm getter
	inline StateMachine<Agent> * GetFSM() const{ return AgentStateMachine; }
	
	//rendering function for sensor data
	void drawPieSlices(irr::video::IVideoDriver*);


	Agent(Model m, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f),irr::scene::ISceneManager* mgr = NULL, Agent_Type T=PREY, mapGraph* g=0);
	virtual ~Agent();

//i don't think any of this is mine
	double hypo(double opp, double adj);
	double agentProximity(Agent *nearAgent);
	double agentBearing(Agent *nearAgent);
	void proximitySensor(double sensorRange);
	void PieDetect();
	void showPieSensor();


	//creates collision detection on the agent with the world
	void createCollisionAnimator(irr::scene::ITriangleSelector* selector ,irr::scene::ISceneManager* mgr);

	//sensor update functions
	virtual void updateWallSensor();
	void updateProximitySensor();
	void updatePieSensor();

	//outputs wall sensor data as a human-readable string
	std::string WallSensorToString();

	//graph getter/setter
	inline mapGraph* getGraph(){return graph;}
	inline void setGraph(mapGraph* g){graph=g;}

};

#endif