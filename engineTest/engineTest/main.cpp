//do destructors/constructors
//singleton stuff; copy constructor, assignment
//free message memory
//entities interact (animation, kewl eh?);

#ifndef IRRLICHT
#include <irrlicht.h>
#endif

#include <vector>

#include "InputHandler.h"
#include "SubjectAgent.h"
#include "Model.h"


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


using namespace irr;


//good design would be of the form, make a chuckie at (3,3,0) <with these ai paramaters>


int main(int argc, char** argv){

	std::vector<GameEntity*> entities;

/*******************************************************/
/****************ENGINE SETUP***************************/
/*******************************************************/

 //create the irrlicht device
 IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(1280,1024), 32, false, true, false, InputHandler::getInstance());
 if(device==NULL)return 1;

 //set the title of the window
 device->setWindowCaption(L"Game AI Assignment 1");
	
 //hide the cursor
 device->getCursorControl()->setVisible(false);

 //get the driver, scene manager, and gui environment objects
 video::IVideoDriver* driver = device->getVideoDriver();
 scene::ISceneManager* smgr = device->getSceneManager();
 gui::IGUIEnvironment* guienv = device->getGUIEnvironment();


/*******************************************************/
/***************CREATE GAME ENTITIES********************/
/*******************************************************/


 //create an animated mesh object from an md2 file
 scene::IAnimatedMesh* mesh = smgr->getMesh("../media/chuckie.MD2");
 if(!mesh)return 1;
 


 //create a player controlled agent and its associated mesh node, and add it to the scene graph
 scene::IAnimatedMeshSceneNode* meshNode = smgr->addAnimatedMeshSceneNode( mesh );
 if(!meshNode)return 1;	
 SubjectAgent playerControlledAgent(meshNode,core::vector3df(75,0,75));
 //
 //create a "scene node" for the animated model //disable lighting
 meshNode->setMaterialTexture(0, driver->getTexture("../media/Chuckie.pcx")); //set the texture

 

meshNode=NULL;


meshNode = smgr->addAnimatedMeshSceneNode(mesh);
 //meshNode->setPosition(core::vector3df(116,128,845));
 Agent agent2(meshNode,core::vector3df(116,128,845));


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

 camera->setPosition(core::vector3df(25,50,25));


 /***************************************************/
 /****************** SET UP COLLOSIONS***************/
 /***************************************************/

 //create a triangle selector object for the map
 scene::ITriangleSelector*  selector = NULL;
 selector = smgr->createOctTreeTriangleSelector(map->getMesh(0), mapNode,128);
 if(!selector)return 1;
 mapNode->setTriangleSelector(selector);


//create a collision node animator and apply it to the camera
 scene::ISceneNodeAnimator *nodeAnimator = 
	smgr->createCollisionResponseAnimator(selector,//geometry for collision 
	camera, //scene node to apply collision to
	core::vector3df(30,50,30),//collision volume radii
	core::vector3df(0,-10,0),//gravity 
	core::vector3df(0,30,0)); //collision volume position
if(!nodeAnimator)return 1;
 camera->addAnimator(nodeAnimator);
 nodeAnimator->drop();


 nodeAnimator = smgr->createCollisionResponseAnimator(selector, meshNode, 
	core::vector3df(30,40,30),//collision volume radii
//
core::vector3df(0,-10,0),//gravity 
	//core::vector3df(0,30,0)
mesh->getBoundingBox().getCenter()	
	); //collision volume position
 
 meshNode->addAnimator(nodeAnimator);
 meshNode->setScale(core::vector3df(1.75f,1.75f,1.75f));
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
 for(int i = 0; i < entities.size(); i++){
 
 
 }


/*******************************************************/
/***************GAME UPDATE LOOP************************/
/*******************************************************/
	while(device->run()){
		
		for(int i = 0; i < entities.size();i++){
			entities[i]->update(device->getTimer());
		}

		//if the mouse is clicked, create a new agent at the camera's current position
		//TO DO!!!


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