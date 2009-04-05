
#ifndef INPUTHANDLER
#define INPUTHANDLER

#include <irrlicht.h>


class InputHandler: public irr::IEventReceiver{

private:
	bool keyPressed[irr::KEY_KEY_CODES_COUNT];
	InputHandler();
	~InputHandler();

public:
	static InputHandler* getInstance();
	bool EXIT_MESSAGE;
	virtual bool OnEvent(const irr::SEvent& event1);
	bool isKeyPressed(int);
	
inline bool InputHandler::isAKeyPressed(){return keyPressed[irr::KEY_KEY_A];}
inline bool InputHandler::isWKeyPressed(){return keyPressed[irr::KEY_KEY_W];}
inline bool InputHandler::isSKeyPressed(){return keyPressed[irr::KEY_KEY_S];}
inline bool InputHandler::isDKeyPressed(){return keyPressed[irr::KEY_KEY_D];}
inline bool InputHandler::isCKeyPressed(){return keyPressed[irr::KEY_KEY_C];}
inline bool InputHandler::isTKeyPressed(){return keyPressed[irr::KEY_KEY_T];}

	bool unprocessedMouseMessageLMB;
	bool unprocessedMouseMessageRMB;
};

#endif