
#ifndef BENTOBOXWIDGET_H
#define BENTOBOXWIDGET_H

#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

#include "3DUIPluginAbstractions.h"

#include "QuickShapes.h"


class BentoViewSettings : public IBentoViewSettings {
public:
    // constructor sets defaults
    BentoViewSettings() :
        showFlow(true),
        showWallStress(true),
        showLeadStress(true),
        dataToBento(glm::mat4(1.0)) {}
    
    bool getShowFlow() { return showFlow; }
    bool getShowWallStress() { return showWallStress; }
    bool getShowLeadStress() { return showLeadStress; }
    glm::mat4 getDataToBentoMat() { return dataToBento; }
    
    void setDataToBentoMat(const glm::mat4 &m) { dataToBento = m; }
    
private:
    bool showFlow;
    bool showWallStress;
    bool showLeadStress;
    glm::mat4 dataToBento;
    // voi = "volume of interest"
    std::vector<glm::vec3> voiPoints;
    std::vector<float> voiRads;
    std::vector<glm::vec3> voiColors; // for highlighting inside the vol
};



class BentoBoxWidgetRenderer;


class BentoBoxWidget : public IBentoBoxWidget {
friend BentoBoxWidgetRenderer;
public:

    // Creates a new widget with columns for numInstances data instances of time-varying data.
    // Timesteps are assumed to be discrete numbered ints, usually minTimestep is 0.  A volume
    // drawing interface is used to keep the widget generic -- anything rendering technique
    // that implements this interface may be used to display the subvolumes.
    BentoBoxWidget(int numInstances, glm::mat4 bentoToWorld,
                   float maxViewWidth, float maxViewHeight);
    
    virtual ~BentoBoxWidget();


    // Call once per frame.  This advances any active animations.  Pass the synchronized system time
    // from MinVR in here.
    void animate(float currentSysTime);


    // Starts an animated transition from the current view to the default view where the whole
    // widget is visible.
    void transitionToDefaultView();

    // Starts an animated transition from the current view to a new view that focuses on the
    // indicated sub-volume.
    void transitionToView(int row, int col);

    // Starts an animated transition from the current view to a new view that focuses on the
    // indicated rectangle of sub-volume.
    void transitionToView(int minRow, int minCol, int maxRow, int maxCol);

    glm::mat4 getBentoToWorldMat() { return _toWorld; }
    
    void setBentoToWorldMat(const glm::mat4 &bentoToWorld) { _toWorld = bentoToWorld; }
    
    glm::mat4 getSubVolumesToWorldMat() { return _toWorld * _scaleMat * _transMat; }
    
    
    glm::vec3 centerOfBox(int r, int c);
    
    // True if the ray intersects one of the subVolumes.  If true, then hitRow and hitCol
    // are set to the indices of that subvolume.
    bool intersectSubVolume(const glm::vec3 &rayOrigin, const glm::vec3 &rayDir, int *hitRow, int *hitCol);
    
    // True if testPt lies within a subVolume.  If true, then hitRow and hitCol
    // are set to the indices of that subvolume.
    bool insideSubVolume(const glm::vec3 &testPt, int *hitRow, int *hitCol);

    int getNumViewSettings() { return _viewSettings.size();}
    IBentoViewSettings & getViewSettings(int viewID) { return _viewSettings.at(viewID);}
    
    // parameters come from a VOI sphere defined interactively in a particular row, col.
    // the view settings are copied from that box and a new transformation is applied
    // to create a subvolume based on the point and radius
    void addNewViewRow(int r, int c, glm::vec3 selectionPt, float selectionRad);
    
    std::vector<float> getCriticalTimes() { return _criticalTimes; }
    
    bool isSelected(int r, int c) {
        glm::ivec2 test(r,c);
        std::vector<glm::ivec2>::iterator it = std::find(_selected.begin(), _selected.end(), test);
        return (it != _selected.end());
    }
    
    std::vector<glm::ivec2> getSelected() { return _selected; }
    
    void clearSelected() { _selected.clear(); }
    
    void addToSelected(int r, int c) { _selected.push_back(glm::ivec2(r,c)); }
    
    void removeFromSelected(int r, int c) {
        _selected.erase(std::remove(_selected.begin(), _selected.end(), glm::ivec2(r,c)), _selected.end());
    }
    
private:

    
    class Transition {
    public:
        Transition(float sTime, float sScale, glm::vec3 sTrans,
                   float eTime, float eScale, glm::vec3 eTrans) :
            startTime(sTime), startScale(sScale), startTrans(sTrans),
            endTime(eTime), endScale(eScale), endTrans(eTrans) {}
        
        float startTime;
        float startScale;
        glm::vec3 startTrans;

        float endTime;
        float endScale;
        glm::vec3 endTrans;
    };
    
    
    int _numInstances;
	std::vector<BentoViewSettings> _viewSettings;
	std::vector<float> _criticalTimes;
	glm::mat4 _toWorld;
    float _maxViewWidth;
    float _maxViewHeight;
    glm::mat4 _scaleMat;
    glm::mat4 _transMat;
    Transition *_transition;
    float _lastSysTime;
    std::vector<glm::ivec2> _selected;
};



class BentoBoxWidgetRenderer : public IBentoBoxWidgetRenderer {
public:
    BentoBoxWidgetRenderer(BentoBoxWidget *widget, IBentoVolumeDrawer *volDrawer);
    virtual ~BentoBoxWidgetRenderer();
    
    // Call once per eye.  This draws the entire widget, making calls to the BentoVolumeDrawer
    // passed to the constructor as needed in order to draw all the relevant sub-volumes.
    void draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);
    
    // Draws a white sphere around each subvolume
    void drawBoundingSpheres(glm::mat4 viewMatrix, glm::mat4 projMatrix);
    
    
private:
    BentoBoxWidget *_bento;
    QuickShapes *_quickShapes;
    IBentoVolumeDrawer *_volDrawer;
};




#endif