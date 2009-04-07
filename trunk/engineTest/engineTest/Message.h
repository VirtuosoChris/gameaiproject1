
class GameEntity;

#ifndef MESSAGE
#define MESSAGE

#include "irrlicht.h"




enum Message_Type {KTC_ACTIVATE, KTC_KILL, KTC_REVIVE, KTC_SPOTTED, KTC_ENDROUND, KTC_BEGINROUND, KTC_PLAYER_LEFT_MOUSE_CLICK, KTC_PLAYER_RIGHT_MOUSE_CLICK};

class Message{	

public:
	
	int postTime;
	Message_Type messageType;
	GameEntity *sender;
	GameEntity *receiver;
	Message(){}
	Message(int, Message_Type, GameEntity *, GameEntity *);
	bool operator==( Message) const;
	bool operator<( Message) const;
	bool operator>( Message)const ;
	bool operator>=( Message)const;
	bool operator<=( Message)const;  
 };

#endif