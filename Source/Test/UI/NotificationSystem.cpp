#include "Test/UI/NotificationSystem.h"

USING_NS_CC;
USING_NS_CC::ui;

// on "init" you need to initialize your instance
bool NotificationSystem::init()
{
    _aState = HIDDEN;
    addUIComponents();
    return true;
}

void NotificationSystem::onEnter()
{
    Node::onEnter();
    //schedule to run point25SecAfteronEnter() after 0.25 secs.
    auto f = CallFunc::create(CC_CALLBACK_0(NotificationSystem::point1SecAfteronEnter, this));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.1f), f));
}

void NotificationSystem::addUIComponents()
{
    auto  lay = Layout::create();
    addChild(lay);
    lay->setGlobalZOrder(99);
    //Setup Layout
    lay->setAnchorPoint(Vec2(0, 0.5f));
    lay->setContentSize(Size(200, 34));
    lay->setLayoutType(ui::Layout::Type::ABSOLUTE);
    lay->setBackGroundImage("Sprites/background.png");
    lay->setBackGroundImageScale9Enabled(true);
    lay->setBackGroundImageCapInsets(Rect(3, 3, 10, 10));
    notifBoard = lay;

    //Add msg text

    auto lab = ui::Text::create("<Your Message>", "fonts/arial.ttf", 18);
    lab->setTextColor(Color4B::BLACK);
    lab->setTextAreaSize(Size(200, 34));
    lab->setTextHorizontalAlignment(TextHAlignment::LEFT);
    lab->setTextVerticalAlignment(TextVAlignment::CENTER);
    lab->ignoreContentAdaptWithSize(false);
    lab->setPosition(Vec2(105, 17));

    notifBoard->addChild(lab, 1);
    notifText = lab;

}

void NotificationSystem::setup(Vec2 anch)
{
    anchor = anch;

    notifBoard->setPosition(anch);

}

void NotificationSystem::point1SecAfteronEnter()
{

}

void NotificationSystem::startAnimatePanel()
{
    //If anim running do not do anything
    if (_aState != HIDDEN)
        return;

    //Create sequence of action, notif board out->delay->in->callback
    auto s = notifBoard->getContentSize();
    auto act1 = EaseBackOut::create(MoveBy::create(0.5f, Vec2(-s.width - 15, 0)));
    auto del = DelayTime::create(2);
    auto act2 = act1->reverse();
    auto callFunc = CallFunc::create(CC_CALLBACK_0(NotificationSystem::afterNotifActionComplete, this));

    auto seq = Sequence::create(act1, del, act2, callFunc, nullptr);

    notifBoard->runAction(seq);
    _aState = RUNNING;


}

void NotificationSystem::showNotification(std::string msg)
{
    //If anim running do not do anything
    if (_aState != HIDDEN)
        return;

    //::PlaySound(TEXT("SystemExclamation"), NULL, SND_ALIAS | SND_ASYNC);
    notifText->setString(msg);
    startAnimatePanel();
}

void NotificationSystem::afterNotifActionComplete()
{
    _aState = HIDDEN;
}

