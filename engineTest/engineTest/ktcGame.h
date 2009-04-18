//make minimum spanning tree method static?

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
#include "StateMachine.h"
#include "player.h"

//#define SPAWN_POINT_CREATOR
enum debugMode{NONE, MINSPANNINGTREE, FULLGRAPH};
class ktcGame:public GameEntity{

private:

	//vector of the four AI players and the user as an array of GamePlayer references
	static std::vector<GamePlayer *> playerList;
	
	void RoundRobin(std::vector<GamePlayer *> plst);

	Timer round_time;

	int dMode;
	Model CHUCKIE;
	Model CARTMAN;
	Model CYBERDEMON;

	std::vector<irr::core::vector3df> spawnPointList;
	
	player plyr;
	Agent agent2;
	//Agent agent3;

	
	std::vector<Agent*> entities;

	//Irrlicht Devices
	irr::IrrlichtDevice *device;
	irr::scene::ISceneManager* smgr;
	irr::gui::IGUIEnvironment* gameUI;

	//HUD
	gameHUD* display;

	canEntity can;

	mapGraph graph;

	int playerScores[5];


	std::vector<coverObject*> coverObjectList;	 //scene::ICameraSceneNode *camera;


public:


	void displayMinSpanningTree(){dMode = MINSPANNINGTREE; }	
	void disableDebugOutput(){dMode = NONE; }
	void displayFullGraph(){dMode = FULLGRAPH;}

	ktcGame(IrrlichtDevice *device,irr::scene::ITriangleSelector*);	virtual void update(const irr::ITimer*);
	virtual bool processMessage(const Message*);
	virtual irr::scene::ISceneNode* pointing();  
	virtual irr::scene::ISceneNode* GetCan(irr::scene::ISceneNode* );
	virtual irr::scene::ISceneNode* GetAgent(irr::scene::ISceneNode* );

	std::list<irr::core::vector3df> generateDefenseArc(double startAngleRadians, double endAngleRadians, double radius = 45.0f, double nodeCount = 6); 

	~ktcGame();
};


#endif