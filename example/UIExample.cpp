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
    
    void drawSubVolume(int instanceID, int timestep, BentoViewSettings viewSettings,
                       glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix) {
        
        // For each sub-volume we want to apply both the modelMatrix and a dataToBento matrix.
        // The modelMatrix is the transform for the whole BentoBoxWidget.
        // viewSettings.dataToBento is where we will store the trans, rot, and scale to
        // apply in order to get to the sub-volume that the user has selected.
        glm::mat4 M = modelMatrix * viewSettings.dataToBento;
        
        
        // Draw the "data" for this instance, timestep, and settings:
        glm::mat4 S = glm::mat4(1.0);
        S[0].x = 0.2;
        S[1].y = 0.2;
        S[2].z = 0.2;
        float col1[3] = {1.0, 0.7, 0.8};
        QuickShapes::drawCube(glm::value_ptr(M * glm::translate(glm::mat4(1.0), glm::vec3(-0.3,0,0)) * S),
                              glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), col1);
        float col2[3] = {0.0, 0.3, 0.8};
        QuickShapes::drawSphere(glm::value_ptr(M * glm::translate(glm::mat4(1.0), glm::vec3(-0.1,0.2,0)) * S),
                              glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), col2);
        float col3[3] = {0.3, 0.5, 0.3};
        QuickShapes::drawCylinder(glm::value_ptr(M * glm::translate(glm::mat4(1.0), glm::vec3(0.1,-0.1,0.1)) * S),
                              glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), col3);
    }
    
    void postDraw(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix) {
        // I don't think you will need to do anything here...
    }

};

YourVolumeRenderer gVolRend;







UIExample::UIExample(int argc, char** argv) : VRApp(argc, argv),
    _grabbing(false), _painting(false), _paintingToRoom(glm::mat4(1.0))
{
    // Desktop mode
    _rHandTrackerEvents.insert("FakeTracker1_Move");
    _lHandTrackerEvents.insert("FakeTracker2_Move");
    _paintOnEvents.insert("KbdSpace_Down");
    _paintOffEvents.insert("KbdSpace_Up");
    _grabOnEvents.insert("KbdG_Down");
    _grabOffEvents.insert("KbdG_Up");

    // IV/LAB Cave mode
    _rHandTrackerEvents.insert("RedStylus_Move");
    _lHandTrackerEvents.insert("BlueStylus_Move");
    _paintOnEvents.insert("RedStylusFrontBtn_Down");
    _paintOffEvents.insert("RedStylusFrontBtn_Up");
    _grabOnEvents.insert("BlueStylusFrontBtn_Down");
    _grabOffEvents.insert("BlueStylusFrontBtn_Up");

    // ...

    
    
    _bento = new BentoBoxWidget(9, 0, 400, &gVolRend, glm::mat4(1.0), 3.0, 2.0);
}

UIExample::~UIExample()
{
    QuickShapes::freeGPUMemory();
}


void UIExample::onVREvent(const VREvent &event)
{
    // When working with MinVR, this is a very useful printout for debugging
    // input events.
    event.print();
    
    
    if (_paintOnEvents.find(event.getName()) != _paintOnEvents.end()) {
        _painting = true;
    }
    else if (_paintOffEvents.find(event.getName()) != _paintOffEvents.end()) {
        _painting = false;
    }
    else if (_grabOnEvents.find(event.getName()) != _grabOnEvents.end()) {
        _grabbing = true;
    }
    else if (_grabOffEvents.find(event.getName()) != _grabOffEvents.end()) {
        _grabbing = false;
    }
    else if (_rHandTrackerEvents.find(event.getName()) != _rHandTrackerEvents.end()) {
        _rhand = glm::make_mat4(event.getDataAsFloatArray("Transform"));
        if (_painting) {
            // Transform the right hand transform into "painting space"
            glm::mat4 roomToPainting = glm::inverse(_paintingToRoom);
            glm::mat4 handInPaintingSpace = roomToPainting * _rhand;
            
            // Create a new blob to add to the painting
            PaintBlob pb;
            // set the blob's transform based on the current hand transform
            pb.trans = handInPaintingSpace;
            // jitter the blob's position a bit so that blobs appear to come out
            // of the brush at a random location along the brush's bristles.
            float jitter = 0.5*((GLfloat)rand()/(GLfloat)RAND_MAX) - 0.25;
            pb.trans[3].x += jitter * pb.trans[0].x;
            pb.trans[3].y += jitter * pb.trans[0].y;
            pb.trans[3].z += jitter * pb.trans[0].z;
            
            // give the blob a random radius
            pb.rad = 0.01 + 0.1*((GLfloat)rand()/(GLfloat)RAND_MAX);
            
            // assign a color based on the position of the brush within the room
            float tmp;
            pb.color[0] = std::modf(_rhand[3].x, &tmp);
            pb.color[1] = std::modf(_rhand[3].y, &tmp);
            pb.color[2] = std::modf(_rhand[3].z, &tmp);
            
            _paintBlobs.push_back(pb);
        }
    }
    else if (_lHandTrackerEvents.find(event.getName()) != _lHandTrackerEvents.end()) {
        glm::mat4 newHand = glm::make_mat4(event.getDataAsFloatArray("Transform"));
        if (_grabbing) {
            // Update the paintingToRoom transform based upon the new transform
            // of the left hand relative to the last frame.
            _paintingToRoom = newHand * glm::inverse(_lhand) * _paintingToRoom;
        }
        _lhand = newHand;
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
    
    // Draw a cursor for the left hand
    const GLfloat lcolor [] = {0.8, 0.5, 0.5};
    glm::mat4 scaleHandCursor = glm::mat4(1.0);
    scaleHandCursor[0].x = 0.25;
    scaleHandCursor[1].y = 0.25;
    scaleHandCursor[2].z = 0.25;
    glm::mat4 lHandScaled = _lhand * scaleHandCursor;
    QuickShapes::drawCube(glm::value_ptr(lHandScaled), renderState.getViewMatrix(), renderState.getProjectionMatrix(), lcolor);
    
    // Draw a cursor for the right hand
    const float rcolor [] = {0.5, 0.5, 0.8};
    QuickShapes::drawBrush(glm::value_ptr(_rhand), renderState.getViewMatrix(), renderState.getProjectionMatrix(), rcolor);
    
    // Draw the "painting"
    for (int i=0; i<_paintBlobs.size(); i++) {
        glm::mat4 S = glm::mat4(1.0);
        S[0].x = _paintBlobs[i].rad;;
        S[1].y = _paintBlobs[i].rad;;
        S[2].z = _paintBlobs[i].rad;;
        glm::mat4 M = _paintingToRoom * _paintBlobs[i].trans * S;
        QuickShapes::drawSphere(glm::value_ptr(M), renderState.getViewMatrix(), renderState.getProjectionMatrix(), _paintBlobs[i].color);
    }
    
    _bento->draw(glm::rotate(glm::mat4(1.0), 1.57f, glm::vec3(1,0,0)), glm::make_mat4(renderState.getViewMatrix()), glm::make_mat4(renderState.getProjectionMatrix()));
}
