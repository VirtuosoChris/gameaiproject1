#include "GameStates.h"
#include "ktcGame.h"
#include "MessageHandler.h"

#include <iostream>
using std::cout;

//methods for PrePlay
PrePlay* PrePlay::getInstance(){

  static PrePlay only_inst;

  return &only_inst;
}

void PrePlay::Enter(ktcGame & game){
	cout << "Entering PrePlay state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void PrePlay::Execute(ktcGame & game, const irr::ITimer* timer){
	cout << "Executing PrePlay state.\n";

	//put ChangeState shit here in if conditions
}

void PrePlay::Exit(ktcGame & game){
	cout << "Exiting PrePlay state.\n";
}

bool PrePlay::ExecuteMessage(ktcGame & game, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_START_GAME:	cout << "Starting the game.\n";
						return true;
		case KTC_END_GAME:	cout << "Ending the game\n";
							return true;
	}
	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}


//methods for Play
Play* Play::getInstance(){

  static Play only_inst;

  return &only_inst;
}

void Play::Enter(ktcGame & game){
	cout << "Entering Play state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Play::Execute(ktcGame & game, const irr::ITimer* timer){
	cout << "Executing Play state.\n";

	//put ChangeState shit here in if conditions
}

void Play::Exit(ktcGame & game){
	cout << "Exiting Play state.\n";
}

bool Play::ExecuteMessage(ktcGame & game, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_PAUSE_GAME:	cout << "Starting the game.\n";
						return true;
		case KTC_END_GAME:	cout << "Ending the game\n";
							return true;
	}
	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}

//methods for Pause
Pause* Pause::getInstance(){

  static Pause only_inst;

  return &only_inst;
}

void Pause::Enter(ktcGame & game){
	cout << "Entering Pause state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void Pause::Execute(ktcGame & game, const irr::ITimer* timer){
	cout << "Executing Pause state.\n";

	//put ChangeState shit here in if conditions
}

void Pause::Exit(ktcGame & game){
	cout << "Exiting Pause state.\n";
}

bool Pause::ExecuteMessage(ktcGame & game, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_RESUME_GAME:	cout << "Starting the game.\n";
						return true;
		case KTC_END_GAME:	cout << "Ending the game\n";
							return true;
	}
	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}

//methods for RoundBreak
RoundBreak* RoundBreak::getInstance(){

  static RoundBreak only_inst;

  return &only_inst;
}

void RoundBreak::Enter(ktcGame & game){
	cout << "Entering RoundBreak state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void RoundBreak::Execute(ktcGame & game, const irr::ITimer* timer){
	cout << "Executing RoundBreak state.\n";

	//put ChangeState shit here in if conditions
}

void RoundBreak::Exit(ktcGame & game){
	cout << "Exiting RoundBreak state.\n";
}

bool RoundBreak::ExecuteMessage(ktcGame & game, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_BEGIN_ROUND:	cout << "Starting the game.\n";
						return true;
		case KTC_END_GAME:	cout << "Ending the game\n";
							return true;
	}
	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}

//methods for EndersGame
EndersGame* EndersGame::getInstance(){

  static EndersGame only_inst;

  return &only_inst;
}

void EndersGame::Enter(ktcGame & game){
	cout << "Entering EndersGame state.\n";
	//use MsgHandler->postMessage() here to post a message to all other players (use for loop or some shit)
}

void EndersGame::Execute(ktcGame & game, const irr::ITimer* timer){
	cout << "Executing EndersGame state.\n";

	//put ChangeState shit here in if conditions
}

void EndersGame::Exit(ktcGame & game){
	cout << "Exiting EndersGame state.\n";
}

bool EndersGame::ExecuteMessage(ktcGame & game, const Message *msg){
	switch(msg->messageType){
		//put whatever message types you need here, these are just some examples until we change shit up
		case KTC_END_GAME:	cout << "Ending the game\n";
							return true;
	}
	//false gets returned if no cases we're matched (we couldn't handle the message)
	return false;
}

