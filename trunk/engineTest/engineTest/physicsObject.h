#ifndef PHYSICSOBJECT
#define PHYSICSOBJECT
#include "GameEntity.h"

class physicsObject: public GameEntity{


protected:
	irr::core::vector3df position;
	irr::core::vector3df velocity;
	//irr::core::vector3df displacement;
	double orientation;
	irr::scene::ISceneNode* mynodep;

public:
	inline irr::core::vector3df getPosition(){return position;}
	inline double getOrientation() { return orientation; }
	inline void setVelocity(irr::core::vector3df vel){velocity = vel;}
	inline irr::scene::ISceneNode* getSceneNode(){return mynodep;}
	inline void setPosition(irr::core::vector3df a){position = a;}
	inline irr::core::vector3df getVelocity(){return velocity;}

};



#endif