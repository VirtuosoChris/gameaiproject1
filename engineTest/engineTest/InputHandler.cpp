#include "InputHandler.h"


//constructor
InputHandler::InputHandler(){
	for(int i = 0; i < irr::KEY_KEY_CODES_COUNT;i++){
		keyPressed[i] = false;
	}
}


//Destructor
InputHandler::~InputHandler(){}


//function called when input event is fired
bool InputHandler::OnEvent(const irr::SEvent& event1){
		switch(event1.EventType){
		
			case irr::EET_KEY_INPUT_EVENT:
				keyPressed[event1.KeyInput.Key] =  event1.KeyInput.PressedDown;	
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

