
#ifndef INPUTHANDLER
#define INPUTHANDLER

#include <irrlicht.h>

using namespace irr;
using namespace gui;

// Define some values that we'll use to identify individual GUI controls.
enum
{
        GUI_ID_QUIT_BUTTON = 101,
        GUI_ID_START_BUTTON,
        GUI_ID_CONFIG_BUTTON
};

class InputHandler: public irr::IEventReceiver{

private:
	bool keyPressed[irr::KEY_KEY_CODES_COUNT];
	IrrlichtDevice *device;
	s32 handler_id ;
    IGUIEnvironment* guienv;
	InputHandler();
	~InputHandler();

public:
	static InputHandler* getInstance();
	void setDeviceContext(IrrlichtDevice *inDevice);
	bool EXIT_MESSAGE;
	virtual bool OnEvent(const irr::SEvent& event1);
	bool isKeyPressed(int);
	
inline bool InputHandler::isAKeyPressed(){return keyPressed[irr::KEY_KEY_A];}
inline bool InputHandler::isWKeyPressed(){return keyPressed[irr::KEY_KEY_W];}
inline bool InputHandler::isSKeyPressed(){return keyPressed[irr::KEY_KEY_S];}
inline bool InputHandler::isDKeyPressed(){return keyPressed[irr::KEY_KEY_D];}
inline bool InputHandler::isCKeyPressed(){return keyPressed[irr::KEY_KEY_C];}
inline bool InputHandler::isTKeyPressed(){return keyPressed[irr::KEY_KEY_T];}
inline bool InputHandler::isTabKeyPressed(){return keyPressed[irr::KEY_TAB];}

	bool unprocessedMouseMessageLMB;
	bool unprocessedMouseMessageRMB;
};

#endif