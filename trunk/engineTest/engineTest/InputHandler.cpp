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
			default:
				
				;
		}
		return false;
}



//returns 
InputHandler* InputHandler::getInstance(){
static InputHandler instance;
return &instance;
}


