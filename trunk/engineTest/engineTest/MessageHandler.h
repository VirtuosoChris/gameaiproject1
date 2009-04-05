#ifndef MESSAGEHANDLER
#define MESSAGEHANDLER

#include <irrlicht.h>
#include <set>


class GameEntity;
//class Message;

#include "Message.h"

class MessageHandler{
 
 std::set<Message> messageQueue;
 
 MessageHandler();
 ~MessageHandler();

 void deliverMessage(Message* m);
	 	
 public: 
	 
	 void postMessage(Message_Type type, int delay, GameEntity *sender, GameEntity *receiver,irr::ITimer* timer);
	
	 int update(irr::ITimer*); 

	 static MessageHandler *getInstance();

			
};

#endif