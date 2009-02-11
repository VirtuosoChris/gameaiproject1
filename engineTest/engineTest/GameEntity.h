#define GAMEENTITY

#include <irrlicht.h>

#include <vector>

class Message;
class Agent;

class GameEntity{
	protected:
	irr::core::vector3df position;
	irr::core::vector3df velocity;
	irr::core::vector3df displacement;

	static std::vector<Agent*>* agentList;
	
	public:
		double orientation;
	static void setAgentList(std::vector<Agent*>*);


	virtual void processMessage(Message*)=0;
	virtual void update(irr::ITimer*)=0;

	irr::core::vector3df getPosition();
	double getOrientation() { return orientation; }
	
	void setVelocity(irr::core::vector3df vel);

	GameEntity();
	virtual ~GameEntity();

};

