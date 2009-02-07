//TODO: TEST THIS MESSAGE CLASS's OPERATORS ERROR PRONE

#include "Message.h"

const int OFFSET_TIME_MILLIS = 10;


bool Message::operator==( Message m)const{

	int a = postTime - 
		m.postTime;
	if(a < 0)a=-a;
	if(a<=OFFSET_TIME_MILLIS)return true;
	return false;
}

bool Message::operator>( Message m)const{

	return (!operator==(m) && postTime - m.postTime < 0);
}


bool Message::operator<( Message m)const{
	return (!operator==(m) && postTime - m.postTime > 0);
}


bool Message::operator>=( Message m)const{

	if( operator==(m))return true;
	
	if( postTime - m.postTime >0)
		return true;

		return false;
}


bool Message::operator<=( Message m)const{

	if( operator==(m))return true;
	
	if( postTime - m.postTime <0)
		return true;

		return false;

}