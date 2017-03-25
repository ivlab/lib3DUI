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


#ifndef UIEXAMPLE_H
#define UIEXAMPLE_H


#include <api/MinVR.h>
using namespace MinVR;

#include <glm/glm.hpp>
#include <vector>
#include <set>

#include "BentoBoxWidget.h"


/** This example program is meant to illustrate how to create a MinVR program
    that includes an interesting 3D user interface.  Here, the user interface
    assumes that each hand holds a 6 DOF tracker with one button on it.  A
    3D cursor follows each hand -- the right hand cursor is a paintbrush, and
    the left hand is a cube.  When the right hand button is pressed and held
    then the brush begins to paint a trail of multi-colored spherical "3D paint
    blobs".  When the left hand button is pressed and held, this "grabs onto"
    the entire 3D painting so that the user can then translate and rotate
    the scene.  The interface is a super-simplified version of the CavePainting
    tool (Keefe et al., 2001) and recently seen in TiltBrush and similar tools.
 */
class UIExample : public VRApp {
public:
    
    /** The constructor passes argc and argv on to VRApp.
     */
    UIExample(int argc, char** argv);
    virtual ~UIExample();

    /** This is the critical function to override in a MinVR app that has an
        interesting user interface.
     */
    void onVREvent(const VREvent &event);

    /** Override this function to initialize graphics (load textures, etc.)
     */
    void onVRRenderGraphicsContext(const VRGraphicsState &renderState);

    /** Override this function to actually draw the graphics each frame.
     */
    void onVRRenderGraphics(const VRGraphicsState &renderState);
    
private:

    // Sets of event names that will trigger right hand tracking, left hand
    // tracking, painting, and grabbing.  These are sets of names rather than
    // just a single name so that you can easily run the program in different
    // modes, such as in a Cave, Vive, Oculus, zSpace, desktop.
    std::set< std::string > _rHandTrackerEvents;
    std::set< std::string > _lHandTrackerEvents;
    std::set< std::string > _paintOnEvents;
    std::set< std::string > _paintOffEvents;
    std::set< std::string > _grabOnEvents;
    std::set< std::string > _grabOffEvents;
    
    // Transformation matrices for the left hand and right hand
    glm::mat4 _lhand;
    glm::mat4 _rhand;

    // UI state:  Painting is true when the right hand button is held down,
    // Grabbing is true when the left hand button is held down.
    bool _grabbing;
    bool _painting;

    // Transforms paint blobs to "room" space (the fixed physical space of
    // the room as defined by the coordinate system of the VR trackers).
    glm::mat4 _paintingToRoom;

    class PaintBlob {
    public:
        glm::mat4 trans;
        float rad;
        float color[3];
    };
    std::vector<PaintBlob> _paintBlobs;
    
    BentoBoxWidget *_bento;
    BentoBoxWidgetRenderer *_bentoRend;

};


#endif
