#include "gameHUD.h"


using namespace irr;
using namespace video;

gameHUD::gameHUD(video::IVideoDriver* videoDriver, int x1, int y1, int x2, int y2, int maxShotTimerValue){
        //class constructor
   driver = videoDriver;
       
   //shot timer bar size
   x1Bar = x1;
   y1Bar = y1;
   x2Bar = x2;
   y2Bar = y2;
       
        //max bar values
   maxShotTimerBarValue = maxShotTimerValue;

        //current bar values
   shotTimerBarValue = maxShotTimerValue;

		//scalar delta for bar value
   deltaShotTimerBar = shotTimerBarValue;

   //load textures

   //load some texture for spellbar and make it transparent with ColorKey 0 (black) and put it into a texture array
   GUITextures[0] = driver->getTexture("../Media/Textures/spellbar_smaller.bmp");
   driver->makeColorKeyTexture(GUITextures[0], video::SColor(0,0,0,0));
} 

void gameHUD::render(){

   float delta; //status bar variation
   core::dimension2d<s32> screenSize = driver->getScreenSize(); 

   double screenX=screenSize.Width;
   double screenY=screenSize.Height; 

   //changes the bar value from X to Y smoothly
   if ((int)deltaShotTimerBar != (int)shotTimerBarValue){
      delta = shotTimerBarValue - deltaShotTimerBar;
      if (delta > 0)
         shotTimerBarValue -= 0.2;
      if (delta < 0)
         shotTimerBarValue += 0.2;
   }
       
   //draws the timer bar according to its value (green for high, decreasing to yellow till red), and some others rectangles for a cool look
   driver->draw2DImage(GUITextures[0], core::position2d<s32>(screenX - 341, screenY - 73), core::rect<s32>(0,0,341,73), 0, video::SColor(255,255,255,255), true);

   driver->draw2DRectangle(video::SColor(255, 100, 100, 100), core::rect<s32>((screenX - 305), (screenY - 45), ((maxShotTimerBarValue*2.7)+ (screenX - 305)), (screenY - 25)));

   driver->draw2DRectangle(video::SColor(255, 125, 125, 125), core::rect<s32>((screenX - 305)+1, (screenY - 45)+1, ((maxShotTimerBarValue*2.7)+ (screenX - 305)-1), (screenY - 25)-1));

   driver->draw2DRectangle(video::SColor(255, 150, 150, 150), core::rect<s32>((screenX - 305)+3, (screenY - 45)+3, ((maxShotTimerBarValue*2.7)+ (screenX - 305)-3), (screenY - 25)-3));

   driver->draw2DRectangle(core::rect<s32>((screenX - 305)+3, (screenY - 45)+3, ((maxShotTimerBarValue*2.7)+ (screenX - 305)-3), (screenY - 25)-3),

                     video::SColor(255, 255-shotTimerBarValue*2.55, shotTimerBarValue*2.55, 0),

                     video::SColor(255, 255-shotTimerBarValue*2.55, shotTimerBarValue*2.55, 0),

                     video::SColor(255, 255-shotTimerBarValue*2.55, shotTimerBarValue*2.55-150, 0),

                     video::SColor(255, 255-shotTimerBarValue*2.55, shotTimerBarValue*2.55-150, 0)); 

} 

void gameHUD::setShotTimerBarValue(int shotTimerValue){
   deltaShotTimerBar = shotTimerValue;
}