#ifndef GRABBINGSTATE_H
#define GRABBINGSTATE_H

/** In the GrabbingState, update the roomToVirtual transform on hand trackerDrag
    events.  Return to the StartState with the hand button is released.  Update
    the brush cursor on brush trackerMove and trackerDrag events.  On brush
    trackerDrag events change the roomToVirtual scale. */
class GrabbingState : public Pen3DUIState {
public:
	GrabbingState(Pen3DUI *pen3DUI, Mesh *brushCursor, Mesh *handCursor);
	virtual ~GrabbingState();

	void enterState();

	void brushTrackerMove(glm::mat4 transform);
	void brushTrackerDrag(glm::mat4 transform);

	void handTrackerDrag(glm::mat4 transform);
	void handBtnUp();

private:
	glm::mat4 _lastFrame;
};

#endif
