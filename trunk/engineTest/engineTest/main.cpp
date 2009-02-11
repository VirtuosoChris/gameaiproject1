
//good design would be of the form, make a chuckie at (3,3,0) <with these ai paramaters> and that's it... no worrying about scene nodes or collision detection

//do destructors/constructors
//singleton stuff; copy constructor, assignment
//free message memory
//entities interact (animation, kewl eh?);

//replace exit 0's with proper exiting

#ifndef IRRLICHT
#include <irrlicht.h>
#endif

#include <vector>
#include <string>

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

bool ENABLE_DEBUG_OUTPUT = true;


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
Model CYBERDEMON = createModel("../media/cyber.md2","../media/cyber.pcx",device,2.0f);


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


 //create the laser pointer particle
 scene::IBillboardSceneNode *billboard = smgr->addBillboardSceneNode();
 billboard->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
 billboard->setMaterialTexture(0,driver->getTexture("../media/particle.bmp"));
 billboard->setMaterialFlag(video::EMF_LIGHTING, false);
 billboard->setMaterialFlag(video::EMF_ZBUFFER,false);
 billboard->setSize(core::dimension2d<f32>(20.0f, 20.0f));


 core::line3d<f32> line;
 core::vector3df intersection;
 core::triangle3df triangle;
 

 //add the agents to the agent list
 entities.push_back(&playerControlledAgent);
 entities.push_back(&agent2);
 

//add collision to each game entity in the agent list
 for(int i = 0; i < (int)entities.size(); i++){
	 entities[i]->createCollisionAnimator(selector,smgr);
 
 }


/*******************************************************/
/***************GAME UPDATE LOOP************************/
/*******************************************************/
	while(device->run()){
		
		for(int i = 0; i < (int)entities.size();i++){
			if(entities[i]){
			entities[i]->update(device->getTimer());
			}
		}

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
 

		 line.start = camera->getPosition();
		 line.end = line.start + (camera->getTarget() - line.start).normalize() * 5000.0f;
 
		billboard->setVisible(true);
		 
		if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle))
			billboard->setPosition(intersection);
		 else{
			 billboard->setVisible(false);
		 }


		 

		//Draw everything
		 driver->beginScene(true, true, video::SColor(255,100,101,140));
			smgr->drawAll();  //draw 3d objects
			guienv->drawAll();//draw gui components
		 driver->endScene();//end drawing


		
	 	 
	 }


	 device->drop();

return 0;
}