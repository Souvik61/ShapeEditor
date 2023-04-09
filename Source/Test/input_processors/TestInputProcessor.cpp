#include "TestInputProcessor.h"
#include "Test/UI/EditorPanelUI.h"
#include "../RigidBodiesManager.h"
#include "../RigidBodyModel.h"
#include "../ShapesDrawNode.h"
#include "../OverallManager.h"


TestInputProcessor::TestInputProcessor()
{
    
}

void TestInputProcessor::onMouseUp(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseUp(e);

    CCLOG("Its working");

    if (b2dManager)
        b2dManager->onMouseUp(e.mEvent);
}

void TestInputProcessor::onMouseMoved(CustomMouseEvent e)
{
	EditorInputProcessor::onMouseMoved(e);

    //processPanning(e);

    if (b2dManager)
        b2dManager->onMouseMove(e.mEvent);
}

void TestInputProcessor::onMouseDown(CustomMouseEvent e) 
{
    EditorInputProcessor::onMouseDown(e);

    if (b2dManager)
        b2dManager->onMouseDown(e.mEvent);
}

void TestInputProcessor::onMouseScroll(CustomMouseEvent e)
{
    //processZooming(e);

    if (b2dManager)
        b2dManager->onMouseScroll(e.mEvent);
}

void TestInputProcessor::onMouseDragged(CustomMouseEvent e)
{

}

//------------------
//Utility Methods
//------------------

void TestInputProcessor::processPanning(CustomMouseEvent)
{
}

void TestInputProcessor::processZooming(CustomMouseEvent)
{
    //CCLOG("Its working");
}


