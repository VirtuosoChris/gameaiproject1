//do destructors/constructors
//singleton stuff; copy constructor, assignment
//agent class
//free message memory
//gameentitylist
//make displacement heading
//bounding boxes

#ifndef IRRLICHT
#include <irrlicht.h>
#endif

#include "InputHandler.h"

#include "Agent.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


using namespace irr;



int main(int argc, char** argv){

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

	 
 //create an animated mesh object from an md2 file
 scene::IAnimatedMesh* mesh = smgr->getMesh("../media/chuckie.MD2");
 if(!mesh)return 1;
 


 //create a player controlled agent and its associated mesh node, and add it to the scene graph
 scene::IAnimatedMeshSceneNode* meshNode = smgr->addAnimatedMeshSceneNode( mesh );
 if(!meshNode)return 1;	
 Agent playerControlledAgent(meshNode);
 //meshNode=NULL;

 //create a "scene node" for the animated model
 meshNode->setMaterialFlag(video::EMF_LIGHTING, false); //disable lighting
 meshNode->setMaterialTexture(0, driver->getTexture("../media/Chuckie.pcx")); //set the texture
 meshNode->setPosition(core::vector3df(75,0,75));


 //load the pk3 file containing the .bsp map file into the engine file system
 device->getFileSystem()->addZipFileArchive("../media/map-20kdm2.pk3");
 
 //get the mesh from the map bsp file
 scene::IAnimatedMesh *map  = smgr->getMesh("20kdm2.bsp");
 
 if(!map)return 1;
 //a scene node for the map
 scene::ISceneNode *mapNode = NULL;
 mapNode = smgr->addOctTreeSceneNode(map->getMesh(0), 0, -1, 1024);
 if(!mapNode)return 1;

 //translate the map a bit since it wasn't modeled around the origin
 mapNode->setPosition(core::vector3df(-1300,-144,-1249));


 scene::ICameraSceneNode *camera = 
	 smgr->addCameraSceneNodeFPS();

 camera->setPosition(core::vector3df(25,50,25));

 
 scene::ITriangleSelector*  selector = NULL;
 selector = smgr->createOctTreeTriangleSelector(map->getMesh(0), mapNode,128);
 if(!selector)return 1;
 mapNode->setTriangleSelector(selector);


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

 




 scene::IBillboardSceneNode *billboard = smgr->addBillboardSceneNode();
 billboard->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
 billboard->setMaterialTexture(0,driver->getTexture("../media/particle.bmp"));
 billboard->setMaterialFlag(video::EMF_LIGHTING, false);
 billboard->setMaterialFlag(video::EMF_ZBUFFER,false);
 billboard->setSize(core::dimension2d<f32>(20.0f, 20.0f));


 core::line3d<f32> line;
 
 core::vector3df intersection;
 core::triangle3df triangle;
 
 if(selector == NULL)return 1;
 

// gui::IGUIStaticText ist =  guienv->addStaticText(str.c_str(),core::rect<s32>(10,10,260,22), true);


 //while the user doesn't close the window
	 while(device->run()){
		  core::stringw str = L"";
		  
		 
		 playerControlledAgent.update(device->getTimer());
		 str+=playerControlledAgent.orientation;
		 str+=" (";
		 str+=playerControlledAgent.displacement.X;
		 str+=",";
		 str+=playerControlledAgent.displacement.Z;
		 str+=")";
		 device->setWindowCaption(str.c_str());
 
 //meshNode->setRotation(core::vector3df(0.0f,rot,0.0f));
 
      //core::vector3df nodePos = meshNode->getPosition();
      //nodePos.Z += 1.0f;
	  //  meshNode->setPosition(nodePos);
	  

		billboard->setVisible(true);
		 if(smgr->getSceneCollisionManager()->getCollisionPoint(line, selector,intersection, triangle))
			billboard->setPosition(intersection);
		 else{
			 billboard->setVisible(false);
		 }


		 //begin drawing a frame
		 driver->beginScene(true, true, video::SColor(255,100,101,140));
			smgr->drawAll();  //draw 3d objects
			guienv->drawAll();//draw gui components
		
		 driver->endScene();//end drawing


		 line.start = camera->getPosition();
		 line.end = line.start + (camera->getTarget() - line.start).normalize() * 5000.0f;
 
		 //add static text to the window
	//	 core::stringw str = "Position:";
	//	 str +=camera->getPosition().X;
	//	 str +=":";
	//	 str +=camera->getPosition().Y;
	//	 str +=":";
	//	 str+=camera->getPosition().Z;
	//	 ist.setText(str.c_str());
	 	 
	 }


	
	 device->drop();

return 0;
}