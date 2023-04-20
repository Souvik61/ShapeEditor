#include "MiscTesting.h"
#include "ui/CocosGUI.h"
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
USING_NS_AX::ui;

Scene* MiscTesting::createScene()
{
    return MiscTesting::create();
}

// on "init" you need to initialize your instance
bool MiscTesting::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    scheduleUpdate();

    visibleSize = _director->getVisibleSize();
    origin = _director->getVisibleOrigin();

    //addCloseButton();

    /////////////////////////////
    // 3. add your codes below...

    //addUISubsystem();

    auto btn = Button::create("Sprites/newicons/ic_import.png");
    btn->setPosition(Vec2(100, 100));
    addChild(btn, 1);

    //Add dialog system
    {
        auto d = DialogWindowSystem::create();
        addChild(d, 11, "DS");
        //_manager->dialogWindowSystem = d;
        //_manager->eventManager->_dialogSystem = d;
        //_manager->eventManager->setDialogWindowSystem(d);
    }
    
    //addB2DSystem();

    addCloseButton();
    
    return true;
}

void MiscTesting::update(float dt)
{
    Scene::update(dt);

}

void MiscTesting::onEnter()
{
    Scene::onEnter();
}

//Add UI subsystem
void MiscTesting::addUISubsystem()
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

void MiscTesting::addB2DSystem()
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

void MiscTesting::addGridDraw()
{
    auto bG = BackGrid::create();
    bG->setVisible(false);
    addChild(bG, -2);

    bG->gridSize = visibleSize;//Set total grid size
    bG->cellSize.setSize(10, 10);//Set cell size

    //bG->validateGrid();

    _manager->backGrid = bG;
}

void MiscTesting::addCloseButton()
{
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MiscTesting::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {

    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void MiscTesting::menuCloseCallback(Ref* pSender)
{
    DialogWindowSystem* diaSystem = getChildByName<DialogWindowSystem*>("DS");

    //diaSystem->showRenameDialog();
    diaSystem->showImgSelectionDialog();

}
