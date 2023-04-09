#include "EditionInputProcessor.h"
#include "Test/UI/EditorPanelUI.h"
#include "../RigidBodiesManager.h"
#include "../RigidBodyModel.h"
#include "../ShapesDrawNode.h"
#include "../OverallManager.h"


EditionInputProcessor::EditionInputProcessor() :draggedPoint(nullptr),
_touchDown(false)
{
    
}

void EditionInputProcessor::onMouseUp(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseUp(e);

    if (!_touchDown) return;
    _touchDown = false;

    //RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //if (model == nullptr) return;
    //
    //if ((*draggedPoint) != nullptr) {
    //    (*draggedPoint) = nullptr;
    ////    model.computePhysics();
    ////    screen.buildBody();
    //}
    //else if (_editorPanel->_screenInterface->mouseSelectP2 != nullptr) {//////////////
    //   
    //    //screen.selectedPoints.replaceBy(getPointsInSelection());
    //    //_editorPanel->selectedPointsReplaceBy();!!!!!!!!!!!!!!!!11
    //    loadSelectedPoints();
    //}
    //else {
    //    _editorPanel->selectedPoints.clear();
    //}
    //
    //_editorPanel->_screenInterface->mouseSelectP1 = nullptr;
    //_editorPanel->_screenInterface->mouseSelectP2 = nullptr;
    //_touchDown = false;

}

void EditionInputProcessor::onMouseMoved(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseMoved(e);

    //Nearest point calculation
    //{
    //    RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //    if (model == nullptr) return;
    //
    //    Vec2 p = e.mEvent->getLocationInView();
    //    //nearestPoint = nullptr;
    //
    //    if (_editorPanel->_screenInterface->nearestPoint != nullptr)
    //    {
    //        delete _editorPanel->_screenInterface->nearestPoint;
    //        _editorPanel->_screenInterface->nearestPoint = nullptr;
    //    }
    //
    //    float dist = 100 * 1; //canvas.worldCamera.zoom;
    //
    //    loadAllPoints();
    //
    //    for (Vec2 v : allPointsBuffer) {
    //        if (v.distanceSquared(p) < dist)
    //        {
    //            _editorPanel->_screenInterface->nearestPoint = new Vec2(v.x, v.y);
    //            //nearestPoint->set(v.x, v.y);
    //        }
    //    }
    //}

    //calculateNearestPoint(e.mEvent->getLocationInView());

    if (_touchDown)
        onMouseDragged(e);
    else
    {
        Vec2 p = e.mEvent->getLocationInView();
        _editorPanel->oManager->buffDelegate->applyNewInvTransform(&p);

        calculateNearestPoint(p);
    }
}

void EditionInputProcessor::onMouseDown(CustomMouseEvent e) 
{
    EditorInputProcessor::onMouseDown(e);

    _touchDown = e.mEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT;
    if (!_touchDown) return;
    
    //RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //if (model == nullptr) return;
    //
    //auto iScreen = _editorPanel->_screenInterface;
    //
    //Vec2 t = e.mEvent->getLocationInView();
    //_editorPanel->oManager->spaceConv->applyTInv(&t);
    //
    //_editorPanel->editorManager->validateNearestPoint(t);
    //
    //draggedPoint = &_editorPanel->editorManager->nearestPoint;
    //
    //if (*draggedPoint == nullptr) {
    //
    //    //auto v = iScreen->mouseSelectP1;
    //    //if (v == nullptr)iScreen->mouseSelectP1 = new Vec2();
    //
    //    _editorPanel->editorManager->mSel.p1.set(e.mEvent->getLocationInView());
    //
    //    //iScreen->mouseSelectP1->set(e.mEvent->getLocationInView());
    //    //_editorPanel->oManager->spaceConv->applyTInv(iScreen->mouseSelectP1);
    //}
    //else {
    //    //If dragged point is origin point
    //    if ((**draggedPoint)==model->origin) {
    //        //_editorPanel->selectedPoints.clear();
    //        _editorPanel->editorManager->selectedPoints.clear();
    //    }
    //    //If we clicked a point
    //    else if (!_editorPanel->editorManager->isSelectedPointsContain(**draggedPoint)) {
    //        
    //        _editorPanel->editorManager->selectedPointsReplaceBy(*draggedPoint);
    //
    //    }
    //}
}

