#include "EditorPanelUI.h"
#include "Test/UtilityClasses.h"
#include "EditorTabLayout.h"
#include "PlayTabLayout.h"
#include "Utils/Helpers.h"

USING_NS_AX;
USING_NS_AX::ui;

// on "init" you need to initialize your instance
bool EditorPanelUI::init()
{ 
    //_currentInputProcessor = nullptr;
    _prevMode = EditorMode::VIEW;

    //998,720
    setContentSize(Size(998, 720));
    auto s = getContentSize();
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    viewSize.set(976, 670);

    //scheduleUpdate();

    //Add mouse pointer node
    _mousePointer = DrawNode::create();
    _mousePointer->drawDot(Vec2::ZERO, 11, Color4F::RED);
    _mousePointer->retain();


    //Init layout
    _windowLayout = ui::Layout::create();

    Size selfSize = getContentSize();

    //Setup Layout
    //_windowLayout->setContentSize(Size(selfSize.width, selfSize.height));
    //_windowLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //_windowLayout->setLayoutType(ui::Layout::Type::HORIZONTAL);
    //_windowLayout->setBackGroundImage("Sprites/background.png");
    //_windowLayout->setBackGroundImageScale9Enabled(true);
    //_windowLayout->setBackGroundImageCapInsets(Rect(3, 3, 10, 10));
    //
    ////Set layout position in parent
    //_windowLayout->setPositionX(selfSize.width / 2);
    //_windowLayout->setPositionY(selfSize.height / 2);

    //Editor label
    auto label = Label::createWithTTF("Editor", "fonts/arial.ttf", 20);
    label->enableBold();
    label->enableShadow(Color4B::GRAY);
    label->setTextColor(Color4B::BLACK);
    addChild(label, 1, "label");
    //Update text position
    label->setPositionX(label->getContentSize().width / 2 + 10);
    label->setPositionY(getContentSize().height - 15);

    label->setVisible(false);//

    auto line = DrawNode::create(100);
    addChild(line, 1, "line");
    //Update line position
    line->clear();
    line->setLineWidth(2);
    line->drawLine(Vec2::ZERO, Vec2(getContentSize().width, 0), Color4F::GRAY);
    line->setPositionX(0);
    line->setPositionY(getContentSize().height - label->getContentSize().height - 11);
    line->setVisible(false);

    //_windowLayout->setContentSize(Size(s.width, s.height));

    //Event Listener Keyboard
    _listenerKey = EventListenerKeyboard::create();
    _listenerKey->onKeyPressed = AX_CALLBACK_2(EditorPanelUI::onKeyUp, this);
    _listenerKey->onKeyReleased = AX_CALLBACK_2(EditorPanelUI::onKeyDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerKey, this);

    //Add Screen Interface
    {
        _screenInterface = EditorScreenInterface::create();
        addChild(_screenInterface);
        _screenInterface->eOnMouseDown = CC_CALLBACK_1(EditorPanelUI::onMouseDown, this);
        _screenInterface->eOnMouseUp = CC_CALLBACK_1(EditorPanelUI::onMouseUp, this);
        _screenInterface->eOnMouseMove = CC_CALLBACK_1(EditorPanelUI::onMouseMoved, this);
        _screenInterface->eOnMouseScroll = CC_CALLBACK_1(EditorPanelUI::onMouseScroll, this);
    }

    viewMid = DrawNode::create();
    addChild(viewMid, 3);
    //viewMid->drawDot(Vec2::ZERO, 7, Color4F::RED);
    viewMid->setPosition(s.width / 2, 10 + (viewSize.height / 2));

    addNewUI();

    //Set initial mode to view
    changeModeUI(EditorMode::VIEW);

    return true;
}

void EditorPanelUI::addNewUI()
{
    Size s = getContentSize();

    Size widgetSize(s);

    auto displayText = Text::create();
    //displayText->setPosition(VisibleRect::bottom() + Vec2(0, 50));
    addChild(displayText);


    auto tab = TabControl::create();
    addChild(tab);
    tab->setContentSize(Size(s.width - 8, s.height - 8));//-17
    tab->setHeaderHeight(30.f);
    tab->setHeaderWidth(75.f);
    //tab->setHeaderSelectedZoom(0);
    tab->setHeaderDockPlace(TabControl::Dock::TOP);
    tab->setTabChangedEventListener(CC_CALLBACK_2(EditorPanelUI::onTabChanged, this));

    //::Helper::makeBound(tab, Color4F::BLUE);

    auto header1 = TabHeader::create("EDIT", "Sprites/newicons/tab_new_disabled.png", "Sprites/newicons/tab_new_disabled.png", "Sprites/newicons/tab_new_selected.png", "Sprites/newicons/tab_new_disabled.png", "Sprites/newicons/tab_new_disabled.png");
    header1->setTitleFontSize(20);
    header1->getTitleRenderer()->enableBold();
    auto header2 = TabHeader::create("PLAY", "Sprites/newicons/tab_new_disabled.png", "Sprites/newicons/tab_new_disabled.png", "Sprites/newicons/tab_new_selected.png", "Sprites/newicons/tab_new_disabled.png", "Sprites/newicons/tab_new_disabled.png");
    header2->setTitleFontSize(20);
    header2->getTitleRenderer()->enableBold();

    //Add Editor Tab
    {
        auto container1 = EditorTabLayout::create();
        tab->insertTab(0, header1, container1);
        container1->initLayout();
        _modeLabel = container1->modeLabel;
    }
    //Add Play Tab
    {
        auto container2 = PlayTabLayout::create();
        tab->insertTab(1, header2, container2);
        container2->initLayout();
        playTab = container2;
    }
    tab->setSelectTab(0);
    tab->setPosition(widgetSize / 2);

}

