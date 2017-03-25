#include "StartState.h"


void StartState::brushTrackerMove(glm::mat4 transform) {
	_brushCursor->setTransform(transform);
}

void StartState::brushBtnDown() {
	_pen3DUI->setState(Pen3DUI::INKING_STATE);
}

void StartState::handTrackerMove(glm::mat4 transform) {
	_handCursor->setTransform(transform);
}

void StartState::handBtnDown() {
	_pen3DUI->setState(Pen3DUI::GRABBING_STATE);
}

