#include "TestScene12.h"
#include "Test/UI/ProjectPanelUI.h"
#include "Test/UI/EditorPanelUI.h"
#include "Test/UI/PlayTabLayout.h"
#include "AppDelegate.h"
#include "Test/OverallManager.h"
#include "Test/NewShapesDrawNode.h"
#include "Test/RbListController.h"
#include "Test/draw/EditorDraw.h"
//Box2d helpers
#include "Phys/B2_WorldNode.h"
#include "Phys/DebugDrawNode.h"
#include "Phys/ShapeHelper.h"
#include "Phys/DefHelper.h"
#include "Phys/SuperPhysHelper.h"
#include "Phys/B2_PhysicsBody.h"
#include "Phys/DefHelper.h"
#include "Test/b2d/B2dManager.h"
#include "Test/b2d/SpawnManager.h"

USING_NS_AX;

Scene* TestScene12::createScene()
{
    return TestScene12::create();
}

// on "init" you need to initialize your instance
bool TestScene12::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    //scheduleUpdate();

    visibleSize = _director->getVisibleSize();
    origin = _director->getVisibleOrigin();

    //addCloseButton();

    /////////////////////////////
    // 3. add your codes below...

    addUISubsystem();

    auto prjManager = new ProjectManager();
    auto rbManager = new RigidBodiesManager();

    _manager = new OverallManager();
    _manager->uiSystem = _uiSystem;
    _manager->prjManager = prjManager;
    _manager->rbManager = rbManager;
    _manager->rbManager->setInputModuleUI(_uiSystem->editPanelUI);
    prjManager->jIOSystem->setOverallManager(_manager);

    auto rBListCtrl = RbListController::create();
    addChild(rBListCtrl);
    rBListCtrl->rbMan = rbManager;
    rBListCtrl->rbUI = _uiSystem->rbPanelUI;
    _manager->rbManager->_onEntryAddedListenerList.push_back(CC_CALLBACK_1(RbListController::entryAddedCallback, rBListCtrl));
    _manager->rbManager->onEntryDeletedListenerList.push_back(CC_CALLBACK_1(RbListController::entryDeletedCallback, rBListCtrl));
    _manager->rbManager->onSelChangedListenerList.push_back(CC_CALLBACK_1(RbListController::entrySelectedCallback, rBListCtrl));

    //Add event manager
    auto eM = EventManager::create();
    addChild(eM, 2);
    eM->oManager = _manager;
    _manager->eventManager = eM;

    //Add State tracker
    auto sT = new StateTracker();
    sT->oManager = _manager;
    sT->rbManager = _manager->rbManager;
    _manager->sTracker = sT;

    //Add dialog system
    {
        auto d = DialogWindowSystem::create();
        addChild(d, 11);
        _manager->dialogWindowSystem = d;
        _manager->eventManager->_dialogSystem = d;
        _manager->eventManager->setDialogWindowSystem(d);
    }

    auto shapeDraw1 = NewShapesDrawNode::create();
    //Add shape draw node
    {
        auto shapeDraw = ShapesDrawNode::create();
        shapeDraw->setRbManager(_manager->rbManager);
        shapeDraw->setEditorPanel(_manager->uiSystem->editPanelUI);
        //_manager->uiSystem->editPanelUI->setDrawNode(shapeDraw);
        addChild(shapeDraw, 9);
        shapeDraw->setVisible(false);

        shapeDraw1->setRbManager(_manager->rbManager);
        shapeDraw1->setEditorPanel(_manager->uiSystem->editPanelUI);
        addChild(shapeDraw1, 9);
        //_manager->uiSystem->editPanelUI->setDrawNode(shapeDraw1);
    }

    //Add bg grid
    addGridDraw();

    //Editor manager
    {

        auto editM = EditorManager::create();
        editM->editorUI = _manager->uiSystem->editPanelUI;
        addChild(editM);

        //New Editor draw
        auto eDraw = EditorDraw::create();
        addChild(eDraw, 1);
        eDraw->editManager = editM;
        editM->drawer = eDraw;

        _manager->editSystem = editM;
        _manager->uiSystem->editPanelUI->editManager = editM;
        _manager->uiSystem->editPanelUI->oManager = _manager;
        editM->oManager = _manager;
    }

    //Linkages

    editPanelUI = _manager->uiSystem->editPanelUI;

    _uiSystem->rbPanelUI->_rbToolbarLayout->_onClickEventFromButtons = CC_CALLBACK_1(EventManager::onButtonPressFromRbPanel, _manager->eventManager);
    _manager->uiSystem->rbPanelUI->onAListingClicked = CC_CALLBACK_1(EventManager::onAListingClickedFromRbPanel, _manager->eventManager);
    _manager->uiSystem->prjPanelUI->onBtnPressedCallback = CC_CALLBACK_1(EventManager::onBtnPressedFromPrjPanel, _manager->eventManager);
    _manager->uiSystem->rbPanelUI->addSpwnBtnListener(CC_CALLBACK_1(EventManager::onSpwnButtonFromRbPanel, _manager->eventManager));

    dynamic_cast<EditorPanelUI*>(_manager->uiSystem->editPanelUI)->playTab->pCtrlPanel->eOnButtonPress = CC_CALLBACK_1(EventManager::onPlayTabCtrlEvent, _manager->eventManager);

    //Add new screen space translator
    {
        auto t = new SpaceConverter();
        auto mid = _manager->uiSystem->editPanelUI->getWorldViewPortMidpoint();
        t->center = mid;
        t->applyScale(1);

        t->screenOffset.set(-mid.x, -mid.y);
        t->addOffset(Vec2(-200, -250));//Experimental!!!!!!
        t->validateMatrices();

        _manager->spaceConv = t;
    }

    //Setup a new camera
    {
        auto s = _director->getWinSize();
        auto cam = Camera::createOrthographic(s.width, s.height, 1, 1000);
        cam->setCameraFlag(CameraFlag::USER1);
        addChild(cam, 99, "b2_cam");
        b2Cam = cam;

        Vec2 a = visibleSize / 2;
        auto mid = _manager->uiSystem->editPanelUI->getWorldViewPortMidpoint();

        Vec2 c = a - mid;

        Vec3 p = getDefaultCamera()->getPosition3D();
        cam->setPosition(c + Vec2(0, 0));
        cam->setPositionZ(p.z);

        //Add a pointer to show spawn point
        auto camPointer = Sprite::create("Sprites/ui/crosshair.png");
        camPointer->setScale(0.4f);
        camPointer->setCameraMask((unsigned short)CameraFlag::USER1, true);
        //camPointer->setPositionX(5);
        //camPointer->setPositionY(5);
        addChild(camPointer, 2, "sp_pointer");


        //Sky
        auto l1 = LayerColor::create(Color4B(0, 191, 255, 220));
        l1->setCameraMask((unsigned short)CameraFlag::USER1, true);
        //addChild(l1, 2);

        //Testing
        //auto l = DrawNode::create();
        //l->setCameraMask((unsigned short)CameraFlag::USER1, true);
        //l->drawDot(Vec2::ZERO, 10, Color4F::RED);
        //l->drawDot(visibleSize / 2, 10, Color4F::RED);
        //l->drawDot(visibleSize, 10, Color4F::RED);
        //addChild(l, 2);

    }

    addB2DSystem();

    _manager->b2dManager->deactivateWorld(); //Firstly world will be inactive.

    //Test module
    //auto tM = TestModule::create();
    //addChild(tM, 44);
    //tM->setUserData((void*)_manager);//Trick to access the manager from test module

    //Testing
    //auto l = DrawNode::create();
    //l->drawLine(Vec2::ZERO, Vec2(100, 0), Color4F::RED);
    //l->setPosition(200, 200);
    //addChild(l, 100);

    //This means all things are inited.
    _manager->init();
    
    return true;
}

