
#include "UIManager.h"
#include "QuickShapes.h"
#include "UIOverviewState.h"


#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


UIManager::UIManager(BentoBoxWidget *bento) :
    _lhandCursorType(CURSOR_CUBE),
    _rhandCursorType(CURSOR_LASER),
    _lhandDown(false),
    _rhandDown(false),
    _lhandMat(glm::mat4(1.0)),
    _rhandMat(glm::mat4(1.0))
{
    _overviewState = new UIOverviewState(this, bento);
    _currentState = _overviewState;
    _currentStateID = STATE_OVERVIEW;
}


UIManager::~UIManager() {
    delete _overviewState;
}
    
    
void UIManager::setState(UI_STATE newState) {
    if (newState == STATE_OVERVIEW) {
        _currentState->exitState();
        _currentStateID = STATE_OVERVIEW;
        _currentState = _overviewState;
        _currentState->enterState();
    }
    // ...
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
