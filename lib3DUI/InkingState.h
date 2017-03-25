#ifndef INKINGSTATE_H
#define INKINGSTATE_H

/** In the InkingState, create (or add to) a 3D line when a brush trackerDrag
    event is received.  Transition back to StartState if the brush button is
    released.  Update the hand cursor on hand trackerMove and trackerDrag
    events.  Ignore hand button presses? */
class InkingState : public Pen3DUIState {
public:
	InkingState(Pen3DUI *pen3DUI, Mesh *brushCursor, Mesh *handCursor);
	virtual ~InkingState();

	void enterState();

	void brushTrackerDrag(glm::mat4 transform);
	void brushBtnUp();

	void handTrackerMove(glm::mat4 transform);
	void handTrackerDrag(glm::mat4 transform);

private:
	bool _createNewLine;
};

#endif
