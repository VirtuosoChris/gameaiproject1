#include "Agent.h"
#include "InputHandler.h"

void Agent::update(){

}


void Agent::processMessage(Message*){

}

Agent::Agent(irr::scene::IAnimatedMeshSceneNode* a, irr::core::vector3df p)
:mynodep(a),position(p)
{
;
}

Agent::~Agent(){

}