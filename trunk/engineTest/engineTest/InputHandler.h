#ifndef IRRLICHT
#include <irrlicht.h>
#endif

class InputHandler: public irr::IEventReceiver{

private:
	bool keyPressed[irr::KEY_KEY_CODES_COUNT];
	InputHandler();
	~InputHandler();

public:
	InputHandler* getInstance();
	virtual bool OnEvent(const irr::SEvent& event1);
};