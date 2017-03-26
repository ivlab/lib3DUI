#ifndef UIOVERVIEWSTATE_H
#define UIOVERVIEWSTATE_H


#include <glm/glm.hpp>

#include "BentoBoxWidget.h"
#include "UIState.h"


class UIOverviewState : public UIState {
public:
    UIOverviewState(UIManager *uiMgr, BentoBoxWidget *bento);
    virtual ~UIOverviewState();

    void enterState();
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
