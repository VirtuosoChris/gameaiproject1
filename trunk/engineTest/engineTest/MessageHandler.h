#define MESSAGEHANDLER

#include <irrlicht.h>



class GameEntity;
//class Message;

#ifndef MESSAGE
#include "Message.h"
#endif

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