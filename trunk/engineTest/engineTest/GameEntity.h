#ifndef IRRLICHT
#include <irrlicht.h>
#define IRRLICHT
#endif

class Message;

class GameEntity{
	irr::core::vector3df position;
	double orientation;
	irr::core::vector3df velocity;

	public:
	virtual void processMessage(Message*)=0;
	virtual void update()=0;
	
	void setVelocity(irr::core::vector3df vel);

	GameEntity();
	virtual ~GameEntity();

};

