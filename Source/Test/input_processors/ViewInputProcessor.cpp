#include "ViewInputProcessor.h"
#include "Test/UI/EditorPanelUI.h"
#include "../RigidBodiesManager.h"
#include "../RigidBodyModel.h"
#include "../ShapesDrawNode.h"
#include "../EditorManager.h"
#include "../PointSpaceNode.h"
#include "Test/OverallManager.h"

void ViewInputProcessor::onMouseUp(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseUp(e);
}

void ViewInputProcessor::onMouseMoved(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseMoved(e);

    processPanning(e);
}

void ViewInputProcessor::onMouseDown(CustomMouseEvent e)
{
    EditorInputProcessor::onMouseDown(e);

    if (e.mEvent->getMouseButton() != EventMouse::MouseButton::BUTTON_LEFT)
        return;
}

void ViewInputProcessor::onMouseScroll(CustomMouseEvent e)
{
    processZooming(e);
}

void ViewInputProcessor::processPanning(CustomMouseEvent e)
{
    if (_editorPanel->_screenInterface->isRMBPressed())
    {
        auto pN = editManager->pointsNode;
        Vec2 delta = e.mEvent->getLocationInView() - editManager->prevMousePoint;
        
        float sc = _editorPanel->oManager->spaceConv->scale;
        
        //pN->setPosition(pN->getPosition() + delta);
        //_editorPanel->oManager->buffDelegate->addOffset(delta);
        //_editorPanel->oManager->buffDelegate->refreshMat();
        //_editorPanel->oManager->buffDelegate->validateNewTransform();
        
        //New!
        _editorPanel->oManager->spaceConv->addOffset(delta * (1 / sc));
        _editorPanel->oManager->spaceConv->validateMatrices();
    }
}

void ViewInputProcessor::processZooming(CustomMouseEvent e)
{
    float scrDt = e.mEvent->getScrollY() * -0.1f * 2;//<-scroll speed
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
