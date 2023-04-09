#include "PlayInputProcessor.h"
#include "Test/UI/EditorPanelUI.h"
#include "../RigidBodiesManager.h"
#include "../RigidBodyModel.h"
#include "../ShapesDrawNode.h"
#include "../EditorManager.h"
#include "../PointSpaceNode.h"
#include "Test/OverallManager.h"

void PlayInputProcessor::onMouseUp(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseUp(e);
}

void PlayInputProcessor::onMouseMoved(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseMoved(e);

    processPanning(e);
}

void PlayInputProcessor::onMouseDown(CustomMouseEvent e)
{
    EditorInputProcessor::onMouseDown(e);

    if (e.mEvent->getMouseButton() != EventMouse::MouseButton::BUTTON_LEFT)
        return;
}

void PlayInputProcessor::onMouseScroll(CustomMouseEvent e)
{
    processZooming(e);
}

void PlayInputProcessor::processPanning(CustomMouseEvent e)
{
    if (_editorPanel->_screenInterface->isRMBPressed())
    {
        
    }
}

void PlayInputProcessor::processZooming(CustomMouseEvent e)
{
    

}
