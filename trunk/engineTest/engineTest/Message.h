class GameEntity;


#ifndef IRRLICHT
#define IRRLICHT
#include "irrlicht.h"
#endif



enum Message_Type {MSG_ACTIVATE, MSG_ROTATE_LEFT, MSG_ROTATE_RIGHT, MSG_MOVE_FORWARD, MSG_MOVE_BACKWARD};

class Message{


	
	public:

	int postTime;
	Message_Type messageType;
	GameEntity *sender;
	GameEntity *receiver;

      bool operator==( Message) const;
	  bool operator<( Message) const;
	  bool operator>( Message)const ;
	  bool operator>=( Message)const;
	  bool operator<=( Message)const;
	  
 };