#ifndef UIMANAGER_H
#define UIMANAGER_H


#include "3DUIPluginAbstractions.h"
#include "UIState.h"
#include "QuickShapes.h"


class UIManagerRenderer;

class UIManager : public IUIManager {
friend UIManagerRenderer;
public:
    
    enum UI_STATE {
        START_STATE = 0,
        INKING_STATE = 1,
        GRABBING_STATE = 2
    };
    
    
    enum CURSOR_TYPE {
        CURSOR_LASER = 0,
        CURSOR_SPHERE = 1,
        CURSOR_CUBE = 2
    };
    
    UIManager();
    virtual ~UIManager();
    
    
    void setState(UI_STATE newState);
    
    // Tracker move event
    void rhandTrackerMove(glm::mat4 transform);
    
    // Called when the rhand button is pressed
    void rhandBtnDown();
    
    // Called when the brush button is released.
    void rhandBtnUp();
    
    
    // Tracker move event
    void lhandTrackerMove(glm::mat4 transform);
    
    // Called when the hand button is pressed
    void lhandBtnDown();
    
    // Called when the hand button is released.
    void lhandBtnUp();
    
private:
    
    UI_STATE  _currentStateID;
    UIState   *_currentState;
    
    CURSOR_TYPE _lhandCursorType;
    CURSOR_TYPE _rhandCursorType;
    
    bool _lhandDown;
    bool _rhandDown;
    
    glm::mat4 _lhandMat;
    glm::mat4 _rhandMat;
};



class UIManagerRenderer : public IUIManagerRenderer {
public:
    UIManagerRenderer(UIManager *mgr);
    virtual ~UIManagerRenderer();
    
    void draw(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix);
    
private:
    UIManager *_mgr;
    QuickShapes *_quickShapes;
};


#endif

