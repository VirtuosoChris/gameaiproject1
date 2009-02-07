#ifndef IRRLICHT
#define IRRLICHT
#include <irrlicht.h>
#endif


class GameEntity;
//class Message;

#include "Message.h"
//#include "GameEntity.h"

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