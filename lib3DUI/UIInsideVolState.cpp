
#include "UIInsideVolState.h"
#include "UIManager.h"

#include <glm/gtc/matrix_transform.hpp>


#include <iostream>

UIInsideVolState::UIInsideVolState(UIManager *uiMgr, BentoBoxWidget *bento) :
    UIState(uiMgr), _bento(bento)
{
    
}


UIInsideVolState::~UIInsideVolState() {
    
}



void UIInsideVolState::enterState(STATE_ID fromState) {

}


void UIInsideVolState::exitState() {
    
}
    
void UIInsideVolState::lhandTrackerMove(glm::mat4 transform) {
    
}

void UIInsideVolState::lhandBtnDown() {

}

void UIInsideVolState::lhandTrackerDrag(glm::mat4 transform) {

}

void UIInsideVolState::lhandBtnUp() {

}
    
void UIInsideVolState::rhandTrackerMove(glm::mat4 transform) {
    
}

void UIInsideVolState::rhandBtnDown() {
    
}

void UIInsideVolState::rhandTrackerDrag(glm::mat4 transform) {
}

void UIInsideVolState::rhandBtnUp() {

}

