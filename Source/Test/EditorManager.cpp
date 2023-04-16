#include "EditorManager.h"
#include "PointSpaceNode.h"
#include "Test/UI/EditorPanelUI.h"
#include "RigidBodyModel.h"
#include "RigidBodiesManager.h"
#include "Test/UI/EditorScreenInterface.h"
#include "OverallManager.h"
#include "draw/EditorDraw.h"
#include "Test/input_processors/CreationInputProcessor.h"
#include "Test/input_processors/EditorInputProcessor.h"
#include "Test/input_processors/TestInputProcessor.h"
#include "Test/input_processors/ViewInputProcessor.h"
#include "Test/input_processors/EditionInputProcessorv3.h"

USING_NS_AX;

// on "init" you need to initialize your instance
bool EditorManager::init()
{
	//_pointsNode = PointSpaceNode::create();
	//addChild(_pointsNode);

    nearestPoint = nullptr;
    _hasNearClosePt = false;
	
    //Initially change mode to view
    //changeMode(EditorMode::VIEW);



	return true;
}

void EditorManager::resetPointSpace()
{
	//pointsNode->setPosition(editorUI->getWorldViewPortMidpoint());
}

void EditorManager::validateNearestPoint(const Vec2& pt)
{
    RigidBodyModel* model = rbManager->getSelectedModel();
    if (model == nullptr) return;

    Vec2 p = pt;

    //if (editorUI->_screenInterface->nearestPoint != nullptr)
    //{
    //    Vec2** a = &_editorPanel->_screenInterface->nearestPoint;
    //    *a = nullptr;
    //}

    nearestPoint = nullptr;

    float dist = 100 * 1; //canvas.worldCamera.zoom;


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

    for (ShapeModel* shape : model->_shapes) {

        for (int i = 0; i < shape->_vertices.size(); i++)
        {
            Vec2* v = &shape->_vertices.at(i);
            
            if (v->distanceSquared(p) < dist)
            {
                nearestPoint = v;
            }
        }
    }

}

bool EditorManager::isSelectedPointsContain(Vec2 p)
{
    size_t s = selectedPoints.size();

    for (size_t i = 0; i < s; i++)
    {
        if ((*selectedPoints[i]) == p) //Could be used fuzzy equals
            return true;
    }
    return false;
}

void EditorManager::selectedPointsReplaceBy(Vec2* p)
{
    selectedPoints.clear();
    selectedPoints.push_back(p);
}

void EditorManager::selectPointsInMouseSelection()
{
    RigidBodyModel* model = rbManager->getSelectedModel();

    //Not sure if its required
    selectedPoints.clear();

    Vec2 p1 = mSel.p1;
    Vec2 p2 = mSel.p2;

    //Convert both to logic space
    editorUI->oManager->spaceConv->applyTInv(&p1);
    editorUI->oManager->spaceConv->applyTInv(&p2);

    if (mSel.isValid()) 
    {
        Rect rect(
            min(p1.x, p2.x),
            min(p1.y, p2.y),
            abs(p2.x - p1.x),
            abs(p2.y - p1.y)
        );

        for (ShapeModel* shape : model->_shapes) {//for each shape

            for (int i = 0; i < shape->_vertices.size(); i++)
            {
                Vec2* p = &shape->_vertices.at(i);

                if (rect.containsPoint(*p))
                {
                    selectedPoints.push_back(p);
                }
            }
        }
    }
}

void EditorManager::removeSelectedPoints()
{
    if (!isRemoveEnabled())
        return;

    auto& shapes = oManager->rbManager->getSelectedModel()->_shapes;
    
    //Make a copy of the original selected points
    std::vector<Vec2> selCopy;
    selCopy.reserve(selectedPoints.size());
    for (Vec2* p : selectedPoints) 
    {
        selCopy.push_back(*p);
    }

    for (int i = shapes.size() - 1; i >= 0; i--) { //For each shape in selected rb
        ShapeModel* shape = shapes.at(i);

        for (Vec2 p : selCopy) { //For each selected point

            //Check if p is found in shapes vertices
            bool f = (std::find(shape->_vertices.begin(), shape->_vertices.end(), p) != shape->_vertices.end());

            if (f) {
                auto it = std::find(shape->_vertices.begin(), shape->_vertices.end(), p);
                shape->_vertices.erase(it);
            }
        }

        if (shape->_vertices.empty())
            shapes.erase(i);

    }

    selectedPoints.clear();
    oManager->rbManager->getSelectedModel()->computePhysics();

}

bool EditorManager::isRemoveEnabled()
{
    if (oManager->rbManager->getSelectedModel() == nullptr)
        return false;
    return !selectedPoints.empty();
}

void EditorManager::setNearestClosingPt(bool avail,const ax::Vec2& v)
{
    _hasNearClosePt = avail;
    nearClosePt = v;
}

//-------------------
//Events
//-------------------


//------------------------
//--Mouse Input functions
//------------------------

void EditorManager::onMouseUp(EventMouse* e)
{
    CustomMouseEvent mEve = { CustomMouseEvent::EventType::UP,e };
    //_rbManager->onMouseInteractionFromEditor(mEve, _mode);

    if (_currentInputProcessor)
        _currentInputProcessor->onMouseUp(mEve); //Send event to input processor
}

