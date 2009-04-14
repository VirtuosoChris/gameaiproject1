#ifndef KTCGAME
#define KTCGAME

#include "GameEntity.h"
#include "Model.h"
#include "Agent.h"
#include "canEntity.h"
#include "gunEntity.h"
#include "InputHandler.h"
#include "MessageHandler.h"
#include "Message.h"
#include "mapGraph.h"
#include "coverObject.h"
#include "gameHUD.h"

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

	//Irrlicht Devices
	irr::IrrlichtDevice *device;
	irr::scene::ISceneManager* smgr;
	irr::gui::IGUIEnvironment* gameUI;

	//Camera Scene Node
	scene::ICameraSceneNode *camera;

	//HUD
	gameHUD* display;

	canEntity can;
	gunEntity gun;

	mapGraph graph;

	int playerScores[5];

	std::vector<coverObject*> coverObjectList;	 //scene::ICameraSceneNode *camera;




public:

	ktcGame(IrrlichtDevice *device,irr::scene::ITriangleSelector*, gameHUD* display);
	virtual void update(irr::ITimer*);
	virtual bool processMessage(const Message*);
	virtual irr::scene::ISceneNode* pointing();  
	virtual irr::scene::ISceneNode* GetCan(irr::scene::ISceneNode* );
	virtual irr::scene::ISceneNode* GetAgent(irr::scene::ISceneNode* );

	std::list<irr::core::vector3df> generateDefenseArc(double startAngleRadians, double endAngleRadians, double radius = 45.0f, double nodeCount = 6); 

	~ktcGame();
};


#endif