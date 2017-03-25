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
#include "UIManager.h"


/** 
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
    std::set< std::string > _lHandDownEvents;
    std::set< std::string > _lHandUpEvents;
    std::set< std::string > _rHandDownEvents;
    std::set< std::string > _rHandUpEvents;
    
    
    BentoBoxWidget *_bento;
    BentoBoxWidgetRenderer *_bentoRend;

    UIManager *_uiMgr;
    UIManagerRenderer *_uiMgrRend;
    
};


#endif
