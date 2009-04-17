#ifndef TIMER_H_
#define TIMER_H_

#include "GameEntity.h"

#include <iostream>
using std::cout;

class Timer : public GameEntity{
private:
	int timer;
	irr::u32 last_update;

public:
	virtual void update(const irr::ITimer*);
	virtual bool processMessage(const Message*);
	Timer(int t=0) : timer(t), last_update(0) {}
	void convert();
	int getTime(){ return timer; }
	void setTime(int t){
		cout << "I reset the time.\n";
		timer = t; 
	}
};

#endif
