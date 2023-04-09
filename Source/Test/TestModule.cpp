#include "TestModule.h"
#include "Test/OverallManager.h"

USING_NS_CC;

bool TestModule::init()
{

    mListener = EventListenerMouse::create();
    mListener->onMouseMove = CC_CALLBACK_1(TestModule::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mListener, this);

    ptr = DrawNode::create();
    ptr->drawDot(Vec2::ZERO, 10, Color4F::BLUE);
    addChild(ptr);

    return true;
}

void TestModule::onMouseMove(ax::EventMouse* eM)
{
    Vec2 a = eM->getLocationInView();

    auto man = static_cast<OverallManager*>(getUserData());
    man->buffDelegate->applyNewInvTransform(&a);

    ptr->setPosition(a);
}

//bool DialogPrompt::onTouchBegan(Touch* t, Event* e)
//{
//    auto bounds = e->getCurrentTarget()->getBoundingBox();
//
//    if (bounds.containsPoint(t->getLocationInView())) {
//        
//        CCLOG("Touched");
//    }
//    return true;
//}