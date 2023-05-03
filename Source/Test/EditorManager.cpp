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
#include "Utils/CamDelegate.h"
#include "Test/UI/EditorTabLayout.h"

USING_NS_AX;

// on "init" you need to initialize your instance
bool EditorManager::init()
{
	//_pointsNode = PointSpaceNode::create();
	//addChild(_pointsNode);
    scheduleUpdate();
    nearestPoint = nullptr;
    _hasNearClosePt = false;
	
    //Initially change mode to view
    //changeMode(EditorMode::VIEW);

    //Patch change later
    backgroundSpriteDraw = Sprite::create();
    backgroundSpriteDraw->setOpacity(127);
    backgroundSpriteDraw->setCameraMask((unsigned short)CameraFlag::USER2);
    backgroundSpriteDraw->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(backgroundSpriteDraw, 3);
    rendTexVisitNodes.push_back(backgroundSpriteDraw);

	return true;
}

void EditorManager::update(float dt)
{
    Node::update(dt);

    //Put this code somewhere else
    updateBackgroundImage();

    //Position draw nodes and rendered sprite correctly
    {
        //Do not do this calculation every frame
        //Calculate sprite scale factor
        Vec2 spSize = backgroundSpriteDraw->getContentSize();
        float scF = 500 / spSize.width;//Will change from constant 500 later
        backgroundSpriteDraw->setScale(scF);

        //Calculate zoom
        float zoom = oManager->spaceConv->scale;
        editorCam->initOrthographic(970 * (1 / zoom), 662 * (1 / zoom), 1, 1000);

        //Calculate global screen space position of point(0,0)
        Vec2 a;
        oManager->spaceConv->applyT(&a);
        //Calculate editorCamera space position of the screenspace point calculated above
        Vec2 b = convertGlobalScreenSpaceToEditCamCoord(a);

        //CCLOG("%f;%f", b.x, b.y);

        backgroundSpriteDraw->setPosition(b);
    }

    if (editorCam && backgroundSpriteDraw) {
        camDelegate->setVisitingCamera(editorCam);
        //Set ui render texture to begin and end
        editorUI->editTab->_rend->beginWithClear(0, 0, 0, 0);
        //backgroundSpriteDraw->visit();
        for (auto i : rendTexVisitNodes)
        {
            i->visit();
        }
        editorUI->editTab->_rend->end();
        camDelegate->setVisitingCamera(nullptr);
    }
}

void EditorManager::updateBackgroundImage()
{
    if (rbManager->getSelectedModel() == nullptr) return;

    //If current selected rigidbody's imgPath != displayed image change it
    if (!rbManager->getSelectedModel()->isImagePathValid()) return;

    auto a = bgSpritePath;
    auto b = rbManager->getSelectedModel()->getImagePath();

    //If 2 image paths do not match
    if (a != b)
    {
        bgSpritePath = b;
        if (b == "") 
        {
            backgroundSpriteDraw->init();//Clear background sprite
        }
        else
        {
            backgroundSpriteDraw->initWithFile(b);
        }
        backgroundSpriteDraw->setOpacity(127);
        backgroundSpriteDraw->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    }
}

void EditorManager::resetPointSpace()
{
	//pointsNode->setPosition(editorUI->getWorldViewPortMidpoint());
}

void EditorManager::pauseInput(bool pause)
{
    if (pause)
        editorUI->_screenInterface->pauseInput();
    else
        editorUI->_screenInterface->unpauseInput();
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

void EditorManager::selectedPointsAddAll(std::vector<Vec2*> pts)
{
/////////////////////////////////////////////////////////////////////////////////////////////////
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
            std::min(p1.x, p2.x),
            std::min(p1.y, p2.y),
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

void EditorManager::insertPointsBetweenSelected()
{
    if (selectedPoints.size() <= 1)return;

    if (!isInsertEnabled())
        return;

    std::vector<Vec2> toAdd;

    for (ShapeModel* shape : rbManager->getSelectedModel()->_shapes)
    {
        if (shape->getType() != ShapeModel::Type::POLYGON)
            continue;

        auto& vs = shape->_vertices;

        for (int i = 0; i < vs.size(); i++) {
            Vec2 p1 = vs.at(i);
            Vec2 p2 = i != vs.size() - 1 ? vs.at(i + 1) : vs.at(0);

            //if (selectedPoints.contains(p1) && selectedPoints.contains(p2)) {
            //    Vector2 p = new Vector2((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
            //    vs.add(i + 1, p);
            //    toAdd.add(p);
            //}

            bool cond = isSelectedPointsContain(p1) && isSelectedPointsContain(p2);

            if (cond)
            {
                Vec2 p((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
                vs.insert(vs.begin() + i + 1, p);
                toAdd.push_back(p);
            }
        }
    }

    //selectedPoints.addAll(toAdd);
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

bool EditorManager::isInsertEnabled()
{
    return true;
}

void EditorManager::setNearestClosingPt(bool avail,const ax::Vec2& v)
{
    _hasNearClosePt = avail;
    nearClosePt = v;
}

//-------------------
//Events
//-------------------

void EditorManager::onInsertBetweenSelectedPointsBtnCallback(ax::Ref* s, ax::ui::Widget::TouchEventType t)
{
    if (t == ui::Widget::TouchEventType::ENDED)
    {
        insertPointsBetweenSelected();
    }
}

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
    mouseLocation = e->getLocationInView();
    
    //Send event to rigidbodies manager
    CustomMouseEvent mEve = { CustomMouseEvent::EventType::MOVED,e };

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

void EditorManager::createCamera()
{
    auto defCam = getScene()->getDefaultCamera();
    //Create a 2nd camera    
    editorCam = Camera::createOrthographic(970, 662, 1, 1000);//Set harcoded values for now
    editorCam->setCameraFlag(CameraFlag::USER2);
    getScene()->addChild(editorCam, 1);
    //cam->setPosition3D(defCam->getPosition3D());
    editorCam->setPosition(Vec2(0, 0));
    editorCam->setPositionZ(defCam->getPositionZ());
    editorCam->setRotation3D(defCam->getRotation3D());
}

ax::Vec2 EditorManager::convertEditCamToGlobalScreenSpaceCoord(ax::Vec2 in)
{
    //Convert to virtual screen space
    auto a = editorCam->projectGL(Vec3(in.x, in.y, 0));
    //Convert to rendText Space
    auto winSize = _director->getWinSize();
    auto rendTexSize = editorUI->editTab->viewPlaceholder->getContentSize();
    Vec2 b((a.x / winSize.x) * rendTexSize.width, (a.y / winSize.y) * rendTexSize.height);
    //Convert to global screen space
    Vec2 c = editorUI->editTab->viewPlaceholder->convertToWorldSpace(b);

    return c;
}

ax::Vec2 EditorManager::convertGlobalScreenSpaceToEditCamCoord(ax::Vec2 in)
{
    //Convert to Rendtex space
    Vec2 a = editorUI->editTab->viewPlaceholder->convertToNodeSpace(in);
    //Convert to virtual viewport space
    auto winSize = _director->getWinSize();
    auto rendTexSize = editorUI->editTab->viewPlaceholder->getContentSize();
    Vec2 b((a.x / rendTexSize.x) * winSize.width, (a.y / rendTexSize.y) * winSize.height);
    //Convert to worldspace
    Vec3 c = editorCam->unprojectGL(Vec3(b.x, b.y, 0));
    
    return Vec2(c.x, c.y);
}


