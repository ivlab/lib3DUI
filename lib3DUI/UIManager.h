#ifndef UIMANAGER_H
#define UIMANAGER_H


#include "UIState.h"


class UIManager {
public:
    
    enum UI_STATE {
        START_STATE = 0,
        INKING_STATE = 1,
        GRABBING_STATE = 2
    };
    
    
    UIManager();
    virtual ~UIManager();
    
    
    void setState(UI_STATE newState);
    
    // Tracker move event called when the brush button is not depressed
    void rhandTrackerMove(glm::mat4 transform);
    
    // Called when the brush button is pressed, typically to begin a draw operation
    void rhandBtnDown();
    
    // Tracker move event called when the brush button is depressed
    void rhandTrackerDrag(glm::mat4 transform);
    
    // Called when the brush button is released.
    void rhandBtnUp();
    
    
    // Tracker move event called when the hand button is not depressed
    void lhandTrackerMove(glm::mat4 transform);
    
    // Called when the hand button is pressed, typically to begin a grab operation
    void lhandBtnDown();
    
    // Tracker move event called when the hand button is depressed
    void lhandTrackerDrag(glm::mat4 transform);
    
    // Called when the hand button is released.
    void lhandBtnUp();
    
private:
    
    UI_STATE  _currentStateID;
    UIState   *_currentState;
    
};

#endif

