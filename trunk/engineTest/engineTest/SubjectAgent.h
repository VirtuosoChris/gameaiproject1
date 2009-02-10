#include "irrlicht.h"
#include "Agent.h"
class SubjectAgent:public Agent{


protected:
bool moving;

public:
virtual void update(irr::ITimer*);
//SubjectAgent(irr::scene::IAnimatedMeshSceneNode* n, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f));



SubjectAgent(Model m, irr::core::vector3df p = irr::core::vector3df(0.0f,0.0f,0.0f),irr::scene::ISceneManager* mgr = NULL);


};