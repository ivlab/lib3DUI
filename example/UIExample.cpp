/**
 This file is part of the MinVR Open Source Project, which is developed and
 maintained collaboratively by the University of Minnesota and Brown University.
 
 Copyright (c) 2016-2017 Regents of the University of Minnesota and Brown University.
 This software is distributed under the BSD-3 Clause license, which can be found
 at: http://github.minvr.org/blob/master/LICENSE.txt
 
 Original Author(s) of this File:
	Dan Keefe, 2017, University of Minnesota
	
 Author(s) of Significant Updates/Modifications to the File:
	...
 */


#include "UIExample.h"
#include "QuickShapes.h"

// OpenGL Headers
#if defined(WIN32)
#define NOMINMAX
#include <windows.h>
#include <GL/gl.h>
#elif defined(__APPLE__)
#define GL_GLEXT_PROTOTYPES
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <cmath>

#include <iostream>


QuickShapes QS;


/// This is a standin for Seth and Dan's Rendering Code, which should work
/// with the BentoBoxWidget as long as it can implement the IBentoVolumeDrawer
/// interface.
class YourVolumeRenderer : public IBentoVolumeDrawer {
public:
    void preDraw(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix) {
        // 1. setup offscreen buffer and set drawing for back faces only
        // 2. _bento->drawBoundingSpheres();
        // 3. grab depth image
        // 4. clear, set drawing for front faces only
        // 5. _bento->drawBoundingSpheres();
        // 6. grab depth image
    }
    
    void drawSubVolume(int instanceID, int timestep, IBentoViewSettings *viewSettings,
                       glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix) {
        
        // For each sub-volume we want to apply both the modelMatrix and a dataToBento matrix.
        // The modelMatrix is the transform for the whole BentoBoxWidget.
        // viewSettings.dataToBento is where we will store the trans, rot, and scale to
        // apply in order to get to the sub-volume that the user has selected.
        glm::mat4 M = modelMatrix * viewSettings->getDataToBentoMat();
        
        
        // Draw the "data" for this instance, timestep, and settings:
        glm::mat4 S = glm::mat4(1.0);
        S[0].x = 0.2;
        S[1].y = 0.2;
        S[2].z = 0.2;
        float col1[3] = {1.0, 0.7, 0.8};
        QS.drawCube(glm::value_ptr(M * glm::translate(glm::mat4(1.0), glm::vec3(-0.3,0,0)) * S),
                              glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), col1);
        float col2[3] = {0.0, 0.3, 0.8};
        QS.drawSphere(glm::value_ptr(M * glm::translate(glm::mat4(1.0), glm::vec3(-0.1,0.2,0)) * S),
                              glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), col2);
        float col3[3] = {0.3, 0.5, 0.3};
        QS.drawCylinder(glm::value_ptr(M * glm::translate(glm::mat4(1.0), glm::vec3(0.1,-0.1,0.1)) * S),
                              glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), col3);
    }
    
    void postDraw(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix) {
        // I don't think you will need to do anything here...
    }

};

YourVolumeRenderer gVolRend;







UIExample::UIExample(int argc, char** argv) : VRApp(argc, argv, "desktop.minvr") {
    // Desktop mode
    _rHandTrackerEvents.insert("FakeTracker1_Move");
    _lHandTrackerEvents.insert("FakeTracker2_Move");
    _rHandDownEvents.insert("KbdSpace_Down");
    _rHandUpEvents.insert("KbdSpace_Up");
    _lHandDownEvents.insert("KbdG_Down");
    _lHandUpEvents.insert("KbdG_Up");

    // IV/LAB Cave mode
    _rHandTrackerEvents.insert("RedStylus_Move");
    _lHandTrackerEvents.insert("BlueStylus_Move");
    _rHandDownEvents.insert("RedStylusFrontBtn_Down");
    _rHandUpEvents.insert("RedStylusFrontBtn_Up");
    _lHandDownEvents.insert("BlueStylusFrontBtn_Down");
    _lHandUpEvents.insert("BlueStylusFrontBtn_Up");

    // ...

    
    
    // For a vertical layout in the Cave:
    _bento = new BentoBoxWidget(9, glm::rotate(glm::mat4(1.0), 1.57f, glm::vec3(1,0,0)), 3.0, 2.0);
    
    // For a horizontal layout on a table:
    //_bento = new BentoBoxWidget(9, glm::mat4(1.0), 3.0, 2.0);
                                
    _bentoRend = new BentoBoxWidgetRenderer(_bento, &gVolRend);
    
    _uiMgr = new UIManager(_bento);
    _uiMgrRend = new UIManagerRenderer(_uiMgr);
}

UIExample::~UIExample()
{
}


void UIExample::onVREvent(const VREvent &event)
{
    // When working with MinVR, this is a very useful printout for debugging
    // input events.
    //event.print();
    
    
    if (_rHandDownEvents.find(event.getName()) != _rHandDownEvents.end()) {
        _uiMgr->rhandBtnDown();
    }
    else if (_rHandUpEvents.find(event.getName()) != _rHandUpEvents.end()) {
        _uiMgr->rhandBtnUp();
    }
    else if (_lHandDownEvents.find(event.getName()) != _lHandDownEvents.end()) {
        _uiMgr->lhandBtnDown();
    }
    else if (_lHandUpEvents.find(event.getName()) != _lHandUpEvents.end()) {
        _uiMgr->lhandBtnUp();
    }
    else if (_rHandTrackerEvents.find(event.getName()) != _rHandTrackerEvents.end()) {
        _uiMgr->rhandTrackerMove(glm::make_mat4(event.getDataAsFloatArray("Transform")));
    }
    else if (_lHandTrackerEvents.find(event.getName()) != _lHandTrackerEvents.end()) {
        _uiMgr->lhandTrackerMove(glm::make_mat4(event.getDataAsFloatArray("Transform")));
    }
    
    else if (event.getName() == "FrameStart") {
        float t = event.getDataAsFloat("ElapsedSeconds");
        _bento->animate(t);
    }
    else if (event.getName() == "KbdA_Down") {
        _bento->transitionToView(1,1, 2,2);
    }
    
}

    
void UIExample::onVRRenderGraphicsContext(const VRGraphicsState &renderState) {
    if (renderState.isInitialRenderCall()) {
        glEnable(GL_DEPTH_TEST);
        glClearDepth(1.0f);
        glDepthFunc(GL_LEQUAL);
        glClearColor(0.2, 0.2, 0.2, 1);
    }
}


void UIExample::onVRRenderGraphics(const VRGraphicsState &renderState) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    _uiMgrRend->draw(glm::make_mat4(renderState.getViewMatrix()),
                     glm::make_mat4(renderState.getProjectionMatrix()));

    _bentoRend->draw(glm::make_mat4(renderState.getViewMatrix()),
                     glm::make_mat4(renderState.getProjectionMatrix()));
}
