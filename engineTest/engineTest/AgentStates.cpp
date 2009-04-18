#include "AgentStates.h"
#include "Agent.h"
#include "MessageHandler.h"
#include "cpMath.h"

#include <iostream>
using std::cout;

//methods for Defend
Defend* Defend::GetInstance(){

  static Defend only_inst;

  return &only_inst;
}

void Defend::Enter(Agent & agt){
	cout << "Entering Defend state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Defend::Execute(Agent & agt, const irr::ITimer* timer){
	cout << "Executing Defend state.\n";

	//put ChangeState shit here in if conditions
}

void Defend::Exit(Agent & agt){
	cout << "Exiting Defend state.\n";
}

bool Defend::ExecuteMessage(Agent & agt, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	if(agt.pl_inv.getTime() > 0){
							//don't kill agent cause he's invincible
							return true;
						}
						cout << "I killed you sucka.\n";
						agt.GetFSM()->ChangeState(Die::GetInstance());
						return true;
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}


//methods for Patrol
Patrol* Patrol::GetInstance(){

  static Patrol only_inst;

  return &only_inst;
}

void Patrol::Enter(Agent & agt){
	cout << "Entering Patrol state.\n";

//	agt.create
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Patrol::Execute(Agent & agt, const irr::ITimer* timer){
	//cout << "Executing Patrol state.\n";

	irr::core::vector3df accel;
	accel= agt.followPath(timer);
	agt.walk(accel);

}

void Patrol::Exit(Agent & agt){
	cout << "Exiting Patrol state.\n";
}

bool Patrol::ExecuteMessage(Agent & agt, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	if(agt.pl_inv.getTime() > 0){
							//don't kill agent cause he's invincible
							return true;
						}
						cout << "I killed you sucka.\n";
						agt.GetFSM()->ChangeState(Die::GetInstance());
						return true;
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}


//methods for Pursue
Pursue * Pursue::GetInstance(){

  static Pursue only_inst;

  return &only_inst;
}

void Pursue::Enter(Agent & agt){
	cout << "Entering Persue state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Pursue::Execute(Agent & agt, const irr::ITimer* timer){
	cout << "Executing Persue state.\n";

	if(agt.getSpottedAgent()){
	//agt.walk(2*agt.seek(agt.getSpottedAgent()->getPosition())+ agt.wallAvoidance());
		agt.walk(agt.seek(agt.getSpottedAgent()->getPosition())+ agt.wallAvoidance());
	}

	//put ChangeState shit here in if conditions
}

void Pursue::Exit(Agent & agt){
	cout << "Exiting Persue state.\n";
}

bool Pursue::ExecuteMessage(Agent & agt, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	if(agt.pl_inv.getTime() > 0){
							//don't kill agent cause he's invincible
							return true;
						}
						cout << "I killed you sucka.\n";
						agt.GetFSM()->ChangeState(Die::GetInstance());
						return true;
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}


//methods for Hide
Hide* Hide::GetInstance(){

  static Hide only_inst;

  return &only_inst;
}

void Hide::Enter(Agent & agt){
	agt.getPathList().clear();

	agt.newTargetLocation(agt.getMyCoverObject()->getCoverPosition(agt.getIt()));
	cout << "Entering Hide state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Hide::Execute(Agent & agt, const irr::ITimer* timer){
	

	//agt.getPathList().clear();
	//agt.createPatrolRoute(agt.getGraph());
	//agt.GetFSM()->ChangeState(Patrol::GetInstance());

	static bool there = false;//false;//temp
///	cout << "Executing Hide state.\n";


	
	double agtAngle = vectorAngle((agt.getPosition() - agt.getMyCoverObject()->getPosition()).normalize()); 
	double r =agt.getMyCoverObject()->getBoundaryRadius()+10;



	//agt.getPathList().push_back(agt.getMyCoverObject()->getCoverPosition(agt.getIt()));
	
	if(!there &&(agt.getMyCoverObject()->getPosition() - agt.getSceneNode()->getPosition()).getLength() < r){
	agt.getPathList().clear();

	irr::scene::ISceneNode* a = agt.smgr->addSphereSceneNode(5);
	a->setPosition(agt.getPosition());

	//agt.setPosition(vector3df(r*cos(agtAngle),agt.getPosition().Y, r*sin(agtAngle)));
	there = true;
	//std::cout<<"THERE\n";
	}

	if(!there)agt.walk(agt.followPath(timer));
	else if(there){
	double ANGULARVELOCITY = .1 / r;

	double timeElapsed = agt.getUpdateTimeIncrement();

	double angle1 = agtAngle;
	double angle2 =  vectorAngle((agt.getMyCoverObject()->getCoverPosition(agt.getIt()) - agt.getMyCoverObject()->getSceneNode()->getPosition()).normalize()); 

double transl = 0;

	if( fabs(angle1 - angle2) < fabs(angle2 - angle1)){
	
		transl = (angle1 - angle2) /  fabs(angle1 - angle2);

	}else{
	
		transl = (angle2 - angle1) / fabs(angle2- angle1);
	}


	transl = (angle2 - angle1);
	transl = transl / fabs(transl);
	if(fabs(angle2 - angle1) > PI){transl*=-1;}

	//if( agtAngle > angle2){transl = 1;}
	//if(agtAngle < angle2){transl = -1;}
	//if(agtAngle == angle2){transl = 0;}


	//transl = (angle2 - agtAngle) / fabs(angle2 - agtAngle);
	double newAngle = agtAngle + (ANGULARVELOCITY * timeElapsed * transl);

	//std::cout<<"AV * T:"<<(ANGULARVELOCITY*timeElapsed)<<std::endl;

//	newAngle = fmod(newAngle, 2*PI);
//	if(newAngle < 0){
//	
//		newAngle = 2*PI - fabs(newAngle);
//
//	}

	irr::core::vector3df newPos = agt.getMyCoverObject()->getSceneNode()->getPosition() + vector3df(r * cos(newAngle), agt.getPosition().Y - agt.getMyCoverObject()->getSceneNode()->getPosition().Y, r*sin(newAngle)); ;


	//std::cout<<"oldAngle:"<<agtAngle<<" newAngle:"<<newAngle<<" transl:"<<transl<<" angular vel:"<<ANGULARVELOCITY<<" TARGETANGLE "<<angle2<<"\n";
	std::cout<<radiansToDegrees(newAngle)<<std::endl;


	agt.setPosition(newPos);
	}


//agt.walk(agt.followPath(timer));


	
	

}

void Hide::Exit(Agent & agt){
	cout << "Exiting Hide state.\n";
}

bool Hide::ExecuteMessage(Agent & agt, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	if(agt.pl_inv.getTime() > 0){
							//don't kill agent cause he's invincible
							return true;
						}
						cout << "I killed you sucka.\n";
						agt.GetFSM()->ChangeState(Die::GetInstance());
						return true;
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}


//methods for Flee
Flee* Flee::GetInstance(){

  static Flee only_inst;

  return &only_inst;
}

void Flee::Enter(Agent & agt){
	cout << "Entering Flee state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Flee::Execute(Agent & agt, const irr::ITimer* timer){
	cout << "\nExecuting Flee state.\n";

	if(agt.getIt()){
	//agt.walk(2*agt.avoid(agt.getIt())+ 10*agt.wallAvoidance());
	agt.walk(agt.avoid(agt.getIt())+ agt.wallAvoidance());
	}

	//put ChangeState shit here in if conditions
}

void Flee::Exit(Agent & agt){
	cout << "Exiting Flee state.\n";
}

bool Flee::ExecuteMessage(Agent & agt, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	if(agt.pl_inv.getTime() > 0){
							//don't kill agent cause he's invincible
							return true;
						}
						cout << "I killed you sucka.\n";
						agt.GetFSM()->ChangeState(Die::GetInstance());
						return true;
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}


//methods for Act_Orb
Act_Orb* Act_Orb::GetInstance(){

  static Act_Orb only_inst;

  return &only_inst;
}

void Act_Orb::Enter(Agent & agt){
	cout << "Entering Act_Orb state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Act_Orb::Execute(Agent & agt, const irr::ITimer* timer){
	cout << "Executing Act_Orb state.\n";

	//put ChangeState shit here in if conditions
}

void Act_Orb::Exit(Agent & agt){
	cout << "Exiting Act_Orb state.\n";
}

bool Act_Orb::ExecuteMessage(Agent & agt, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	if(agt.pl_inv.getTime() > 0){
							//don't kill agent cause he's invincible
							return true;
						}
						cout << "I killed you sucka.\n";
						agt.GetFSM()->ChangeState(Die::GetInstance());
						return true;
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}




Die* Die::GetInstance(){
	static Die only_inst;
	return &only_inst;

}
 
void Die::Enter(Agent & agt){

	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setMD2Animation(scene::EMAT_DEATH_FALLBACKSLOW);
	
	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setLoopMode(false);

	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setAnimationSpeed(20);
	agt.getPathList().clear();
	
	cout<<"cleared";
	agt.setSeekTarget(((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->getPosition());
	
	agt.getSceneNode()->setPosition(agt.getSceneNode()->getPosition() + vector3df(0,20,0));
	


}

void Die::Execute(Agent & agt, const irr::ITimer* timer){
	//int frameCount = agt.getSceneNode()
	//std::cout<<"\nExecuting die state\n";  
	if(
	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->getFrameNr()
	>= ((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->getEndFrame()){
	

		agt.getSceneNode()->setVisible(false);
		//((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setRotation(vector3df(0, 0, 75));

		//agt.getSceneNode()->setPosition( agt.getSceneNode()->getPosition() - vector3df(0, 40,0));
	}
	
}

void Die::Exit(Agent & agt){
	cout << "I'm about to reset the time.\n";
	agt.pl_inv.setTime(10000);
	
	agt.getSceneNode()->setVisible(true);
		
	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setAnimationSpeed(60);
	
	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setLoopMode(true);

	
	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setMD2Animation(scene::EMAT_STAND);
	
}

bool Die::ExecuteMessage(Agent & agt, const Message * msg){
	
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;

		case KTC_REVIVE:	agt.GetFSM()->ChangeState(Flee::GetInstance());
							return true;
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}


Wait* Wait::GetInstance(){
	static Wait only_inst;
	return &only_inst;

}
 
void Wait::Enter(Agent & agt){
	//set anim to stand
}

void Wait::Execute(Agent & agt, const irr::ITimer* timer){
	
	if(agt.getTimer().getTime() >= 10000)
		agt.GetFSM()->ChangeState(Patrol::GetInstance());
}

void Wait::Exit(Agent & agt){

}

bool Wait::ExecuteMessage(Agent & agt, const Message * msg){

	//false always gets returned here because we don't want to handle any messages in the wait state
	return false;
}
