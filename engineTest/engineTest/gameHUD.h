#ifndef GAME_HUD
#define GAME_HUD

#include "irrlicht.h"

using namespace irr;
using namespace video;
//Object that represents all Scene Nodes Assembled for in-game HUD and UI
class gameHUD {

private:
   video::IVideoDriver* driver;
   int x1Bar, y1Bar, x2Bar, y2Bar;

   int	maxShotTimerBarValue; //size of the timer bar
   int	roundTimer;			  //Current Round Time, updated by clock function
   double deltaShotTimerBar;  //difference scalar
   double shotTimerBarValue;  //current bar value
   double screenX, screenY;
   bool gunTimerReady;		//current gun readiness

   //Texture Storage for random GUI HUD elements
   //Assignments:
   //	0 : Gun Timer Bar
   //	1 : Crosshair
   video::ITexture* GUITextures[10];

   //Texture Storage for character GUI HUD elements
   //Assignments:
   //	0-9 : Numbers zero through nine
   //	10  : Colon Character 
   video::ITexture* CharTextures[11];

   //Texture Storage for fixed position clock characters
   //Assignments:
   //	0 : Minutes (zero to nine)
   //	1 : Seconds (1x10^1)
   //	2 : Seconds (1x10^0)
   video::ITexture* ClockTextures[3];

   gameHUD(); //constructor
   ~gameHUD(); //destructor :O

public:

   static gameHUD* getInstance(); //returns an instance of the gameHUD
   void render(); //render the HUD, must be called AFTER the 3D draw, or it  wont show
   void setShotTimerBarValue(int shotTimerValue); //change bar values
   void updateRoundTimer(int timeInSeconds); //changes game timer value
   void updateClockTextures(); //changes the pointers for the clock textures
   void setVideoDriver (video::IVideoDriver* videoDriver);
   void loadTextures(); //loads all relevant textures into private member variables
   void setGunReady(bool ready); //sets gun Readiness
   bool getGunReady(); //returns true if gun is ready to be fired, false otherwise
}; 

#endif