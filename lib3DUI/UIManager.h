#ifndef UIMANAGER_H
#define UIMANAGER_H


#include "3DUIPluginAbstractions.h"
#include "BentoBoxWidget.h"
#include "UIStates.h"
#include "QuickShapes.h"


class UIManagerRenderer;

class UIManager : public IUIManager {
friend UIManagerRenderer;
public:

    enum CURSOR_TYPE {
        CURSOR_LASER = 0,
        CURSOR_SPHERE = 1,
        CURSOR_CUBE = 2
    };
    
    UIManager(BentoBoxWidget *bento);
    virtual ~UIManager();
    
    
    void setState(UIState::STATE_ID newState);
    
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
    
    glm::mat4 getLHandMat() { return _lhandMat; }
    
    glm::mat4 getRHandMat() { return _rhandMat; }
    
private:
    
    UIState::STATE_ID  _currentStateID;
    UIState   *_currentState;
    UIState   *_bothOutsideVol;
    UIState   *_dhInsideVol;
    UIState   *_ndhInsideVol;
    UIState   *_bothInsideVol;
    
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
    
    void draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);
    
private:
    UIManager *_mgr;
    QuickShapes *_quickShapes;
};


#endif

