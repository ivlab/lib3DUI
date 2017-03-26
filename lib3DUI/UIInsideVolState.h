#ifndef UISCALINGSTATE_H
#define UISCALINGSTATE_H


#include <glm/glm.hpp>

#include "BentoBoxWidget.h"
#include "UIState.h"


class UIInsideVolState : public UIState {
public:
    UIInsideVolState(UIManager *uiMgr, BentoBoxWidget *bento);
    virtual ~UIInsideVolState();

    void enterState(STATE_ID fromState);
    void exitState();

    void lhandTrackerMove(glm::mat4 transform);
    void lhandBtnDown();
    void lhandTrackerDrag(glm::mat4 transform);
    void lhandBtnUp();

    void rhandTrackerMove(glm::mat4 transform);
    void rhandBtnDown();
    void rhandTrackerDrag(glm::mat4 transform);
    void rhandBtnUp();
    
private:
    BentoBoxWidget *_bento;
};

#endif
