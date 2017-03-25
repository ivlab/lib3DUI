#include "InkingState.h"


InkingState::InkingState(Pen3DUI *pen3DUI, Mesh *brushCursor, Mesh *handCursor) : 
	Pen3DUIState(pen3DUI, brushCursor, handCursor) 
{
	_createNewLine = true;
}

InkingState::~InkingState() 
{
}

void 
InkingState::enterState() 
{
	_createNewLine = true;
}

void 
InkingState::brushTrackerDrag(glm::mat4 transform) 
{
	_brushCursor->setTransform(transform);

	if (_createNewLine) {
		// TODO: Create a new 3D line object, add it to the "artwork"


		_createNewLine = false;
	}
	else {
		// TODO: Add a new point to the existing 3D line object.

	}
}

void 
InkingState::brushBtnUp() 
{
	_pen3DUI->setState(Pen3DUI::START_STATE);
}

void 
InkingState::handTrackerMove(glm::mat4 transform) 
{
	_handCursor->setTransform(transform);
}

void 
InkingState::handTrackerDrag(glm::mat4 transform) 
{
	_handCursor->setTransform(transform);
}
