#ifndef UISTATE_H
#define UISTATE_H

#include "BentoBoxWidget.h"
#include <glm/glm.hpp>

class UIManager;


/** Following the State Design Pattern, this class defines callbacks for the 
    UI events that must be handled for all of the states the the Pen3D system.
    Concrete implementations of this base class are then used to define the
    specific behavior given the current state. */ 
class UIState {
public:
    
    enum STATE_ID {
        STATE_BOTHOUTSIDE = 0,
        STATE_DHINSIDE = 1,
        STATE_NDHINSIDE = 2,
        STATE_BOTHINSIDE = 3
    };
    
	UIState(UIManager *uiMgr, BentoBoxWidget *bento) :
        _uiMgr(uiMgr), _bento(bento) {}
	virtual ~UIState() {}

	virtual void enterState(STATE_ID fromState) {}
	virtual void exitState() {}

	virtual void lhandTrackerMove(glm::mat4 transform) {}
	virtual void lhandBtnDown() {}
	virtual void lhandTrackerDrag(glm::mat4 transform) {}
	virtual void lhandBtnUp() {}

	virtual void rhandTrackerMove(glm::mat4 transform) {}
	virtual void rhandBtnDown() {}
	virtual void rhandTrackerDrag(glm::mat4 transform) {}
	virtual void rhandBtnUp() {}

protected:
	UIManager *_uiMgr;
    BentoBoxWidget *_bento;
};



// BothOutsideVol:  Both cursors are outside of the bento box
// DH: laser pointer that highlights the current box, click and release
//     transitions view to that box, click and hold allows for multiple selection,
//     click and release with nothing selected transitions to overview
// NDH: translate entire bento, scale entire bento if DH btn is pressed
class BothOutsideVol : public UIState {
public:
    BothOutsideVol(UIManager *uiMgr, BentoBoxWidget *bento);
    virtual ~BothOutsideVol();
    
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
    bool _grabbing;
};


// DHInsideVol:  DH inside volume, NDH outside
// DH: define VOI
// NDH: nothing (for now)
class DHInsideVol : public UIState {
public:
    DHInsideVol(UIManager *uiMgr, BentoBoxWidget *bento);
    virtual ~DHInsideVol();
    
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
    glm::vec3 _spherePt;
    float _sphereRad;
};


// NDHInsideVol:  DH outside volume, NDH inside
// DH: nothing (for now)
// NDH: translate and rotate data, scale if DH btn is pressed while active
class NDHInsideVol : public UIState {
public:
    NDHInsideVol(UIManager *uiMgr, BentoBoxWidget *bento);
    virtual ~NDHInsideVol();
    
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
    
};


// BothInsideVol:  DH inside volume, NDH inside volume
// DH: define VOI
// NDH: translate and rotate data, scale if DH btn is pressed while active
class BothInsideVol : public UIState {
public:
    BothInsideVol(UIManager *uiMgr, BentoBoxWidget *bento);
    virtual ~BothInsideVol();
    
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
    glm::vec3 _spherePt;
    float _sphereRad;
};



#endif
