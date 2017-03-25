#include "GrabbingState.h"

GrabbingState::GrabbingState(Pen3DUI *pen3DUI, Mesh *brushCursor, Mesh *handCursor) : 
	Pen3DUIState(pen3DUI, brushCursor, handCursor) 
{
}

GrabbingState::~GrabbingState() 
{
}


void 
GrabbingState::enterState() 
{
	_lastFrame = glm::mat4(1.0);
}

void 
GrabbingState::brushTrackerMove(glm::mat4 transform) 
{
	_brushCursor->setTransform(transform);
}

void 
GrabbingState::brushTrackerDrag(glm::mat4 transform) 
{
	_brushCursor->setTransform(transform);

	// TODO: Adjust scale of the roomToVirtual transform based upon dist between the hands
	// This math is a bit tricky.  Watch out for instabilities.
}

void 
GrabbingState::handTrackerDrag(glm::mat4 transform) 
{
	_handCursor->setTransform(transform);

	// Adjust pos and rot of the roomToVirtual transform
	if (_lastFrame != glm::mat4(1.0)) {
	    glm::dmat4 delta = transform * glm::inverse(_lastFrame);
    	glm::dmat4 t = getRoomToVirtualSpaceFrame() * glm::inverse(delta);
    	setRoomToVirtualSpaceTransform(t);
    }
    _lastFrame = transform;
}

void 
GrabbingState::handBtnUp() 
{
	_pen3DUI->setState(Pen3DUI::START_STATE);
}

