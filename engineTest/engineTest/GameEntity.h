#ifndef IRRLICHT
#include <irrlicht.h>
#define IRRLICHT
#endif

class Message;

class GameEntity{
	protected:
	irr::core::vector3df position;
	irr::core::vector3df velocity;
	
	public:

		double orientation;
		
	irr::core::vector3df displacement;



	virtual void processMessage(Message*)=0;
	virtual void update(irr::ITimer*)=0;
	
	void setVelocity(irr::core::vector3df vel);

	GameEntity();
	virtual ~GameEntity();

};

