
#include "BentoBoxWidget.h"
#include "QuickShapes.h"


#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


BentoBoxWidget::BentoBoxWidget(int numInstances, glm::mat4 bentoToWorld,
                               float maxViewWidth, float maxViewHeight) :
    _numInstances(numInstances),
    _toWorld(bentoToWorld),
    _maxViewWidth(maxViewWidth),
    _maxViewHeight(maxViewHeight),
    _transition(NULL),
    _lastSysTime(-1.0),
    _voiSelectionActive(false)
{
    // Each row has its own view settings.  We'll start with just one row, so
    // initialize the array with one instance of the default settings.
    _viewSettings.push_back(BentoViewSettings());

    
    // Each colum will display one or more timesteps.
    // Intitialize to always display the very first timestep
    _criticalTimes.push_back(0.0);
    
    _scaleMat = glm::mat4(1.0);
    _transMat = glm::mat4(1.0);
}

BentoBoxWidget::~BentoBoxWidget() {

}


void BentoBoxWidget::animate(float currentSysTime) {
    if (_lastSysTime == -1.0) {
        _lastSysTime = currentSysTime;
        transitionToDefaultView();
    }
    
    if (_transition != NULL) {
        float a = (currentSysTime - _transition->startTime) / (_transition->endTime - _transition->startTime);
        if (a >= 1.0) {
            _transMat = glm::translate(glm::mat4(1.0), _transition->endTrans);
            _scaleMat[0].x = _transition->endScale;
            _scaleMat[1].y = _transition->endScale;
            _scaleMat[2].z = _transition->endScale;
            delete _transition;
            _transition = NULL;
        }
        else {
            glm::vec3 trans = glm::mix(_transition->startTrans, _transition->endTrans, a);
            _transMat = glm::translate(glm::mat4(1.0), trans);
            float scale = glm::mix(_transition->startScale, _transition->endScale, a);
            _scaleMat[0].x = scale;
            _scaleMat[1].y = scale;
            _scaleMat[2].z = scale;
        }
    }
    _lastSysTime = currentSysTime;
}



glm::vec3 BentoBoxWidget::centerOfBox(int r, int c) {
    int nrows = _viewSettings.size();
    if (getVOISelectionActive()) {
        nrows--;
    }
    int ncols = _numInstances * _criticalTimes.size();
    float rfloat = 0.0;
    if (nrows > 1) {
        rfloat = ((float)r/(float)(nrows-1) - 0.5) * (float)(nrows-1);
    }
    float cfloat = 0.0;
    if (ncols > 1) {
        cfloat = ((float)c/(float)(ncols-1) - 0.5) * (float)(ncols-1);
    }
    return glm::vec3(cfloat, 0.0, rfloat);
}



void BentoBoxWidget::transitionToDefaultView() {
    int nrows = _viewSettings.size();
    int ncols = _numInstances * _criticalTimes.size();
    transitionToView(0, 0, nrows-1, ncols-1);
}

void BentoBoxWidget::transitionToView(int row, int col) {
    transitionToView(row, col, row, col);
}
  
void BentoBoxWidget::transitionToView(int minRow, int minCol, int maxRow, int maxCol) {
    glm::vec3 center;
    int count = 0;
    for (int r = minRow; r <= maxRow; r++) {
        for (int c = minCol; c <= maxCol; c++) {
            center += centerOfBox(r,c);
            count++;
        }
    }
    center /= (float)count;
    glm::vec3 newTrans = -center;
    
    float sw = _maxViewWidth / (float)(maxCol - minCol + 1);
    float sh = _maxViewHeight / (float)(maxRow - minRow + 1);
    float newScale = glm::min(sw, sh);
    
    std::cout << newScale << std::endl;
    
    _transition = new Transition(_lastSysTime, _scaleMat[0].x, glm::vec3(_transMat[3]),
                                 _lastSysTime + 1.5, newScale, newTrans);
    
}




bool BentoBoxWidget::intersectSubVolume(const glm::vec3 &rayOrigin, const glm::vec3 &rayDir, int *hitRow, int *hitCol) {
    // TODO
    return false;
}



bool BentoBoxWidget::insideSubVolume(const glm::vec3 &testPt, int *hitRow, int *hitCol) {
    int nrows = _viewSettings.size();
    int ncols = _numInstances * _criticalTimes.size();
    for (int r = 0; r < nrows; r++) {
        for (int c = 0; c < ncols; c++) {
            glm::vec3 ctr = centerOfBox(r,c);
            float l = glm::length(testPt - ctr);
            if (l < 0.45) {  // subvols have diameter 0.9
                *hitRow = r;
                *hitCol = c;
                return true;
            }
        }
    }
    return false;
}



