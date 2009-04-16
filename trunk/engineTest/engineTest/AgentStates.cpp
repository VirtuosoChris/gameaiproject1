#include "AgentStates.h"
#include "Agent.h"
#include "MessageHandler.h"

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
		case KTC_KILL:	cout << "I killed you sucka.\n";
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
		case KTC_KILL:	cout << "I killed you sucka.\n";
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
	agt.walk(2*agt.seek(agt.getSpottedAgent()->getPosition())+ agt.wallAvoidance());
	}

	//put ChangeState shit here in if conditions
}

void Pursue::Exit(Agent & agt){
	cout << "Exiting Persue state.\n";
}

bool Pursue::ExecuteMessage(Agent & agt, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	cout << "I killed you sucka.\n";
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
	cout << "Entering Hide state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Hide::Execute(Agent & agt, const irr::ITimer* timer){
	cout << "Executing Hide state.\n";

	//put ChangeState shit here in if conditions
}

void Hide::Exit(Agent & agt){
	cout << "Exiting Hide state.\n";
}

bool Hide::ExecuteMessage(Agent & agt, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	cout << "I killed you sucka.\n";
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
//	cout << "Executing Flee state.\n";

	if(agt.getIt()){
	agt.walk(2*agt.avoid(agt.getIt())+ 10*agt.wallAvoidance());
	}

	//put ChangeState shit here in if conditions
}

void Flee::Exit(Agent & agt){
	cout << "Exiting Flee state.\n";
}

bool Flee::ExecuteMessage(Agent & agt, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	cout << "I killed you sucka.\n";
						agt.GetFSM()->ChangeState(Die::getInstance());
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
		case KTC_KILL:	cout << "I killed you sucka.\n";
						return true;
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}




Die* Die::getInstance(){
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
	//std::cout<<"UADJFHKDHF\n";  
	if(
	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->getFrameNr()
	>= ((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->getEndFrame()){
	
		//std::cout<<"laksjd\n";

		agt.getSceneNode()->setVisible(false);
		//((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setRotation(vector3df(0, 0, 75));

		//agt.getSceneNode()->setPosition( agt.getSceneNode()->getPosition() - vector3df(0, 40,0));
	}
	
}

void Die::Exit(Agent & agt){

		agt.getSceneNode()->setVisible(true);
		
	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setAnimationSpeed(60);
	
	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setLoopMode(true);

	
	((irr::scene::IAnimatedMeshSceneNode*)agt.getSceneNode())->setMD2Animation(scene::EMAT_STAND);
	
}

bool Die::ExecuteMessage(Agent & agt, const Message * msg){
	
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	cout << "I killed you sucka.\n";
						return true;
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;

		case KTC_REVIVE: 

			agt.GetFSM()->ChangeState(Flee::GetInstance());
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
	
	return true;
}
