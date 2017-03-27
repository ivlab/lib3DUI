
#include "UIStates.h"
#include "UIManager.h"

#include <glm/gtc/matrix_transform.hpp>


#include <iostream>


// -----------------  STATE:  BOTH HANDS OUTSIDE  -----------------

BothOutsideVol::BothOutsideVol(UIManager *uiMgr, BentoBoxWidget *bento) :
    UIState(uiMgr,bento), _grabbing(false)
{
}

BothOutsideVol::~BothOutsideVol() {
}


void BothOutsideVol::enterState(STATE_ID fromState) {
    std::cout << "ENTER STATE: BothOutside" << std::endl;
}


void BothOutsideVol::exitState() {
}
    
void BothOutsideVol::lhandTrackerMove(glm::mat4 transform) {
    glm::vec3 posInBentoFrame = glm::inverse(_bento->getSubVolumesToWorldMat()) * transform[3];
    int row, col;
    if (_bento->insideSubVolume(posInBentoFrame, &row, &col)) {
        _uiMgr->setState(STATE_NDHINSIDE);
    }
}

void BothOutsideVol::lhandBtnDown() {
    _grabbing = true;
}

void BothOutsideVol::lhandTrackerDrag(glm::mat4 transform) {
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

void BothOutsideVol::lhandBtnUp() {
    _grabbing = false;
}



void BothOutsideVol::rhandTrackerMove(glm::mat4 transform) {
    glm::vec3 posInBentoFrame = glm::inverse(_bento->getSubVolumesToWorldMat()) * transform[3];
    int row, col;
    if (_bento->insideSubVolume(posInBentoFrame, &row, &col)) {
        _uiMgr->setState(STATE_DHINSIDE);
    }
}

void BothOutsideVol::rhandBtnDown() {
}

void BothOutsideVol::rhandTrackerDrag(glm::mat4 transform) {
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
        
        //std::cout << ratio << std::endl;
        
        if (ratio != 1.0) {
            _bento->setBentoToWorldMat(glm::scale(glm::mat4(1.0), glm::vec3(ratio, ratio, ratio)) * _bento->getBentoToWorldMat());
        }
    }
}

void BothOutsideVol::rhandBtnUp() {
}



// -----------------  STATE:  DH INSIDE  -----------------

DHInsideVol::DHInsideVol(UIManager *uiMgr, BentoBoxWidget *bento) :
    UIState(uiMgr,bento), _grabbing(false)
{
}

DHInsideVol::~DHInsideVol() {
}


void DHInsideVol::enterState(STATE_ID fromState) {
    std::cout << "ENTER STATE: DHInside" << std::endl;
}

void DHInsideVol::exitState() {
}


void DHInsideVol::lhandTrackerMove(glm::mat4 transform) {
    glm::vec3 posInBentoFrame = glm::inverse(_bento->getSubVolumesToWorldMat()) * transform[3];
    int row, col;
    if (_bento->insideSubVolume(posInBentoFrame, &row, &col)) {
        _uiMgr->setState(STATE_BOTHINSIDE);
    }
}

void DHInsideVol::lhandBtnDown() {
}

void DHInsideVol::lhandTrackerDrag(glm::mat4 transform) {
}

void DHInsideVol::lhandBtnUp() {
}


void DHInsideVol::rhandTrackerMove(glm::mat4 transform) {
    glm::vec3 posInBentoFrame = glm::inverse(_bento->getSubVolumesToWorldMat()) * transform[3];
    int row, col;
    if (!_bento->insideSubVolume(posInBentoFrame, &row, &col)) {
        _uiMgr->setState(STATE_BOTHOUTSIDE);
    }
}

void DHInsideVol::rhandBtnDown() {
}

void DHInsideVol::rhandTrackerDrag(glm::mat4 transform) {
}

void DHInsideVol::rhandBtnUp() {
}



// -----------------  STATE:  NDH INSIDE  -----------------

NDHInsideVol::NDHInsideVol(UIManager *uiMgr, BentoBoxWidget *bento) :
UIState(uiMgr,bento), _grabbing(false)
{
}

NDHInsideVol::~NDHInsideVol() {
}


void NDHInsideVol::enterState(STATE_ID fromState) {
    std::cout << "ENTER STATE: NDHInside" << std::endl;
}

void NDHInsideVol::exitState() {
}


void NDHInsideVol::lhandTrackerMove(glm::mat4 transform) {
    glm::vec3 posInBentoFrame = glm::inverse(_bento->getSubVolumesToWorldMat()) * transform[3];
    int row, col;
    if (!_bento->insideSubVolume(posInBentoFrame, &row, &col)) {
        _uiMgr->setState(STATE_BOTHOUTSIDE);
    }
}

void NDHInsideVol::lhandBtnDown() {
}

void NDHInsideVol::lhandTrackerDrag(glm::mat4 transform) {
}

void NDHInsideVol::lhandBtnUp() {
}


void NDHInsideVol::rhandTrackerMove(glm::mat4 transform) {
    glm::vec3 posInBentoFrame = glm::inverse(_bento->getSubVolumesToWorldMat()) * transform[3];
    int row, col;
    if (_bento->insideSubVolume(posInBentoFrame, &row, &col)) {
        _uiMgr->setState(STATE_BOTHINSIDE);
    }
}

void NDHInsideVol::rhandBtnDown() {
}

void NDHInsideVol::rhandTrackerDrag(glm::mat4 transform) {
}

void NDHInsideVol::rhandBtnUp() {
}




// -----------------  STATE:  BOTH HANDS INSIDE  -----------------

BothInsideVol::BothInsideVol(UIManager *uiMgr, BentoBoxWidget *bento) :
UIState(uiMgr,bento), _grabbing(false)
{
}

BothInsideVol::~BothInsideVol() {
}


void BothInsideVol::enterState(STATE_ID fromState) {
    std::cout << "ENTER STATE: BothInside" << std::endl;
}

void BothInsideVol::exitState() {
}


void BothInsideVol::lhandTrackerMove(glm::mat4 transform) {
    glm::vec3 posInBentoFrame = glm::inverse(_bento->getSubVolumesToWorldMat()) * transform[3];
    int row, col;
    if (!_bento->insideSubVolume(posInBentoFrame, &row, &col)) {
        _uiMgr->setState(STATE_DHINSIDE);
    }
}

void BothInsideVol::lhandBtnDown() {
}

void BothInsideVol::lhandTrackerDrag(glm::mat4 transform) {
}

void BothInsideVol::lhandBtnUp() {
}


void BothInsideVol::rhandTrackerMove(glm::mat4 transform) {
    glm::vec3 posInBentoFrame = glm::inverse(_bento->getSubVolumesToWorldMat()) * transform[3];
    int row, col;
    if (!_bento->insideSubVolume(posInBentoFrame, &row, &col)) {
        _uiMgr->setState(STATE_NDHINSIDE);
    }
}

void BothInsideVol::rhandBtnDown() {
}

void BothInsideVol::rhandTrackerDrag(glm::mat4 transform) {
}

void BothInsideVol::rhandBtnUp() {
}

