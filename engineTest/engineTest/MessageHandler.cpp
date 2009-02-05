#include <irrlicht.h>
#include <set>
#include "messagehandler.h"

enum Message_Type {MSG_ACTIVATE, MSG_ROTATE_LEFT, MSG_ROTATE_RIGHT, MSG_MOVE_FORWARD, MSG_MOVE_BACKWARD};
		 
//class GameEntity;
//class MessageHandler;
//class  Message;

static const  float OFFSET_TIME_MILLIS= 10.0;//why can't i initialize this inside a class? wtf

class Message{

	double postTime;
		Message_Type messageType;
		GameEntity *sender;
		GameEntity *receiver;

	public:
      bool operator==(Message);
	  bool operator<(Message);
	  bool operator>(Message);
	  bool operator>=(Message);
	  bool operator<=(Message);
	  
 };

bool Message::operator==(Message m){

	double a = postTime - 
		m.postTime;
	if(a < 0)a=-a;
	if(a<=OFFSET_TIME_MILLIS)return true;
	return false;
}
 

 
class GameEntity{
	irr::core::vector3df position;
	double orientation;
	
	public:
	virtual void processMessage(Message*)=0;
};


static MessageHandler* MessageHandler::getInstance(){
		 static MessageHandler instance;
		 return &instance;
	 }
