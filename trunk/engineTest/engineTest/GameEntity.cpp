#include "GameEntity.h"
std::vector<Agent*>* GameEntity::agentList;

void GameEntity::setVelocity(irr::core::vector3df vel){
		   velocity = vel;
}


GameEntity::GameEntity(){

}


GameEntity::~GameEntity(){

}

irr::core::vector3df GameEntity::getPosition(){
return position;
}



void GameEntity::setAgentList(std::vector<Agent*>* abc){

	agentList = abc;
}
