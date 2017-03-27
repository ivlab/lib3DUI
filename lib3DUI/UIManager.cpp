
#include "UIManager.h"
#include "QuickShapes.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


UIManager::UIManager(BentoBoxWidget *bento) :
    _lhandCursorType(CURSOR_CUBE),
    _rhandCursorType(CURSOR_LASER),
    _lhandDown(false),
    _rhandDown(false),
    _lhandMat(glm::mat4(1.0)),
    _rhandMat(glm::mat4(1.0))
{
    _bothOutsideVol = new BothOutsideVol(this, bento);
    _dhInsideVol = new DHInsideVol(this, bento);
    _ndhInsideVol = new NDHInsideVol(this, bento);
    _bothInsideVol = new BothInsideVol(this, bento);

    _currentState = _bothOutsideVol;
    _currentStateID = UIState::STATE_BOTHOUTSIDE;
}


UIManager::~UIManager() {
    delete _bothOutsideVol;
    delete _dhInsideVol;
    delete _ndhInsideVol;
    delete _bothInsideVol;
}
    
    
void UIManager::setState(UIState::STATE_ID newState) {
    if (newState == UIState::STATE_BOTHOUTSIDE) {
        UIState *prev = _currentState;
        UIState::STATE_ID prevID = _currentStateID;
        prev->exitState();
        _currentStateID = UIState::STATE_BOTHOUTSIDE;
        _currentState = _bothOutsideVol;
        _currentState->enterState(prevID);
    }
    else if (newState == UIState::STATE_DHINSIDE) {
        UIState *prev = _currentState;
        UIState::STATE_ID prevID = _currentStateID;
        prev->exitState();
        _currentStateID = UIState::STATE_DHINSIDE;
        _currentState = _dhInsideVol;
        _currentState->enterState(prevID);
    }
    else if (newState == UIState::STATE_NDHINSIDE) {
        UIState *prev = _currentState;
        UIState::STATE_ID prevID = _currentStateID;
        prev->exitState();
        _currentStateID = UIState::STATE_NDHINSIDE;
        _currentState = _ndhInsideVol;
        _currentState->enterState(prevID);
    }
    else if (newState == UIState::STATE_BOTHINSIDE) {
        UIState *prev = _currentState;
        UIState::STATE_ID prevID = _currentStateID;
        prev->exitState();
        _currentStateID = UIState::STATE_BOTHINSIDE;
        _currentState = _bothInsideVol;
        _currentState->enterState(prevID);
    }

    else {
        std::cerr << "UIManager: unknown state " << (int)newState << std::endl;
        exit(1);
    }
}


void UIManager::rhandTrackerMove(glm::mat4 transform) {
    if (_rhandDown) {
        _currentState->rhandTrackerDrag(transform);
    }
    else {
        _currentState->rhandTrackerMove(transform);
    }
    _rhandMat = transform;
}


void UIManager::rhandBtnDown() {
	_currentState->rhandBtnDown();
    _rhandDown = true;
}

void UIManager::rhandBtnUp() {
	_currentState->rhandBtnUp();
    _rhandDown = false;
}


void UIManager::lhandTrackerMove(glm::mat4 transform) {
    if (_lhandDown) {
        _currentState->lhandTrackerDrag(transform);
    }
    else {
        _currentState->lhandTrackerMove(transform);
    }
    _lhandMat = transform;
}

void UIManager::lhandBtnDown() {
	_currentState->lhandBtnDown();
    _lhandDown = true;
}

void UIManager::lhandBtnUp() {
	_currentState->lhandBtnUp();
    _lhandDown = false;
}


// --------------------- Friend Renderer Class ----------------------


UIManagerRenderer::UIManagerRenderer(UIManager *mgr) : _mgr(mgr) {
    _quickShapes = new QuickShapes();
}

UIManagerRenderer::~UIManagerRenderer() {
    delete _quickShapes;
}


void UIManagerRenderer::draw(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    
    float lcol[3] = {0.7, 0.2, 0.2};
    float rcol[3] = {0.2, 0.2, 0.7};
    
    if (_mgr->_lhandCursorType == _mgr->CURSOR_CUBE) {
        glm::mat4 S = glm::mat4(1.0);
        S[0].x = 0.1;
        S[1].y = 0.1;
        S[2].z = 0.1;
        glm::mat4 lM = _mgr->_lhandMat * S;
        _quickShapes->drawCube(glm::value_ptr(lM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), lcol);
    }
    else if (_mgr->_lhandCursorType == _mgr->CURSOR_SPHERE) {
        glm::mat4 S = glm::mat4(1.0);
        S[0].x = 0.1;
        S[1].y = 0.1;
        S[2].z = 0.1;
        glm::mat4 lM = _mgr->_lhandMat * S;
        _quickShapes->drawSphere(glm::value_ptr(lM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), lcol);
    }
    else if (_mgr->_lhandCursorType == _mgr->CURSOR_LASER) {
        glm::mat4 S = glm::mat4(1.0);
        S[0].x = 0.03;
        S[1].y = 0.2;
        S[2].z = 0.03;
        glm::mat4 lM = _mgr->_lhandMat * glm::rotate(glm::mat4(1.0), -1.57f, glm::vec3(1,0,0)) * S;
        _quickShapes->drawCylinder(glm::value_ptr(lM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), lcol);
        S[0].x = 0.005;
        S[1].y = 1.5;
        S[2].z = 0.005;
        float lasercol[3] = {0.7, 0.7, 0.2};
        lM = _mgr->_lhandMat * glm::rotate(glm::mat4(1.0), -1.57f, glm::vec3(1,0,0)) * S *
             glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 1.0f, 0.0f));
        _quickShapes->drawCylinder(glm::value_ptr(lM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), lasercol);
    }

    if (_mgr->_rhandCursorType == _mgr->CURSOR_CUBE) {
        glm::mat4 S = glm::mat4(1.0);
        S[0].x = 0.1;
        S[1].y = 0.1;
        S[2].z = 0.1;
        glm::mat4 rM = _mgr->_rhandMat * S;
        _quickShapes->drawCube(glm::value_ptr(rM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), rcol);
    }
    else if (_mgr->_rhandCursorType == _mgr->CURSOR_SPHERE) {
        glm::mat4 S = glm::mat4(1.0);
        S[0].x = 0.1;
        S[1].y = 0.1;
        S[2].z = 0.1;
        glm::mat4 rM = _mgr->_rhandMat * S;
        _quickShapes->drawSphere(glm::value_ptr(rM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), rcol);
    }
    else if (_mgr->_rhandCursorType == _mgr->CURSOR_LASER) {
        glm::mat4 S = glm::mat4(1.0);
        S[0].x = 0.03;
        S[1].y = 0.2;
        S[2].z = 0.03;
        glm::mat4 rM = _mgr->_rhandMat * glm::rotate(glm::mat4(1.0), -1.57f, glm::vec3(1,0,0)) * S;
        _quickShapes->drawCylinder(glm::value_ptr(rM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), rcol);
        S[0].x = 0.005;
        S[1].y = 1.5;
        S[2].z = 0.005;
        float lasercol[3] = {0.7, 0.7, 0.2};
        rM = _mgr->_rhandMat * glm::rotate(glm::mat4(1.0), -1.57f, glm::vec3(1,0,0)) * S *
        glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 1.0f, 0.0f));
        _quickShapes->drawCylinder(glm::value_ptr(rM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), lasercol);
    }
    
}
