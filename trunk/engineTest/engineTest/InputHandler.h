#ifndef IRRLICHT
#include <irrlicht.h>
#define IRRLICHT
#endif

class InputHandler: public irr::IEventReceiver{

private:
	bool keyPressed[irr::KEY_KEY_CODES_COUNT];
	InputHandler();
	~InputHandler();

public:
	static InputHandler* getInstance();
	virtual bool OnEvent(const irr::SEvent& event1);
	bool isKeyPressed(int);
	bool isAKeyPressed();
	bool isWKeyPressed();
	bool isSKeyPressed();
	bool isDKeyPressed();
	bool isCKeyPressed();

	bool unprocessedMouseMessageLMB;
	bool unprocessedMouseMessageRMB;
};