void EditorManager::onMouseMoved(EventMouse* e)
{
    //_mousePointer->setOpacity(255);
    //_mousePointer->setPosition(e->getLocationInView());

    //Send event to rigidbodies manager
    CustomMouseEvent mEve = { CustomMouseEvent::EventType::MOVED,e };
    //_rbManager->onMouseInteractionFromEditor(mEve, _mode);

    if (_currentInputProcessor)
        _currentInputProcessor->onMouseMoved(mEve); //Send event to input processor
    prevMousePoint = e->getLocationInView();
}

void EditorManager::onMouseDown(EventMouse* e)
{
    //Send event to rigidbodies manager
    CustomMouseEvent mEve = { CustomMouseEvent::EventType::DOWN,e };
    // _rbManager->onMouseInteractionFromEditor(mEve, _mode);

    if (_currentInputProcessor)
        _currentInputProcessor->onMouseDown(mEve); //Send event to input processor
}

void EditorManager::onMouseScroll(cocos2d::EventMouse* e)
{
    //Send event
    CustomMouseEvent mEve = { CustomMouseEvent::EventType::MOVED,e };
    //_rbManager->onMouseInteractionFromEditor(mEve, _mode);

    //@todo again send this event to editor manager for proper processing
    if (_currentInputProcessor)
        _currentInputProcessor->onMouseScroll(mEve); //Send event to input processor
}

//---------------------------
//--Keyboard Input functions
//---------------------------

void EditorManager::onKeyDown(EventKeyboard::KeyCode k, Event* e)
{
    if (k == EventKeyboard::KeyCode::KEY_M)
    {
        //changeMode();
        changeModeCycle();
    }
    else if (k == EventKeyboard::KeyCode::KEY_DELETE)//Why is this here? change it
    {
        removeSelectedPoints();
    }
}

void EditorManager::onKeyUp(EventKeyboard::KeyCode, Event*)
{
}

//-------------------
//Others
//-------------------

void EditorManager::setInputProcessor(EditorInputProcessor* p)
{
    _currentInputProcessor = p;
    _currentInputProcessor->setEditorPanel(editorUI);
    _currentInputProcessor->setEditorManager(this);
}

void EditorManager::changeMode()
{
    //CC_SAFE_DELETE(_currentInputProcessor);
    //
    //_mode = EditorMode((_mode + 1) % 3);
    //_mode = EditorMode((_mode == 0) ? 1 : _mode);
    //
    //switch (_mode)
    //{
    //case VIEW:
    //    break;
    //case CREATE:
    //{
    //    auto p = new CreationInputProcessor();
    //    setInputProcessor(p);
    //    _modeLabel->setString("Mode: Create");
    //}break;
    //case EDIT:
    //{
    //    auto p = new NewEditionInputProcessor();
    //    setInputProcessor(p);
    //    _modeLabel->setString("Mode: Edit");
    //}   break;
    //case TEST:
    //{
    //    _modeLabel->setString("Mode: Test");
    //}   break;
    //default:
    //    break;
    //}
}

void EditorManager::changeModeCycle()
{
    auto mode = EditorMode((_mode + 1) % 3);
    //_mode = EditorMode((_mode == 0) ? 1 : _mode);

    changeMode(mode);
}

void EditorManager::changeMode(EditorMode mode)
{
    _prevMode = _mode;
    CC_SAFE_DELETE(_currentInputProcessor);

    _mode = mode;
    switch (mode)
    {
    case VIEW:
    {
        auto p = new  ViewInputProcessor();
        setInputProcessor(p);
        //_modeLabel->setString("Mode: View");
        editorUI->changeModeUI(EditorMode::VIEW);
    }
    break;
    case CREATE:
    {
        auto p = new CreationInputProcessor();
        setInputProcessor(p);
        //_modeLabel->setString("Mode: Create");
        editorUI->changeModeUI(EditorMode::CREATE);
    }
    break;
    case EDIT:
    {
        //auto p = new NewEditionInputProcessor();
        auto p = new EditionInputProcessorv3();
        setInputProcessor(p);
        //_modeLabel->setString("Mode: Edit");
        editorUI->changeModeUI(EditorMode::EDIT);
    }   
    break;
    case TEST:
    {
        auto p = new TestInputProcessor();
        p->init(oManager->b2dManager);
        setInputProcessor(p);
        //_modeLabel->setString("Mode: Test");
        editorUI->changeModeUI(EditorMode::VIEW);
    }
    break;
    default:
        break;
    }
}

void EditorManager::changeModeDisabled()
{
    _mode = EditorMode::VIEW;
    CC_SAFE_DELETE(_currentInputProcessor);

    auto p = new EditorInputProcessor();
    setInputProcessor(p);

}

void EditorManager::changeFromPlayMode()
{
    changeMode(_prevMode);
    drawer->pauseDrawing(false);
}

//Call this function intelligently
void EditorManager::changeToPlayMode()
{
    drawer->pauseDrawing(true);
}
