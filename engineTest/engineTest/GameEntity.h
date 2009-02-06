#ifndef IRRLICHT
#include <irrlicht.h>
#endif

class GameEntity{
	irr::core::vector3df position;
	double orientation;
	
	public:
	virtual void processMessage(Message*)=0;
	virtual void update()=0;
};

