#include <irrlicht.h>



#include <set>
#include "MessageHandler.h"

#ifndef GAMEENTITY
#include "GameEntity.h"
#endif
		 
MessageHandler::MessageHandler(){

}
 

MessageHandler::~MessageHandler(){

}



void MessageHandler::postMessage(Message_Type type, int delay, GameEntity *sender, GameEntity *receiver,irr::ITimer* timer){

Message* m = new Message;
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

		//deliverMessage(&*messageQueue.begin());
	    deliverMessage(const_cast<Message*>(&*messageQueue.begin()));
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