//Add UI subsystem
void TestScene12::addUISubsystem()
{
    //Add a solid rect
    auto dN = DrawNode::create();
    dN->drawSolidRect(Vec2::ZERO, visibleSize, Color4B(233, 233, 233, 255));
    //addChild(dN, -1);

    auto prjUI = ProjectPanelUI::create();
    addChild(prjUI, 30);
    //Place at top left
    {
        Size s = prjUI->getContentSize();
        Vec2 a(origin.x, visibleSize.height + origin.y);
        a += Vec2(s.width / 2, s.height / -2);
        prjUI->setPosition(a);
    }

    auto rbUI = RigidbodiesPanelUI::create();
    addChild(rbUI, 20);
    //Place at bottom left
    {
        Size s = rbUI->getContentSize();
        Vec2 a(origin.x, visibleSize.height + origin.y - 178);
        a += Vec2(s.width / 2, s.height / -2);
        rbUI->setPosition(a);
    }

    //for (size_t i = 0; i < 20; i++)
    //{
    //    rbUI->addEntry(std::to_string(i));
    //}
    ////rbUI->addEntry("Hello");
    //rbUI->addEntry("World");

    //Add Editorpanel
    auto editorUI = EditorPanelUI::create();
    //editorUI->initWithManager(_manager);
    addChild(editorUI, 11);
    //Place at mid right
    {
        Size s = editorUI->getContentSize();
        Vec2 a(origin.x + 282, origin.y);
        a += Vec2(s.width / 2, s.height / 2);
        editorUI->setPosition(a);
        editPanelUI = editorUI;
    }
    //editorUI->setScale(0.9f);

    //Add universal notification system
    auto notif = NotificationSystem::create();
    addChild(notif, 13, "sys_notif");
    notif->setup(Vec2(visibleSize.width, visibleSize.height - 50));

    auto ui = UISubsystem::create();
    ui->rbPanelUI = rbUI;
    ui->prjPanelUI = prjUI;
    ui->notifSys = notif;
    ui->editPanelUI = editPanelUI;
    addChild(ui, 1, "ui_system");
    _uiSystem = ui;

}

