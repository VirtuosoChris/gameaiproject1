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

//#define SPAWN_POINT_CREATOR

class ktcGame:public GameEntity{

	Model CHUCKIE;
	Model CARTMAN;
	Model CYBERDEMON;

	std::vector<irr::core::vector3df> spawnPointList;
	
irr::scene::ICameraSceneNode* cam2;

	Agent agent2;
	//Agent agent3;

	
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
	virtual bool processMessage(const Message*);
	~ktcGame();

};


#endif