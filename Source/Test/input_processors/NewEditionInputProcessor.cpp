#include "NewEditionInputProcessor.h"
#include "Test/UI/EditorPanelUI.h"
#include "../RigidBodiesManager.h"
#include "../RigidBodyModel.h"
#include "../ShapesDrawNode.h"
#include "../OverallManager.h"


NewEditionInputProcessor::NewEditionInputProcessor() :draggedPoint(nullptr),
_touchDown(false)
{
    
}

void NewEditionInputProcessor::processPanning(CustomMouseEvent e)
{
    if (_editorPanel->_screenInterface->isRMBPressed())
    {
        //auto pN = _editorPanel->editorManager->pointsNode;
        //Vec2 delta = e.mEvent->getLocationInView() - _editorPanel->prevMousePoint;
        //
        //
        //_editorPanel->oManager->buffDelegate->addOffset(delta);
        //_editorPanel->oManager->buffDelegate->refreshMat();
        //_editorPanel->oManager->buffDelegate->validateNewTransform();
        //
        ////New!
        //_editorPanel->oManager->spaceConv->addOffset(delta);
        //_editorPanel->oManager->spaceConv->validateMatrices();
    }
}

void NewEditionInputProcessor::processZooming(CustomMouseEvent e)
{
    float scrDt = e.mEvent->getScrollY() * -0.1f;
    float sc = _editorPanel->oManager->spaceConv->scale + scrDt;
    sc = std::max(0.1f, sc);
    sc = std::min(10.0f, sc);

    _editorPanel->oManager->buffDelegate->applyScale(sc);
    _editorPanel->oManager->buffDelegate->refreshMat();
    _editorPanel->oManager->buffDelegate->validateNewTransform();

    //New!
    _editorPanel->oManager->spaceConv->applyScale(sc);
    _editorPanel->oManager->spaceConv->validateMatrices();
}

void NewEditionInputProcessor::onMouseUp(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseUp(e);

    if (!_touchDown) return;
    _touchDown = false;

    //RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //if (model == nullptr) return;
    //
    //if ((*draggedPoint) != nullptr) {
    //    (*draggedPoint) = nullptr;
    //
    //    //Set model as save dirty
    //    model->setSaveDirty(true);
    //    //Set model as phys dirty
    //    model->_isPhysDirty = true;
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

void NewEditionInputProcessor::onMouseMoved(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseMoved(e);

    processPanning(e);

    if (_touchDown)
        onMouseDragged(e);
    else
    {
        Vec2 p = e.mEvent->getLocationInView();
        _editorPanel->oManager->buffDelegate->applyNewInvTransform(&p);

        calculateNearestPoint(p);
    }
}

void NewEditionInputProcessor::onMouseDown(CustomMouseEvent e) 
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
    //calculateNearestPoint(t);
    //
    //draggedPoint = &iScreen->nearestPoint;
    //
    //if (*draggedPoint == nullptr) {
    //
    //    auto v = iScreen->mouseSelectP1;
    //    if (v == nullptr)iScreen->mouseSelectP1 = new Vec2();
    //
    //    iScreen->mouseSelectP1->set(e.mEvent->getLocationInView());
    //    _editorPanel->oManager->spaceConv->applyTInv(iScreen->mouseSelectP1);
    //}
    //else {
    //    //If dragged point is origin point
    //    if ((**draggedPoint)==model->origin) {
    //        _editorPanel->selectedPoints.clear();
    //    }
    //    //If we clicked a point
    //    else if (!_editorPanel->isSelectedPointsContain(**draggedPoint)) {
    //        
    //        _editorPanel->selectedPointsReplaceBy(*draggedPoint);
    //
    //    }
    //}
}

void NewEditionInputProcessor::onMouseScroll(CustomMouseEvent e)
{
    processZooming(e);
}

void NewEditionInputProcessor::onMouseDragged(CustomMouseEvent e)
{
    //CCLOG("Touch dragged!");

    if (!_touchDown) return;

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
    //    //Set model as save dirty
    //    model->setSaveDirty(true);
    //    //Set model as phys dirty
    //    model->_isPhysDirty = true;
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

void NewEditionInputProcessor::loadSelectedPoints()
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

void NewEditionInputProcessor::calculateNearestPointN(Vec2 mousePos)
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

void NewEditionInputProcessor::calculateNearestPoint(Vec2 mousePos)
{
    //RigidBodyModel* model = _editorPanel->_rbManager->getSelectedModel();
    //if (model == nullptr) return;
    //
    //Vec2 p = mousePos;
    ////_editorPanel->oManager->buffDelegate->applyNewInvTransform(&p);
    //
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
    //    Vec2 tV = *v;
    //    //_editorPanel->oManager->buffDelegate->applyNewTransform(&tV);
    //
    //    if (tV.distanceSquared(p) < dist)
    //    {
    //        _editorPanel->_screenInterface->nearestPoint = v;
    //    }
    //
    //}
}

void NewEditionInputProcessor::loadAllPoints()
{
    //allPointsBuffer.clear();
    //
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