void BentoBoxWidget::addNewViewRow(int r, int c, glm::vec3 selectionPt, float selectionRad) {
    
    glm::vec3 ptInVolSpace = selectionPt - centerOfBox(r,c);
    float radInVolSpace = selectionRad / _scaleMat[0].x;
    
    BentoViewSettings settings = _viewSettings[r];
    glm::mat4 M = glm::scale(glm::mat4(1.0), glm::vec3(1.0f/radInVolSpace, 1.0f/radInVolSpace, 1.0f/radInVolSpace)) *
                  glm::translate(glm::mat4(1.0), -ptInVolSpace) * settings.getDataToBentoMat();
    settings.setDataToBentoMat(M);
    settings.setRowID(_viewSettings.size());
    _viewSettings.push_back(settings);
}






// -----------------------  Renderer Friend Class ---------------------------


BentoBoxWidgetRenderer::BentoBoxWidgetRenderer(BentoBoxWidget *widget, IBentoVolumeDrawer *volDrawer) :
    _bento(widget), _volDrawer(volDrawer)
{
    _quickShapes = new QuickShapes();
}

BentoBoxWidgetRenderer::~BentoBoxWidgetRenderer() {
    delete _quickShapes;
}


void BentoBoxWidgetRenderer::draw(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    
    glm::mat4 xform = _bento->_toWorld * _bento->_scaleMat * _bento->_transMat;
    
    // Draw cubbies
    float basecol[3] = {0.5, 0.5, 0.5};
    float highcol[3] = {1.0, 1.0, 0.76};
    glm::mat4 S = glm::mat4(1.0);
    S[0].x = 0.5;
    S[1].y = 0.125;
    S[2].z = 0.5;
    
    int nrows = _bento->_viewSettings.size();
    if (_bento->getVOISelectionActive()) {
        nrows--;
    }
    int ncols = _bento->_numInstances * _bento->_criticalTimes.size();
    
    //std::cout << nrows << " " << ncols << std::endl;
    
    for (int r = 0; r < nrows; r++) {
        for (int c = 0; c < ncols; c++) {
            //std::cout << r << " " << c << std::endl;
            glm::vec3 ctr = _bento->centerOfBox(r,c);
            ctr.y = -0.35;
            glm::mat4 M = xform * glm::translate(glm::mat4(1.0), ctr) * S;
            if (_bento->isSelected(r,c)) {
                _quickShapes->drawCubbie(glm::value_ptr(M), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), highcol);
            }
            else {
                _quickShapes->drawCubbie(glm::value_ptr(M), glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), basecol);
            }
        }
    }
    
    // Draw sub-volumes in cubbies
    // Scale down just a tad to leave a gap between cubbies since each cubbie is exactly a 1 unit square
    S[0].x = 0.9;
    S[1].y = 0.9;
    S[2].z = 0.9;
    for (int r = 0; r < nrows; r++) {
        for (int i = 0; i < _bento->_numInstances; i++) {
            for (int t = 0; t < _bento->_criticalTimes.size(); t++) {
                int c = i*_bento->_criticalTimes.size() + t;
                glm::vec3 ctr = _bento->centerOfBox(r,c);
                glm::mat4 M = xform * glm::translate(glm::mat4(1.0), ctr) * S;
                _volDrawer->drawSubVolume(i, t, &_bento->_viewSettings[r], M, viewMatrix, projMatrix);
            }
        }
    }
}

    
void BentoBoxWidgetRenderer::drawBoundingSpheres(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glm::mat4 xform = _bento->_toWorld * _bento->_scaleMat * _bento->_transMat;
    
    float col[3] = {1.0, 1.0, 1.0};
    glm::mat4 S = glm::mat4(1.0);
    S[0].x = 0.9;
    S[1].y = 0.9;
    S[2].z = 0.9;
    int nrows = _bento->_viewSettings.size();
    if (_bento->getVOISelectionActive()) {
        nrows--;
    }
    int ncols = _bento->_numInstances * _bento->_criticalTimes.size();
    for (int r = 0; r < nrows; r++) {
        for (int c = 0; c < ncols; c++) {
            glm::vec3 ctr = _bento->centerOfBox(r,c);
            glm::mat4 M = xform * glm::translate(glm::mat4(1.0), ctr) * S;
            // scale because sphere is radius = 2.0
            glm::mat4 S2 = glm::mat4(1.0);
            S2[0].x = 0.5;
            S2[1].y = 0.5;
            S2[2].z = 0.5;
            _quickShapes->drawSphere(glm::value_ptr(M * S2), glm::value_ptr(viewMatrix),
                                     glm::value_ptr(projMatrix), col);
        }
    }
    
}

