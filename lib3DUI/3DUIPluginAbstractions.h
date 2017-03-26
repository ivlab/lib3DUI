
#ifndef UIPLUGINABSTRACTIONS_H
#define UIPLUGINABSTRACTIONS_H

#include <glm/glm.hpp>

class IBentoViewSettings {
public:
    virtual bool getShowFlow() = 0;
    virtual bool getShowWallStress() = 0;
    virtual bool getShowLeadStress() = 0;
    virtual glm::mat4 getDataToBentoMat() = 0;
};


// Your volume renderer needs to implement this interface to work with BentoBox
class IBentoVolumeDrawer {
public:
    virtual void preDraw(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix) = 0;
	virtual void drawSubVolume(int instanceID, int timestep, IBentoViewSettings *viewSettings,
                               glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix) = 0;
    virtual void postDraw(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix) = 0;
};


class IBentoBoxWidget {
public:
    // Call once per frame.  This advances any active animations.  Pass the synchronized system time
    // from MinVR in here.
    virtual void animate(float currentSysTime) = 0;
    virtual int getNumViewSettings() = 0;
    virtual IBentoViewSettings & getViewSettings(int viewID) = 0;
};


class IBentoBoxWidgetRenderer {
public:
    // Call once per eye.  This draws the entire widget, making calls to the BentoVolumeDrawer
    // passed to the constructor as needed in order to draw all the relevant sub-volumes.
    virtual void draw(glm::mat4 viewMatrix, glm::mat4 projMatrix) = 0;
    
    // Draws a white sphere around each subvolume
    virtual void drawBoundingSpheres(glm::mat4 viewMatrix, glm::mat4 projMatrix) = 0;
};



class IUIManager {
public:

    // Tracker move event
    virtual void rhandTrackerMove(glm::mat4 transform) = 0;
    
    // Called when the rhand button is pressed
    virtual void rhandBtnDown() = 0;
    
    // Called when the brush button is released.
    virtual void rhandBtnUp() = 0;
    
    
    // Tracker move event
    virtual void lhandTrackerMove(glm::mat4 transform) = 0;
    
    // Called when the hand button is pressed
    virtual void lhandBtnDown() = 0;
    
    // Called when the hand button is released.
    virtual void lhandBtnUp() = 0;
};



class IUIManagerRenderer {
public:

    virtual void draw(glm::mat4 viewMatrix, glm::mat4 projMatrix) = 0;
};



#endif