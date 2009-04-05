#ifndef KTCGAME
#define KTCGAME

#include "gameEntity.h"
#include "model.h"
#include "agent.h"
#include "canEntity.h"
#include "gunEntity.h"
#include "inputHandler.h"
#include "MessageHandler.h"
#include "Message.h"
#include "mapGraph.h"

class ktcGame:public GameEntity{

	Model CHUCKIE;
	Model CARTMAN;
	Model CYBERDEMON;

	
	Agent agent2;

	
	std::vector<Agent*> entities;

	irr::IrrlichtDevice *device;
	irr::scene::ISceneManager* smgr;
	scene::ICameraSceneNode *camera;

	canEntity can;
	gunEntity gun;

	mapGraph graph;


	 //scene::ICameraSceneNode *camera;

public:

	ktcGame(IrrlichtDevice *device,irr::scene::ITriangleSelector*);
	virtual void update(irr::ITimer*);
	virtual void processMessage(Message*);
	

};


#endif