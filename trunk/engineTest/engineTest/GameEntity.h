#ifndef IRRLICHT
#include <irrlicht.h>
#define IRRLICHT
#endif

#include <vector>

class Message;
class Agent;

class GameEntity{
	protected:
	irr::core::vector3df position;
	irr::core::vector3df velocity;

	static std::vector<Agent*>* agentList;
	
	public:

		double orientation;
		
	irr::core::vector3df displacement;

	static void setAgentList(std::vector<Agent*>*);


	virtual void processMessage(Message*)=0;
	virtual void update(irr::ITimer*)=0;


	irr::core::vector3df getPosition();
	
	void setVelocity(irr::core::vector3df vel);

	GameEntity();
	virtual ~GameEntity();

};

