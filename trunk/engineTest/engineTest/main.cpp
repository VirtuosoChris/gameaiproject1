
//good design would be of the form, make a chuckie at (3,3,0) <with these ai paramaters> and that's it... no worrying about scene nodes or collision detection

//do destructors/constructors
//singleton stuff; copy constructor, assignment
//free message memory
//entities interact (animation, kewl eh?);

//replace exit 0's with proper exiting

//todo : figure out what goes in which baseclass

#ifndef IRRLICHT
#include <irrlicht.h>
#endif

#include <vector>
#include <string>
#include <iostream>

#ifndef INPUTHANDLER
#include "InputHandler.h"
#endif


#ifndef SUBJECTAGENT
#include "SubjectAgent.h"
#endif

#ifndef MODEL
#include "Model.h"
#endif

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


using namespace irr;
using namespace gui;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;


bool ENABLE_DEBUG_OUTPUT = false;


Model createModel(const char* m, const char* s, IrrlichtDevice *d, double sc=1.0f){
 Model mod;
 mod.mesh = d->getSceneManager()->getMesh(m);
 mod.texture = d->getVideoDriver()->getTexture(s);
 mod.scale = sc;
 if(!(mod.mesh&&mod.texture))exit(0);
 return mod;
}


int main(int argc, char** argv){

	std::vector<Agent*> entities;

	GameEntity::setAgentList(&entities);

/*******************************************************/
/****************ENGINE SETUP***************************/
/*******************************************************/

 //create the irrlicht device
 //IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(1440,900), 32, false, true, true, InputHandler::getInstance());
 IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(800,600), 32, false, true, true, InputHandler::getInstance());
	if(device==NULL)return 1;

 //set the title of the window
 device->setWindowCaption(L"Game AI Assignment 1");
	
 //hide the cursor
 device->getCursorControl()->setVisible(false);

 //get the driver, scene manager, and gui environment objects
 video::IVideoDriver* driver = device->getVideoDriver();
 scene::ISceneManager* smgr = device->getSceneManager();
 gui::IGUIEnvironment* guienv = device->getGUIEnvironment();


/*************************************************************/
/****************LOAD IN MODELS*******************************/
/*************************************************************/
Model CHUCKIE = createModel("../media/chuckie.MD2","../media/Chuckie.pcx",device);
Model BOBAFETT = createModel("../media/bobafett.md2","../media/bobafett.pcx",device, 2.0f);
Model CARTMAN  = createModel("../media/ERIC.MD2","../media/ERIC.pcx",device, 1.5f);
Model CYBERDEMON = createModel("../media/cyber.md2","../media/cyber.pcx",device,3.0f);

/*******************************************************/
/***************CREATE GAME ENTITIES********************/
/*******************************************************/

 SubjectAgent playerControlledAgent(CHUCKIE,core::vector3df(75,0,75),smgr);
 Agent agent2(CARTMAN,core::vector3df(116,128,845),smgr );
 Agent agent3(BOBAFETT, core::vector3df(124, 185, -834), smgr);


 /****************************/
 /*******LOAD THE MAP*********/
 /****************************/
 //load the pk3 file containing the .bsp map file into the engine file system
 device->getFileSystem()->addZipFileArchive("../media/map-20kdm2.pk3");
 
 //get the mesh from the map bsp file
 scene::IAnimatedMesh *map  = smgr->getMesh("20kdm2.bsp");
  if(!map)return 1;
 
 //add a scene node for the map
 scene::ISceneNode *mapNode = NULL;
 mapNode = smgr->addOctTreeSceneNode(map->getMesh(0), 0, -1, 1024);
 if(!mapNode)return 1;

 //translate the map a bit since it wasn't modeled around the origin because artists are morons
 mapNode->setPosition(core::vector3df(-1300,-144,-1249));
 //mapNode->setScale(core::vector3df(1000,1000,1000));



 /**************************************************/
 /***************CREATE THE CAMERA******************/
 /**************************************************/

 scene::ICameraSceneNode *camera = 
	 smgr->addCameraSceneNodeFPS();

 camera->setPosition(core::vector3df(30,30,30));


 /***************************************************/
 /****************** SET UP COLLISIONS***************/
 /***************************************************/

 //create a triangle selector object for the map
 scene::ITriangleSelector*  selector = NULL;
 selector = smgr->createOctTreeTriangleSelector(map->getMesh(0), mapNode,128);
 if(!selector)return 1;
 mapNode->setTriangleSelector(selector);


//create a collision node animator and apply it to the camera
 scene::ISceneNodeAnimator *nodeAnimator = 
	smgr->createCollisionResponseAnimator(selector,//geometry for collision 
	camera, //scene node to apply collision to/	
	core::vector3df(30,50,30),//collision volume radii
	core::vector3df(0,0,0),//gravity 
	core::vector3df(0,30,0)); //collision volume position
