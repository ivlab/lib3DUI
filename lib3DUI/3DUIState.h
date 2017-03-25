#ifndef PEN3DUISTATE_H
#define PEN3DUISTATE_H

/** Following the State Design Pattern, this class defines callbacks for the 
    UI events that must be handled for all of the states the the Pen3D system.
    Concrete implementations of this base class are then used to define the
    specific behavior given the current state. */ 
class Pen3DUIState {
public:
	Pen3DUIState(Pen3DUI *pen3DUI, Mesh *brushCursor, Mesh *handCursor) : 
		_pen3DUI(pen3DUI), _brushCursor(brushCursor), _handCursor(handCursor) {}
	virtual ~Pen3DUIState() {}

	void enterState() {}
	void exitState() {}

	void brushTrackerMove(glm::mat4 transform) {}
	void brushBtnDown() {}
	void brushTrackerDrag(glm::mat4 transform) {}
	void brushBtnUp() {}

	void handTrackerMove(glm::mat4 transform) {}
	void handBtnDown() {}
	void handTrackerDrag(glm::mat4 transform) {}
	void handBtnUp() {}

protected:
	Pen3DUI *_pen3DUI;
	Mesh *_brushCursor;
	Mesh *_handCursor;
};

#endif
