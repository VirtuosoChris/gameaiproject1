#include "GameEntity.h"


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