void EditionInputProcessor::onMouseDragged(CustomMouseEvent e)
{
    CCLOG("Touch dragged!");

    //if (!_touchDown) return;
    //
    //RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //if (model == nullptr) return;
    //
    //if ((*draggedPoint) != nullptr) {
    //    
    //    Vec2 p = e.mEvent->getLocationInView();
    //    _editorPanel->oManager->buffDelegate->applyNewInvTransform(&p);
    //    //model.clearPhysics();
    //
    //    float dx = p.x - (*draggedPoint)->x;
    //    float dy = p.y - (*draggedPoint)->y;
    //    (*draggedPoint)->set((*draggedPoint)->x + dx, (*draggedPoint)->y + dy);
    //
    //    for (int i = 0; i < _editorPanel->selectedPoints.size(); i++) {
    //        Vec2* sp = _editorPanel->selectedPoints.at(i);
    //        if ((*sp) != **draggedPoint) 
    //            (*sp) += Vec2(dx, dy);
    //    }
    //
    //}
    //else {
    //
    //    Vec2 p = e.mEvent->getLocationInView();
    //    _editorPanel->oManager->buffDelegate->applyNewInvTransform(&p);
    //    
    //    Vec2** mSelP2 = &_editorPanel->_screenInterface->mouseSelectP2;
    //
    //    if (*mSelP2 == nullptr) *mSelP2 = new Vec2();
    //    (*mSelP2)->set(p);
    //}

}

//------------------
//Utility Methods
//------------------

void EditionInputProcessor::loadSelectedPoints()
{
    //RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //
    //Vec2** p1 = &_editorPanel->_screenInterface->mouseSelectP1;
    //Vec2** p2 = &_editorPanel->_screenInterface->mouseSelectP2;
    //
    //if (*p1 != nullptr && *p2 != nullptr) {
    //    Rect rect(
    //        min((*p1)->x, (*p2)->x),
    //        min((*p1)->y, (*p2)->y),
    //        abs((*p2)->x - (*p1)->x),
    //        abs((*p2)->y - (*p1)->y)
    //    );
    //
    //    loadAllPoints();
    //
    //    for (Vec2* p : allPointsBuffer) {
    //        
    //        if ((*p) == model->origin) continue;
    //        
    //        if (rect.containsPoint((*p)))
    //            _editorPanel->selectedPoints.push_back(p);
    //    }
    //}
}

void EditionInputProcessor::calculateNearestPointN(Vec2 mousePos)
{
    //RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //if (model == nullptr) return;
    //
    //Vec2 p = mousePos;
    ////nearestPoint = nullptr;
    //
    //if (_editorPanel->_screenInterface->nearestPoint != nullptr)
    //{
    //    Vec2** a = &_editorPanel->_screenInterface->nearestPoint;
    //    //delete _editorPanel->_screenInterface->nearestPoint;
    //    //delete *a;
    //    *a = nullptr;
    //}
    //
    //float dist = 100 * 1; //canvas.worldCamera.zoom;
    //
    //loadAllPoints();
    //
    //for (Vec2* v : allPointsBuffer) {
    //
    //
    //    if (v->distanceSquared(p) < dist)
    //    {
    //        _editorPanel->_screenInterface->nearestPoint = v;
    //    }
    //
    //}
}

void EditionInputProcessor::calculateNearestPoint(Vec2 mousePos)
{
    //RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //if (model == nullptr) return;
    //
    //Vec2 p = mousePos;
    //
    //if (_editorPanel->_screenInterface->nearestPoint != nullptr)
    //{
    //    Vec2** a = &_editorPanel->_screenInterface->nearestPoint;
    //    *a = nullptr;
    //}
    //
    //float dist = 100 * 1; //canvas.worldCamera.zoom;
    //
    //loadAllPoints();
    //
    //for (Vec2* v : allPointsBuffer) {
    //
    //    Vec2 tV = *v;
    //
    //    if (tV.distanceSquared(p) < dist)
    //    {
    //        _editorPanel->_screenInterface->nearestPoint = v;
    //    }
    //
    //}
}

void EditionInputProcessor::loadAllPoints()
{
    allPointsBuffer.clear();

    //RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //
    //for (ShapeModel* shape : model->_shapes) {
    //   
    //    for (int i = 0; i < shape->_vertices.size(); i++)
    //    {
    //        allPointsBuffer.push_back(&shape->_vertices.at(i));
    //    }
    //}
    ////Push origin
    //allPointsBuffer.push_back(&model->origin);
}


