
#include "UIOverviewState.h"
#include "UIManager.h"

#include <glm/gtc/matrix_transform.hpp>


#include <iostream>

UIOverviewState::UIOverviewState(UIManager *uiMgr, BentoBoxWidget *bento) :
    UIState(uiMgr), _bento(bento)
{
    
}


UIOverviewState::~UIOverviewState() {
    
}



void UIOverviewState::enterState() {
    
}


void UIOverviewState::exitState() {
    
}
    
void UIOverviewState::lhandTrackerMove(glm::mat4 transform) {
    
}

void UIOverviewState::lhandBtnDown() {
    
}

void UIOverviewState::lhandTrackerDrag(glm::mat4 transform) {
    // Unconstrained -- allows for rotation:
    //glm::mat4 M = transform * glm::inverse(_uiMgr->getLHandMat()) * _bento->getBentoToWorldMat();
    //_bento->setBentoToWorldMat(M);
    
    // Only translation in the plane of the bento box widget
    glm::vec3 lastHandInBentoFrame =  glm::inverse(_bento->getBentoToWorldMat()) * _uiMgr->getLHandMat()[3];
    glm::vec3 curHandInBentoFrame =  glm::inverse(_bento->getBentoToWorldMat()) * transform[3];
    
    glm::vec3 trans = curHandInBentoFrame - lastHandInBentoFrame;
    trans.y = 0.0f;
    
    glm::vec3 transInWorldFrame = _bento->getBentoToWorldMat() * glm::vec4(trans, 0.0);
    
    _bento->setBentoToWorldMat(glm::translate(glm::mat4(1.0), transInWorldFrame) * _bento->getBentoToWorldMat());
}

void UIOverviewState::lhandBtnUp() {
    
}
    
void UIOverviewState::rhandTrackerMove(glm::mat4 transform) {
    
}

void UIOverviewState::rhandBtnDown() {
    
}

void UIOverviewState::rhandTrackerDrag(glm::mat4 transform) {
    
}

void UIOverviewState::rhandBtnUp() {
    
}

