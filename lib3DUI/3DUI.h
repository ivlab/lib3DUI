#ifndef PEN3DUI_H
#define PEN3DUI_H


/* Main class to implement a 3D user interface that includes two tracked hands.  We assume there
   is just one button on each hand.  We refer to one hand as the Pen and the other as the Hand.
   The pen creates 3D ink to display in VR.  The hand grabs on to the world and repositions and
   rotates it in space.  A State Design Pattern is used to implement this UI.  So, the program 
   should create a new Pen3DUI class and then call it's brush* and hand* methods when the 
   appropriate input events are received.  The Pen3DUI class will then call the appropriate
   versions of these methods based upon it's current state (Start, Inking, Grabbing, etc.). */
class Pen3DUI {
public:

	enum UI_STATE {
		START_STATE = 0,
		INKING_STATE = 1,
		GRABBING_STATE = 2
	};


	Pen3DUI() {
		_startState = new StartState(this);
		_inkingState = new InkingState(this);
		_grabbingState = new GrabbingState(this);
		_currentState = _startState;
	}

	void setState(UI_STATE newState) {
		if (newState == START_STATE) {
			_currentState->exitState();
			_currentStateID = START_STATE;
			_currentState = _startState;
			_currentState->enterState();
		}
		else if (newState == INKING_STATE) {
			_currentState->exitState();
			_currentStateID = INKING_STATE;
			_currentState = _inkingState;
			_currentState->enterState();
		}
		else if (newState == GRABBING_STATE) {
			_currentState->exitState();
			_currentStateID = GRABBING_STATE;
			_currentState = _grabbingState;
			_currentState->enterState();
		}
	}


	// Tracker move event called when the brush button is not depressed
	void brushTrackerMove(glm::mat4 transform) {
		_currentState->brushTrackerMove(transform);
	}

	// Called when the brush button is pressed, typically to begin a draw operation
	void brushBtnDown() {
		_currentState->brushBtnDown();
	}

	// Tracker move event called when the brush button is depressed
	void brushTrackerDrag(glm::mat4 transform) {
		_currentState->brushTrackerDrag(transform);
	}

	// Called when the brush button is released.
	void brushBtnUp() {
		_currentState->brushBtnUp();
	}


	// Tracker move event called when the hand button is not depressed
	void handTrackerMove(glm::mat4 transform) {
		_currentState->handTrackerMove(transform);
	}

	// Called when the hand button is pressed, typically to begin a grab operation
	void handBtnDown() {
		_currentState->handBtnDown();
	}

	// Tracker move event called when the hand button is depressed
	void handTrackerDrag(glm::mat4 transform) {
		_currentState->handTrackerDrag(transform);
	}
	
	// Called when the hand button is released.
	void handBtnUp() {
		_currentState->handBtnUp();
	}

private:

	UI_STATE       _currentStateID;
	Pen3DUIState   *_currentState;
	StartState     *_startState;
	InkingState    *_inkingState;
	GrabbingState  *_grabbingState;

};

#endif

