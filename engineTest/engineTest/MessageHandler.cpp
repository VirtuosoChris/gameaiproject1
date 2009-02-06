#ifndef IRRLICHT
#include <irrlicht.h>
#endif
#include <set>
#include "messagehandler.h"

		 
//class GameEntity;
//class MessageHandler;
//class  Message;


 

MessageHandler::MessageHandler(){

}
 

MessageHandler::~MessageHandler(){

}



void postMessage(Message_Type type, double delay, GameEntity *sender, GameEntity *receiver){
//TO DO
}
	

int update(){
//TO DO	 
}



void MessageHandler::deliverMessage(Message* m){
//TO DO
}

static MessageHandler* MessageHandler::getInstance(){
		 static MessageHandler instance;
		 return &instance;
}