if(!nodeAnimator)return 1;
 camera->addAnimator(nodeAnimator);
 nodeAnimator->drop();



 //add the agents to the agent list
 entities.push_back(&playerControlledAgent);
 entities.push_back(&agent2);
 entities.push_back(&agent3);
 

//add collision to each game entity in the agent list
 for(int i = 0; i < (int)entities.size(); i++){
	 entities[i]->createCollisionAnimator(selector,smgr);
 
 }

/*******************************************************/
/***************GUI SETUP*******************************/
/*******************************************************/
 //gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
//Sensor2
guienv->addStaticText(L"Sensor 2 Output:", rect<s32>(25,400,300,415), true, true, 0, -1, true);
IGUIListBox * s2box = guienv->addListBox(rect<s32>(25, 420, 300, 590), 0, -1, true);
s2box->setAutoScrollEnabled(true);

//PieSensor
guienv->addStaticText(L"PieSensor Output:", rect<s32>(310,400,500,415), true, true, 0, -1, true);
IGUIListBox * piebox = guienv->addListBox(rect<s32>(310, 420, 500, 590), 0, -1, true);
piebox->setAutoScrollEnabled(true);



/*******************************************************/
/***************GAME UPDATE LOOP************************/
/*******************************************************/
	while(device->run()){
		
		//update all entities
		for(int i = 0; i < (int)entities.size();i++){
			if(entities[i]){
			entities[i]->update(device->getTimer());
			}
		}

		//clear piesensor output
		piebox->clear();

		//output piesensor data
		//num_slices*2 = number of sections (elements in array)
		for(int i = 0; i < (playerControlledAgent.pie->num_slices)*2 ; i++)
		{
			stringw pieSection(i+1);
			stringw numAgents(playerControlledAgent.pie->areas[i]);
			stringw mainstring = L"Pie Section: ";
			mainstring+=pieSection;
			mainstring+= L"      NumAgents: ";
			mainstring+=numAgents;
			piebox->addItem(mainstring.c_str());
		}

		//clear sensor2 output
		s2box->clear();

		//the chuckman
		stringw chuckMan;

		//output sensor2 data
		for(int x = 0 ; x < playerControlledAgent.s2d.size() ; x++)
		{
			int id = playerControlledAgent.s2d[x]->agentID;
			double distance = playerControlledAgent.s2d[x]->relDistance;
			double heading = playerControlledAgent.s2d[x]->relHeading;
			stringw idstring(id);
			stringw bstring(distance);
			stringw hstring(heading);
			stringw mainstring = L"AgentID: ";
			mainstring+=idstring;
			mainstring+= L" Distance: ";
			mainstring+=bstring;
			mainstring+= L" Heading: ";
			mainstring+=hstring;
			s2box->addItem(mainstring.c_str());
			stringw chuckPX(playerControlledAgent.position.X);
			stringw chuckPY(playerControlledAgent.position.Y);
			stringw chuckPZ(playerControlledAgent.position.Z);
			//Modify based on increasing orientation
			double self_angle = playerControlledAgent.orientation;
			double remainder = (int)(self_angle/360);
			remainder *= 360;
			double mod = self_angle - abs(remainder);
			self_angle = mod;

			stringw chuckOr(self_angle);
			chuckMan = L"Pos X: ";
			chuckMan+=chuckPX;
			chuckMan+= L" Y: ";
			chuckMan+=chuckPY;
			chuckMan+= L" Z: ";
			chuckMan+=chuckPZ;
			chuckMan+= L" Orient: ";
			chuckMan+=chuckOr;
		}

		//Add Chuck's stats to debug output
		s2box->addItem(chuckMan.c_str());

		//if the mouse is clicked, create a new agent at the camera's current position
		//TO DO!!! //THIS CREATES AN AGENT FOR EVERY TICK THE KEY IS PRESSED, BAD
		
		if(InputHandler::getInstance()->unprocessedMouseMessageLMB){
		Agent* ap = new Agent(CYBERDEMON, camera->getPosition(), smgr);
			ap->createCollisionAnimator(selector,smgr);
			if(ap==NULL)return 1;
			else 
			entities.push_back(ap);	
			InputHandler::getInstance()->unprocessedMouseMessageLMB = false;
		}
		
		//rig the window title bar to show the current camera position
		core::stringw str = L"";  		 
		 str+="(";
		 str+= camera->getPosition().X;
		 str+= ",";
		 str+= camera->getPosition().Y;
		 str+= ",";
		 str+= camera->getPosition().Z;
		 str+= ")";
		 device->setWindowCaption(str.c_str());
 

		 //If the Debug output is enabled, display a box with some stuff


		//Draw everything
		driver->beginScene(true, true, video::SColor(255,100,101,140));
		smgr->drawAll();  //draw 3d objects
		
		//Only draw GUI components if Debug output is enabled
		if(ENABLE_DEBUG_OUTPUT)
			guienv->drawAll();

		driver->endScene();//end drawing 
	 }

	 device->drop();

return 0;
}