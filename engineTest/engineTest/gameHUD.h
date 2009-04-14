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

   int   maxShotTimerBarValue; //size of the timer bar
   double deltaShotTimerBar;  //difference scalar
   double shotTimerBarValue;  //current bar value

   video::ITexture* GUITextures[10];

public:

   gameHUD(video::IVideoDriver* videoDriver, int maxShotTimerValue); //constructor
   ~gameHUD(); //destructor :O
   void render(); //render the HUD, must be called AFTER the 3D draw, or it  wont show
   void setShotTimerBarValue(int shotTimerValue); //change bar values

}; 

#endif