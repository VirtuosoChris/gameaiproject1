#include "InputHandler.h"


extern bool ENABLE_DEBUG_OUTPUT;

//constructor
InputHandler::InputHandler(){
	for(int i = 0; i < irr::KEY_KEY_CODES_COUNT;i++){
		keyPressed[i] = false;
	}

	unprocessedMouseMessageLMB = unprocessedMouseMessageRMB = false;
}


//Destructor
InputHandler::~InputHandler(){}


//function called when input event is fired
bool InputHandler::OnEvent(const irr::SEvent& event1){
		
	

	switch(event1.EventType){
		
			case irr::EET_KEY_INPUT_EVENT:

				if(event1.KeyInput.Key == irr::KEY_ESCAPE)exit(0);
				keyPressed[event1.KeyInput.Key] =  event1.KeyInput.PressedDown;	

				if(keyPressed[irr::KEY_KEY_T])ENABLE_DEBUG_OUTPUT = !ENABLE_DEBUG_OUTPUT;

				break;


			case irr::EET_MOUSE_INPUT_EVENT:
				if(event1.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP){
						unprocessedMouseMessageLMB = true;					
				}if(event1.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP){
						unprocessedMouseMessageRMB = true;					
				}
				
			


			 break;
			default:
				
				;
		}
		return false;
}



//returns the instance of the InputHandler class
 InputHandler* InputHandler::getInstance(){
static InputHandler instance;

return &instance;
}


 bool InputHandler::isKeyPressed(int i){
  return keyPressed[i];
 }

bool InputHandler::isAKeyPressed(){return keyPressed[irr::KEY_KEY_A];}
bool InputHandler::isWKeyPressed(){return keyPressed[irr::KEY_KEY_W];}
bool InputHandler::isSKeyPressed(){return keyPressed[irr::KEY_KEY_S];}
bool InputHandler::isDKeyPressed(){return keyPressed[irr::KEY_KEY_D];}
bool InputHandler::isCKeyPressed(){return keyPressed[irr::KEY_KEY_C];}
bool InputHandler::isTKeyPressed(){return keyPressed[irr::KEY_KEY_T];}