void EditorPanelUI::initWithManager(OverallManager* manager)
{
    oManager = manager;
}

//------------
//Callbacks
//------------

void EditorPanelUI::onTabChanged(int t, TabControl::EventType)
{
    //oManager->eventManager->onTabChanged(t);//Invoke event
}

//-----------------
//--MouseCallbacks
//-----------------

void EditorPanelUI::onMouseDown(cocos2d::EventMouse* em)
{
    Vec2 locationInNode = this->convertToNodeSpace(em->getLocationInView());
    Size s = this->getContentSize();
    Rect rect = Rect(10, 10, s.width - 20, s.height - 50);//20 and 50 offset for borders

    if (rect.containsPoint(locationInNode))
    {

        CustomMouseEvent mEve = { CustomMouseEvent::EventType::DOWN,em };
        //Do something
        
    }
}

void EditorPanelUI::onMouseMoved(EventMouse* em)
{
    Vec2 locationInNode = this->convertToNodeSpace(em->getLocationInView());
    Size s = this->getContentSize();
    Rect rect = Rect(10, 10, s.width - 20, s.height - 50);

    if (rect.containsPoint(locationInNode))
    {
        _mousePointer->setOpacity(255);
        _mousePointer->setPosition(em->getLocationInView());

        //Send event to rigidbodies manager
        CustomMouseEvent mEve = { CustomMouseEvent::EventType::MOVED,em };

        //if (_currentInputProcessor)
        //    _currentInputProcessor->onMouseMoved(mEve); //Send event to input processor
    }
    else
    {
        _mousePointer->setOpacity(0);
    }
    //prevMousePoint = em->getLocationInView();
}

void EditorPanelUI::onMouseUp(EventMouse* e)
{
    Vec2 locationInNode = this->convertToNodeSpace(e->getLocationInView());
    Size s = this->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);

    if (rect.containsPoint(locationInNode))
    {
        CustomMouseEvent mEve = { CustomMouseEvent::EventType::UP,e };
        //_rbManager->onMouseInteractionFromEditor(mEve, _mode);

        //if (_currentInputProcessor)
        //    _currentInputProcessor->onMouseUp(mEve); //Send event to input processor
    }
}

void EditorPanelUI::onMouseScroll(cocos2d::EventMouse* e)
{
    Vec2 locationInNode = this->convertToNodeSpace(e->getLocationInView());
    Size s = this->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);

    if (rect.containsPoint(locationInNode))
    {
        //Send event
        CustomMouseEvent mEve = { CustomMouseEvent::EventType::MOVED,e };

        //@todo again send this event to editor manager for proper processing
        //if (_currentInputProcessor)
        //    _currentInputProcessor->onMouseScroll(mEve); //Send event to input processor
    }
}

//-----------------
//--KeyboardCallbacks
//-----------------

void EditorPanelUI::onKeyDown(cocos2d::EventKeyboard::KeyCode k, cocos2d::Event* e)
{
    //if (_currentInputProcessor)
    //    _currentInputProcessor->onKeyDown(k, e); //Send event to input processor

    //Change mode
    //if (k == EventKeyboard::KeyCode::KEY_M)
    //{
    //    changeModeCycle();
    //}
}

void EditorPanelUI::onKeyUp(cocos2d::EventKeyboard::KeyCode k, cocos2d::Event* e)
{
    //if (_currentInputProcessor)
    //    _currentInputProcessor->onKeyUp(k, e); //Send event to input processor
}

//-----------------
//Others
//-----------------

void EditorPanelUI::changeModeUI(EditorMode m)
{
    _prevMode = mode;

    mode = m;
    switch (m)
    {
    case VIEW:
    {
        _modeLabel->setString("Mode: View");
    }
    break;
    case CREATE:
    {
        _modeLabel->setString("Mode: Create");
    }break;
    case EDIT:
    {
        _modeLabel->setString("Mode: Edit");
    }   break;
    case TEST:
    {
        _modeLabel->setString("Mode: Test");
    }   break;
    default:
        break;
    }
}

void EditorPanelUI::changeToModeFromPlay()
{
    changeModeUI(_prevMode);
}