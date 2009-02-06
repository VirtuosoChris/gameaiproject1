#ifndef IRRLICHT
#include <irrlicht.h>
#define IRRLICHT
#endif


#include <set>
#include "messagehandler.h"

		 
//class MessageHandler;
//class  Message;


 

MessageHandler::MessageHandler(){

}
 

MessageHandler::~MessageHandler(){

}



void MessageHandler::postMessage(Message_Type type, double delay, GameEntity *sender, GameEntity *receiver){

Message* m = (Message*)malloc(sizeof(Message));
m->messageType = type;
m->sender = sender;
m->receiver = receiver;
m->postTime = delay + CURRENT_TIME;

if(delay ==0){
deliverMessage(m);
}

}
	

int MessageHandler::update(){
//TO DO	 
}



void MessageHandler::deliverMessage(Message* m){
	m->receiver->processMessage(m);
}

 MessageHandler* MessageHandler::getInstance(){
		 static MessageHandler instance;
		 return &instance;
}
