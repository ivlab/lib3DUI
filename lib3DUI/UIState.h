#ifndef UISTATE_H
#define UISTATE_H


#include <glm/glm.hpp>

class UIManager;


/** Following the State Design Pattern, this class defines callbacks for the 
    UI events that must be handled for all of the states the the Pen3D system.
    Concrete implementations of this base class are then used to define the
    specific behavior given the current state. */ 
class UIState {
public:
	UIState(UIManager *uiMgr) : _uiMgr(uiMgr) {}
	virtual ~UIState() {}

	virtual void enterState() {}
	virtual void exitState() {}

	virtual void lhandTrackerMove(glm::mat4 transform) {}
	virtual void lhandBtnDown() {}
	virtual void lhandTrackerDrag(glm::mat4 transform) {}
	virtual void lhandBtnUp() {}

	virtual void rhandTrackerMove(glm::mat4 transform) {}
	virtual void rhandBtnDown() {}
	virtual void rhandTrackerDrag(glm::mat4 transform) {}
	virtual void rhandBtnUp() {}

protected:
	UIManager *_uiMgr;
};

#endif
