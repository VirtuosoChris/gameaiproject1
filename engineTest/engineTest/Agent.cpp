#include "Agent.h"
#include "InputHandler.h"
#include <cmath>

using namespace irr;
double degreesToRadians(double degrees){
return 2*3.14159*degrees/360;
}

void Agent::update(irr::ITimer* timer){
    
	static bool moving = false;
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
		orientation = mynodep->getRotation().Y;

		//irr::core::vector3df 
			displacement = irr::core::vector3df((irr::f32)cos(degreesToRadians(orientation)), 0.0f, (irr::f32)sin(degreesToRadians(orientation)));//* SPEED * (irr::f32)TIMEELAPSED;
displacement.Z*=-1;			
		nodePos+=displacement;

		mynodep->setPosition(nodePos);

		mynodep->setAnimationSpeed(40);
		if(!moving){moving=true;
			mynodep->setMD2Animation(scene::EMAT_RUN);
		}
		
		return;
	}

	if(ih->isAKeyPressed()){
		mynodep->setAnimationSpeed(30);
		//ROTATE_LEFT
		orientation -= ROTATION_RATE * TIMEELAPSED;
		mynodep->setRotation(irr::core::vector3df(0.0f,orientation,0.0f));

		//mynodep->setRotation(irr::core::vector3df(0.0f,1,0.0f));
 
		
		if(!moving){moving=true;
			mynodep->setMD2Animation(scene::EMAT_RUN);
			
		}
		//MOVE_LEFT
		//nodePos += irr::core::vector3df((irr::f32)cos(orientation - 90.0f), 0.0f, (irr::f32)sin(orientation - 90.0f))* SPEED * (irr::f32)TIMEELAPSED;
		//mynodep->setPosition(nodePos);
return;
	}

	if(ih->isSKeyPressed()){
		//MOVE_BACK
mynodep->setAnimationSpeed(40);
		
    orientation = mynodep->getRotation().Y;
	//irr::core::vector3df 
		displacement = irr::core::vector3df((irr::f32)cos(degreesToRadians(orientation)), 0.0f, (irr::f32)sin(degreesToRadians(orientation)));//* SPEED * (irr::f32)TIMEELAPSED;
	displacement.Z*=-1;
		nodePos -= displacement;//irr::core::vector3df((irr::f32)-cos(orientation), 0.0f, (irr::f32)-sin(orientation))* SPEED * (irr::f32)TIMEELAPSED;
	
	mynodep->setPosition(nodePos);

	
		if(!moving){moving=true;
			mynodep->setMD2Animation(scene::EMAT_RUN);
				
		}

return;
	}

	if(ih->isDKeyPressed()){
		//ROTATE_RIGHT

		orientation += ROTATION_RATE * TIMEELAPSED;
		mynodep->setRotation(irr::core::vector3df(0.0f,(irr::f32)orientation,0.0f));
		
		
		//STRAFE_RIGHT
		//nodePos += irr::core::vector3df((irr::f32)cos(orientation + 90.0f), 0.0f, (irr::f32)sin(orientation + 90.0f))* SPEED * (irr::f32)TIMEELAPSED;
		//mynodep->setPosition(nodePos);

		mynodep->setAnimationSpeed(30);
		if(!moving){moving=true;
			mynodep->setMD2Animation(scene::EMAT_RUN);
			
		}
return;
	}


	if(moving){moving = false;
	
//		if(!moving){moving=true;
			mynodep->setMD2Animation(scene::EMAT_STAND);
//		}
	}


}


void Agent::processMessage(Message*){

}

Agent::Agent(irr::scene::IAnimatedMeshSceneNode* a, irr::core::vector3df p)
:mynodep(a),position(p)
{
	mynodep->setRotation(irr::core::vector3df(0.0f,orientation = 90.0f,0.0f));
	position = mynodep->getPosition();
	
 mynodep->setMD2Animation(scene::EMAT_STAND); //set the animation to stand?
}

Agent::~Agent(){

}