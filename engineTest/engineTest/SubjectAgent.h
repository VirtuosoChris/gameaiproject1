#define SUBJECTAGENT

#include "irrlicht.h"

#ifndef AGENT
#include "Agent.h"
#endif

#include <vector>

class SubjectAgent:public Agent{


protected:
bool moving;
std::vector<irr::scene::IBillboardTextSceneNode*> feelerParticles;

public:
virtual void update(irr::ITimer*);
//SubjectAgent(irr::scene::IAnimatedMeshSceneNode* n, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f));



SubjectAgent(Model m, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f),irr::scene::ISceneManager* mgr = NULL);


virtual void updateSensor1();

};