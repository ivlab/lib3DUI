
#include "UIManager.h"

UIManager::UIManager() {
    
}


UIManager::~UIManager() {
    
}
    
    
void UIManager::setState(UI_STATE newState) {
    
}


void UIManager::rhandTrackerMove(glm::mat4 transform) {
    _currentState->rhandTrackerMove(transform);
}


void UIManager::rhandBtnDown() {
	_currentState->rhandBtnDown();
}

void UIManager::rhandTrackerDrag(glm::mat4 transform) {
	_currentState->rhandTrackerDrag(transform);
}

void UIManager::rhandBtnUp() {
	_currentState->rhandBtnUp();
}


void UIManager::lhandTrackerMove(glm::mat4 transform) {
	_currentState->lhandTrackerMove(transform);
}

void UIManager::lhandBtnDown() {
	_currentState->lhandBtnDown();
}

void UIManager::lhandTrackerDrag(glm::mat4 transform) {
	_currentState->lhandTrackerDrag(transform);
}
	
void UIManager::lhandBtnUp() {
	_currentState->lhandBtnUp();
}


