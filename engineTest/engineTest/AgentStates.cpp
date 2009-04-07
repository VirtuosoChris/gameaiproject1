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

void Defend::Execute(Agent & agt){
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
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Patrol::Execute(Agent & agt){
	cout << "Executing Patrol state.\n";

	//put ChangeState shit here in if conditions
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

void Pursue::Execute(Agent & agt){
	cout << "Executing Persue state.\n";

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

void Hide::Execute(Agent & agt){
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

void Flee::Execute(Agent & agt){
//	cout << "Executing Flee state.\n";

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

void Act_Orb::Execute(Agent & agt){
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

	agt.mynodep->setMD2Animation(scene::EMAT_DEATH_FALLFORWARD);
	
	agt.mynodep->setLoopMode(false);
	agt.getPathList().clear();
	cout<<"cleared";
	agt.setSeekTarget(agt.mynodep->getPosition());
	//agt.newTargetLocation(agt.mynodep->getPosition(),agt.graph);

}

void Die::Execute(Agent & agt){}

void Die::Exit(Agent & agt){}

bool Die::ExecuteMessage(Agent & agt, const Message * msg){
	/*
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_KILL:	cout << "I killed you sucka.\n";
						return true;
		case KTC_SPOTTED:	cout << "I've been spotted, gotta run!\n";
							return true;
	}

	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
	*/
	return true;
}
