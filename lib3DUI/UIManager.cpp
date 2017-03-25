
#include "UIManager.h"
#include "QuickShapes.h"


#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

UIManager::UIManager() :
    _lhandDown(false),
    _rhandDown(false),
    _lhandMat(glm::mat4(1.0)),
    _rhandMat(glm::mat4(1.0))
{
    
}


UIManager::~UIManager() {
    
}
    
    
void UIManager::setState(UI_STATE newState) {
    
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
}

void UIManager::lhandBtnUp() {
	_currentState->lhandBtnUp();
}


// --------------------- Friend Renderer Class ----------------------


UIManagerRenderer::UIManagerRenderer(UIManager *mgr) : _mgr(mgr) {
    _quickShapes = new QuickShapes();
}

UIManagerRenderer::~UIManagerRenderer() {
    delete _quickShapes;
}


void UIManagerRenderer::draw(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    
    float lcol[3] = {0.7, 0.2, 0.2};
    float rcol[3] = {0.2, 0.2, 0.7};
    
    glm::mat4 S = glm::mat4(1.0);
    S[0].x = 0.25;
    S[1].y = 0.25;
    S[2].z = 0.25;
    
    glm::mat4 lM = modelMatrix * _mgr->_lhandMat * S;
    _quickShapes->drawCube(glm::value_ptr(lM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), lcol);

    glm::mat4 rM = modelMatrix * _mgr->_rhandMat * S;
    _quickShapes->drawCube(glm::value_ptr(rM), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), rcol);
    
}
