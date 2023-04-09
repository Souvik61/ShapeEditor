#include "UIScene.h"
#include "Test/UI/ProjectPanelUI.h"
#include "Test/UI/RigidbodiesPanelUI.h"
#include "Test/UI/EditorPanelUI.h"
#include "Test/EventManager.h"


USING_NS_CC;

Scene* UIScene::createScene()
{
    return UIScene::create();
}

// on "init" you need to initialize your instance
bool UIScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(UIScene::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        //problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
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

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto prjUI = ProjectPanelUI::create();
    addChild(prjUI);
    //Place at top left
    {
        Size s = prjUI->getContentSize();
        Vec2 a(origin.x, visibleSize.height + origin.y);
        a += Vec2(s.width / 2, s.height / -2);
        prjUI->setPosition(a);
    }

    auto rbUI = RigidbodiesPanelUI::create();
    addChild(rbUI);
    //Place at bottom left
    {
        Size s = rbUI->getContentSize();
        Vec2 a(origin.x, visibleSize.height + origin.y - 178);
        a += Vec2(s.width / 2, s.height / -2);
        rbUI->setPosition(a);
    }

    auto editorUI = EditorPanelUI::create();
    addChild(editorUI);
    //Place at mid right
    {
        Size s = editorUI->getContentSize();
        Vec2 a(origin.x + 284, origin.y);
        a += Vec2(s.width / 2, s.height / 2);
        editorUI->setPosition(a);
    }

    auto eventMan = EventManager::create();
    eventMan->panelUI = prjUI;
    addChild(eventMan);

    auto a = EditorPanelUI::create();
    addChild(a);

    return true;
}


void UIScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

}