void TestScene12::addB2DSystem()
{
    //Create world node
    auto wN = rb::B2WorldNode::create(Vec2(0, -900));
    wN->retain();

    //Set debug draw node
    auto dDN = rb::DebugDrawNode::create();
    this->addChild(dDN, 55);
    dDN->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
    wN->setDebugDrawNode(dDN);
    dDN->setCameraMask((unsigned short)CameraFlag::USER1, true);

    //Add box2d Manager
    auto bMan = new B2DManager();
    bMan->wN = wN;
    editPanelUI->playTab->bManager = bMan;//Link box2d manager and playtab interface
    bMan->b2Cam = b2Cam;//Link camera
    _manager->b2dManager = bMan;
    bMan->oManager = _manager;

    //Create a spawn manager
    auto spwnManager = new SpawnManager();
    spwnManager->rbManager = _manager->rbManager;
    spwnManager->wN = wN;
    spwnManager->runningScene = this;
    _manager->spwnManager = spwnManager;

    //Create a dummy body for manager
    b2BodyDef def;
    bMan->m_groundBody = wN->createPhysicsBodyComp(&def);
    bMan->m_groundBody->retain();

    //Create ground
    {
        b2BodyDef bd;
        rb::B2PhysicsBody* ground = wN->createPhysicsBodyComp(&bd);

        b2EdgeShape shape;

        rb::ShapeHelper::initEdgeShapeSetTwoSided(shape, Vec2(-10000.f, 0), Vec2(10000.f, 0));
        ground->createFixture(&shape, 0.0f);


        rb::ShapeHelper::initEdgeShapeSetTwoSided(shape, Vec2(-10000.f, 0), Vec2(-10000.f, 1000));
        ground->createFixture(&shape, 0.0f);


        rb::ShapeHelper::initEdgeShapeSetTwoSided(shape, Vec2(10000.f, 0), Vec2(10000.f, 1000));
        ground->createFixture(&shape, 0.0f);

        auto n = Node::create();
        addChild(n, 0, "ground");
        n->addComponent(ground);

        ground->setPosition((visibleSize.width / 2) + origin.x, origin.y);

        auto grndSp = DrawNode::create();
        grndSp->setCameraMask((unsigned short)CameraFlag::USER1, true);
        grndSp->drawSolidRect(Vec2(-10000, -1000), Vec2(10000, 0), Color4F(Color4B(63, 112, 77, 255)));
        addChild(grndSp);
    }

}

void TestScene12::addGridDraw()
{
    auto bG = BackGrid::create();
    addChild(bG, -2);

    bG->gridSize = visibleSize;//Set total grid size
    bG->cellSize.setSize(10, 10);//Set cell size

    bG->validateGrid();

    _manager->backGrid = bG;
}

void TestScene12::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    //_director->end();

}
