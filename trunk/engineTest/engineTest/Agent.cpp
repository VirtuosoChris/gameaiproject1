#include "Agent.h"
#include "InputHandler.h"
#include <cmath>

void Agent::update(irr::ITimer* timer){
    
	static irr::u32 LASTUPDATE=0;
	static const irr::f32 SPEED = .10f;
	static const float ROTATION_RATE =  .10f;
	int TIMEELAPSED =0; //ADJFHKJHFKJHFKJHF
	InputHandler* ih= InputHandler::getInstance();
	
	if(ih==NULL)return;
	if(!mynodep)return;
	
	if(timer==NULL)return;
	
	irr::u32 ctime= 0;
	TIMEELAPSED = (ctime = timer->getTime()) - LASTUPDATE;
	LASTUPDATE = ctime;

	
	irr::core::vector3df nodePos = mynodep->getPosition();
	

	if(ih->isWKeyPressed()){
		//MOVE_FORWARD
		
		nodePos += irr::core::vector3df((irr::f32)cos(orientation), 0.0f, (irr::f32)sin(orientation))* SPEED * (irr::f32)TIMEELAPSED;
		mynodep->setPosition(nodePos);

	}

	if(ih->isAKeyPressed()){
		
		//ROTATE_LEFT
		orientation -= ROTATION_RATE * TIMEELAPSED;
		mynodep->setRotation(irr::core::vector3df(0.0f,orientation,0.0f));
		//mynodep->setRotation(irr::core::vector3df(0.0f,1,0.0f));
 
		
		//MOVE_LEFT
		//nodePos += irr::core::vector3df((irr::f32)cos(orientation - 90.0f), 0.0f, (irr::f32)sin(orientation - 90.0f))* SPEED * (irr::f32)TIMEELAPSED;
		//mynodep->setPosition(nodePos);

	}

	if(ih->isSKeyPressed()){
		//MOVE_BACK
		
	nodePos += irr::core::vector3df((irr::f32)-cos(orientation), 0.0f, (irr::f32)-sin(orientation))* SPEED * (irr::f32)TIMEELAPSED;
	mynodep->setPosition(nodePos);

	}

	if(ih->isDKeyPressed()){
		//ROTATE_RIGHT

		orientation += ROTATION_RATE * TIMEELAPSED;
		mynodep->setRotation(irr::core::vector3df(0.0f,(irr::f32)orientation,0.0f));
		
		
		//STRAFE_RIGHT
		//nodePos += irr::core::vector3df((irr::f32)cos(orientation + 90.0f), 0.0f, (irr::f32)sin(orientation + 90.0f))* SPEED * (irr::f32)TIMEELAPSED;
		//mynodep->setPosition(nodePos);

	}


}


void Agent::processMessage(Message*){

}

Agent::Agent(irr::scene::IAnimatedMeshSceneNode* a, irr::core::vector3df p)
:mynodep(a),position(p)
{
	mynodep->setRotation(irr::core::vector3df(0.0f,orientation = 0.0f,0.0f));
	position = mynodep->getPosition();

}

Agent::~Agent(){

}