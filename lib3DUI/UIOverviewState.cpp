
#include "UIOverviewState.h"
#include "UIManager.h"

#include <glm/gtc/matrix_transform.hpp>


#include <iostream>

UIOverviewState::UIOverviewState(UIManager *uiMgr, BentoBoxWidget *bento) :
    UIState(uiMgr), _bento(bento), _grabbing(false)
{
    
}


UIOverviewState::~UIOverviewState() {
    
}



void UIOverviewState::enterState(STATE_ID fromState) {
    _prevStateID = fromState;
}


void UIOverviewState::exitState() {
    
}
    
void UIOverviewState::lhandTrackerMove(glm::mat4 transform) {
    
}

void UIOverviewState::lhandBtnDown() {
    _grabbing = true;
}

void UIOverviewState::lhandTrackerDrag(glm::mat4 transform) {
    // Unconstrained -- allows for rotation and translation in/out of the plane
    //glm::mat4 M = transform * glm::inverse(_uiMgr->getLHandMat()) * _bento->getBentoToWorldMat();
    //_bento->setBentoToWorldMat(M);
    
    // Constrained -- only permits movement in the plane of the bento box widget
    glm::vec3 lastHandInBentoFrame =  glm::inverse(_bento->getBentoToWorldMat()) * _uiMgr->getLHandMat()[3];
    glm::vec3 curHandInBentoFrame =  glm::inverse(_bento->getBentoToWorldMat()) * transform[3];
    
    glm::vec3 trans = curHandInBentoFrame - lastHandInBentoFrame;
    trans.y = 0.0f;
    
    glm::vec3 transInWorldFrame = _bento->getBentoToWorldMat() * glm::vec4(trans, 0.0);
    
    _bento->setBentoToWorldMat(glm::translate(glm::mat4(1.0), transInWorldFrame) * _bento->getBentoToWorldMat());
}

void UIOverviewState::lhandBtnUp() {
    _grabbing = false;
}
    
void UIOverviewState::rhandTrackerMove(glm::mat4 transform) {
    
}

void UIOverviewState::rhandBtnDown() {

}

void UIOverviewState::rhandTrackerDrag(glm::mat4 transform) {
    if (_grabbing) {
        glm::vec3 lastHandInBentoFrame =  glm::inverse(_bento->getBentoToWorldMat()) * _uiMgr->getRHandMat()[3];
        glm::vec3 curHandInBentoFrame =  glm::inverse(_bento->getBentoToWorldMat()) * transform[3];
        glm::vec3 otherHandInBentoFrame =  glm::inverse(_bento->getBentoToWorldMat()) * _uiMgr->getLHandMat()[3];
        
        glm::vec3 lastSpan = lastHandInBentoFrame - otherHandInBentoFrame;
        lastSpan.y = 0.0;
        glm::vec3 curSpan = curHandInBentoFrame - otherHandInBentoFrame;
        curSpan.y = 0.0;
        glm::vec3 diffSpan = curSpan - lastSpan;
        
        float ratio = 1.0;
        if ((glm::abs(curSpan.x) > 0.0) && (glm::abs(lastSpan.x) > 0.0) && (glm::abs(diffSpan.x) > glm::abs(diffSpan.z))) {
            ratio = glm::abs(curSpan.x) / glm::abs(lastSpan.x);
        }
        else if ((glm::abs(curSpan.z) > 0.0) && (glm::abs(lastSpan.z) > 0.0)) {
            ratio = glm::abs(curSpan.z) / glm::abs(lastSpan.z);
        }
        
        std::cout << ratio << std::endl;
        
        if (ratio != 1.0) {
            _bento->setBentoToWorldMat(glm::scale(glm::mat4(1.0), glm::vec3(ratio, ratio, ratio)) * _bento->getBentoToWorldMat());
        }
    }
}

void UIOverviewState::rhandBtnUp() {
    
}

