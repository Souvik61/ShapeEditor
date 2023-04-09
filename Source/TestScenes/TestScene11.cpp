#include "TestScene11.h"
#include "Test/UI/ProjectPanelUI.h"
#include "Test/UI/EditorPanelUI.h"
#include "AppDelegate.h"
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

USING_NS_CC;

Scene* TestScene11::createScene()
{
    return TestScene11::create();
}

// on "init" you need to initialize your instance
bool TestScene11::init()
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
    
    return true;
}

//Add UI subsystem
void TestScene11::addUISubsystem()
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
    rbUI->addEntry("World");

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
        panelUI = editorUI;
    }
    //editorUI->setScale(0.9f);

    //Add universal notification system
    auto notif = NotificationSystem::create();
    addChild(notif, 13, "sys_notif");
    notif->setup(Vec2(visibleSize.width, visibleSize.height - 50));

    auto ui = UISubsystem::create();
    ui->prjPanelUI = prjUI;
    ui->notifSys = notif;
    addChild(ui, 1, "ui_system");
    _uiSystem = ui;

}

void TestScene11::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    //_director->end();

}
