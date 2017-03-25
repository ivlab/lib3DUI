#ifndef UISTATE_H
#define UISTATE_H


#include <glm/glm.hpp>

class Cursor;
class UIManager;


/** Following the State Design Pattern, this class defines callbacks for the 
    UI events that must be handled for all of the states the the Pen3D system.
    Concrete implementations of this base class are then used to define the
    specific behavior given the current state. */ 
class UIState {
public:
	UIState(UIManager *uiMgr, Cursor *lhandCursor, Cursor *rhandCursor) :
		    _uiMgr(uiMgr), _lhandCursor(lhandCursor), _rhandCursor(rhandCursor) {}
	virtual ~UIState() {}

	void enterState() {}
	void exitState() {}

	void lhandTrackerMove(glm::mat4 transform) {}
	void lhandBtnDown() {}
	void lhandTrackerDrag(glm::mat4 transform) {}
	void lhandBtnUp() {}

	void rhandTrackerMove(glm::mat4 transform) {}
	void rhandBtnDown() {}
	void rhandTrackerDrag(glm::mat4 transform) {}
	void rhandBtnUp() {}

protected:
	UIManager *_uiMgr;
	Cursor *_lhandCursor;
	Cursor *_rhandCursor;
};

#endif
