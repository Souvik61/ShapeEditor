#include "EditionInputProcessorv3.h"
#include "Test/UI/EditorPanelUI.h"
#include "../RigidBodiesManager.h"
#include "../RigidBodyModel.h"
#include "../ShapesDrawNode.h"
#include "Test/OverallManager.h"


EditionInputProcessorv3::EditionInputProcessorv3() :draggedPoint(nullptr),
_touchDown(false)
{
    
}

void EditionInputProcessorv3::processPanning(CustomMouseEvent e)
{
    if (_editorPanel->_screenInterface->isRMBPressed())
    {
        //auto pN = _editorPanel->editorManager->pointsNode;
        Vec2 delta = e.mEvent->getLocationInView() - editManager->prevMousePoint;
        
        float sc = _editorPanel->oManager->spaceConv->scale;
        
        //_editorPanel->oManager->buffDelegate->addOffset(delta);
        //_editorPanel->oManager->buffDelegate->refreshMat();
        //_editorPanel->oManager->buffDelegate->validateNewTransform();
        
        //New!
        _editorPanel->oManager->spaceConv->addOffset(delta * (1 / sc));
        _editorPanel->oManager->spaceConv->validateMatrices();
    }
}

void EditionInputProcessorv3::processZooming(CustomMouseEvent e)
{
    float scrDt = e.mEvent->getScrollY() * -0.1f * 2;//<- scroll speed
    float sc = _editorPanel->oManager->spaceConv->scale + scrDt;
    sc = max(0.1f, sc);
    sc = min(10.0f, sc);

    //_editorPanel->oManager->buffDelegate->applyScale(sc);
    //_editorPanel->oManager->buffDelegate->refreshMat();
    //_editorPanel->oManager->buffDelegate->validateNewTransform();

    //New!
    _editorPanel->oManager->spaceConv->applyScale(sc);
    _editorPanel->oManager->spaceConv->validateMatrices();
}

void EditionInputProcessorv3::onMouseUp(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseUp(e);

    if (!_touchDown) return;
    _touchDown = false;
    
    RigidBodyModel* model = editManager->rbManager->getSelectedModel();
    if (model == nullptr) return;
    
    if (draggedPoint != nullptr) {
        draggedPoint = nullptr;
    
        //Set model as save dirty
        model->setSaveDirty(true);
        //Set model as phys dirty
        model->_isPhysDirty = true;
    }
    else if (editManager->mSel.isValid()) //If has a valid mouse selection on mouse up
    {
        editManager->selectPointsInMouseSelection();
    }
    else {
        editManager->selectedPoints.clear();
    }
    
    editManager->mSel.setZero();
    editManager->mSel.setValid(false);
    _touchDown = false;

}

void EditionInputProcessorv3::onMouseMoved(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseMoved(e);

    processPanning(e);

    if (_touchDown)
    {
        onMouseDragged(e);
    }
    else
    {
        Vec2 p = e.mEvent->getLocationInView();
        //_editorPanel->oManager->buffDelegate->applyNewInvTransform(&p);
        _editorPanel->oManager->spaceConv->applyTInv(&p);
    
        editManager->validateNearestPoint(p);
    }
}

void EditionInputProcessorv3::onMouseDown(CustomMouseEvent e) 
{
    EditorInputProcessor::onMouseDown(e);

    _touchDown = e.mEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT;
    if (!_touchDown) return;

    RigidBodyModel* model = editManager->rbManager->getSelectedModel();
    if (model == nullptr) return;
    
    auto iScreen = _editorPanel->_screenInterface;
    
    Vec2 t = e.mEvent->getLocationInView();
    _editorPanel->oManager->spaceConv->applyTInv(&t);
    editManager->validateNearestPoint(t);
    
    draggedPoint = editManager->nearestPoint;
    
    if (draggedPoint == nullptr) {
    
        //_editorPanel->editorManager->mSel.setValid(true);
        editManager->mSel.p1.set(e.mEvent->getLocationInView());
    
    }
    else {
        //If dragged point is origin point
        if ((*draggedPoint) == model->origin) {
            editManager->selectedPoints.clear();
        }
        //If we clicked a point
        else if (!editManager->isSelectedPointsContain(*draggedPoint)) {
    
            editManager->selectedPointsReplaceBy(draggedPoint);
        }
    }
}

void EditionInputProcessorv3::onMouseScroll(CustomMouseEvent e)
{
    processZooming(e);
}

void EditionInputProcessorv3::onMouseDragged(CustomMouseEvent e)
{
    if (!_touchDown) return;

    RigidBodyModel* model = editManager->rbManager->getSelectedModel();
    if (model == nullptr) return;
    
    auto editMan = editManager;
    
    if (draggedPoint != nullptr) {
        
        Vec2 p = e.mEvent->getLocationInView();
        //_editorPanel->oManager->buffDelegate->applyNewInvTransform(&p);
        _editorPanel->oManager->spaceConv->applyTInv(&p);
    
    
        float dx = p.x - draggedPoint->x;
        float dy = p.y - draggedPoint->y;
        draggedPoint->set(draggedPoint->x + dx, draggedPoint->y + dy);
    
        for (int i = 0; i < editMan->selectedPoints.size(); i++) {
            Vec2* sp = editMan->selectedPoints.at(i);
            if ((*sp) != *draggedPoint) 
                (*sp) += Vec2(dx, dy);
        }
    
        //CCLOG("x: %f,y: %f", draggedPoint->x, draggedPoint->y);
    
        //Set model as save dirty
        model->setSaveDirty(true);
        //Set model as phys dirty
        model->_isPhysDirty = true;
    }
    else {
    
        Vec2 p = e.mEvent->getLocationInView();
    
        editManager->mSel.setValid(true);
        editManager->mSel.p2.set(p);
    
    }
}

void EditionInputProcessorv3::onKeyUp(ax::EventKeyboard::KeyCode, ax::Event*)
{

}

void EditionInputProcessorv3::onKeyDown(ax::EventKeyboard::KeyCode k, ax::Event* e)
{
    if (k == EventKeyboard::KeyCode::KEY_DELETE)
    {
        editManager->removeSelectedPoints();
    }
}

