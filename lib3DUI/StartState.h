#ifndef STARTSTATE_H
#define STARTSTATE_H

/** In the StartState, the brush and hand cursor transformations need to be
    updated when trackerMove events are received.  If the brush button is
    pressed down, then transition to InkingState.  If the hand button is
    pressed down, then transition to the GrabbingState. */
class StartState : public Pen3DUIState {
public:
	StartState(Pen3DUI *pen3DUI, Mesh *brushCursor, Mesh *handCursor) : 
		Pen3DUIState(pen3DUI, brushCursor, handCursor) {}
	virtual ~StartState() {}

	void brushTrackerMove(glm::mat4 transform);
	void brushBtnDown();

	void handTrackerMove(glm::mat4 transform);
	void handBtnDown();
};

#endif

