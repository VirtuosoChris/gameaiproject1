#include "GameEntity.h"

class Agent:public GameEntity{

virtual void update();
virtual void processMessage(Message*);

};