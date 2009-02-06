#ifndef IRRLICHT
#include <irrlicht.h>
#define IRRLICHT
#endif


#include <set>
#include "messagehandler.h"

		 
MessageHandler::MessageHandler(){

}
 

MessageHandler::~MessageHandler(){

}



void MessageHandler::postMessage(Message_Type type, int delay, GameEntity *sender, GameEntity *receiver,irr::ITimer* timer){

Message* m = (Message*)malloc(sizeof(Message));
m->messageType = type;
m->sender = sender;
m->receiver = receiver;
m->postTime = delay + timer->getTime();

if(delay ==0){
deliverMessage(m);
}else
messageQueue.insert(*m);

}
	

int MessageHandler::update(irr::ITimer* timer){

	while(messageQueue.begin()->postTime < (int)timer->getTime()){

		deliverMessage(&*messageQueue.begin());

		messageQueue.erase(messageQueue.begin());

	}

	return 0;
}



void MessageHandler::deliverMessage(Message* m){
	m->receiver->processMessage(m);
}

 MessageHandler* MessageHandler::getInstance(){
		 static MessageHandler instance;
		 return &instance;
}
