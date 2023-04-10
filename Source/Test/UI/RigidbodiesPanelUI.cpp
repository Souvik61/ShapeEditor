#include "RigidbodiesPanelUI.h"
#include "Utils/Helpers.h"
#include "RigidbodiesPanelUI.h"
#include "Test/UI/CustomUI.h"

USING_NS_CC;
USING_NS_CC::ui;

// on "init" you need to initialize your instance
bool RigidbodiesPanelUI::init()
{
    //282,542
    Size selfSize = Size(282, 542);
    setContentSize(selfSize);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    Vec2 pos;

    //Setup window layout
    {
        Size s(selfSize.width - 10, selfSize.height - 16);

        _windowLayout = Layout::create();
        addChild(_windowLayout);
        _windowLayout->setContentSize(s);
        _windowLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _windowLayout->setLayoutType(ui::Layout::Type::ABSOLUTE);
        _windowLayout->setBackGroundImage("Sprites/newicons/round_purple_sbright.png");
        _windowLayout->setBackGroundImageScale9Enabled(true);
        _windowLayout->setBackGroundImageCapInsets(Rect(16, 16, 32, 32));

        //Set layout position in parent
        _windowLayout->setPositionX(selfSize.width / 2);
        _windowLayout->setPositionY((selfSize.height / 2) - 4);

        //::Helper::makeBound(this);
        //::Helper::makeBound(_windowLayout);
    }

    TTFConfig tc;
    tc.fontFilePath = "fonts/arial.ttf";
    tc.fontSize = 19;
    tc.distanceFieldEnabled = true;

    auto label = Label::createWithTTF(tc,"Rigidbodies");
    {
        label->setTextColor(Color4B::BLACK);
        _windowLayout->addChild(label, 1, "label");
        label->setPositionX(label->getContentSize().width / 2 + 10);
        label->setPositionY(_windowLayout->getContentSize().height - 15);
    }

    addOtherUIComponents();

    //::Helper::makeBound(this);

    auto dN = DrawNode::create();
    dN->drawSolidRect(Vec2::ZERO, Vec2(getContentSize()), Color4B(167, 167, 170, 255));
    addChild(dN, -1);

    return true;
}

void RigidbodiesPanelUI::addOtherUIComponents()
{
    Vec2 pos;
    Size s = _windowLayout->getContentSize();

    //Create a vertical layout that will hold rbToolbar and rbList
    auto l = Layout::create();
    {
        Size s1(s.width - 10, s.height - 40);
        l->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        l->setLayoutType(ui::Layout::Type::VERTICAL);
        //l->setBackGroundImage("Sprites/background.png");
        //l->setBackGroundImageScale9Enabled(true);
        //l->setBackGroundImageCapInsets(Rect(3, 3, 10, 10));
        _windowLayout->addChild(l, 1);
        l->setContentSize(s1);

        l->setPositionX(s.width / 2);
        l->setPositionY(s1.height / 2 + 10);
    }

    auto s1 = l->getContentSize();

    //Add rigidbody toolbar
    auto toolBar = RbToolbarLayout::create();
    {
        toolBar->setupWithSize(Size(s1.width, 37));
        l->addChild(toolBar);//Add to layout
        _rbToolbarLayout = toolBar;
    }

    //Add listview
    {
        Size s2(s1.width, s1.height - toolBar->getContentSize().height);

        auto lV = createTheListView(s2);
        l->addChild(lV, 2);
    }

}

void RigidbodiesPanelUI::update(float dt)
{

}

ax::ui::ListView* RigidbodiesPanelUI::createTheListView(ax::Size s)
{
    // Create the list view ex
    _listView = ListView::create();
    // set list view ex direction
    _listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    _listView->setBounceEnabled(true);
    _listView->setBackGroundImage("Sprites/newicons/round_purple_disabled.png");
    _listView->setBackGroundImageScale9Enabled(true);
    _listView->setBackGroundImageCapInsets(Rect(16, 16, 32, 32));
    //_listView->setBackGroundColor(Color3B(63, 167, 170));
    _listView->setContentSize(s);
    _listView->setScrollBarPositionFromCorner(Vec2(7, 7));
    _listView->setInertiaScrollEnabled(false);
    _listView->setScrollBarEnabled(false);
    _listView->setBounceEnabled(false);

    _listView->setItemsMargin(10);
    _listView->setGravity(ListView::Gravity::CENTER_HORIZONTAL);
    _listView->setPadding(0, 15, 0, 15);

    return _listView;
}

void RigidbodiesPanelUI::addEntry(std::string name)
{
    //If already same named entry exists do nothing
    if (_rbLayoutMap.find(name) != _rbLayoutMap.end())
        return;

    auto entry = RbEntryLayout::create();
    auto a = _listView->getContentSize();
    Size s(a.width - 15, 40);
    entry->setup(s, name);
    entry->setTouchEnabled(true);
    entry->addTouchEventListener(CC_CALLBACK_2(RigidbodiesPanelUI::onRbEntryClicked, this));
    //entry->_spwnBtn->addTouchEventListener(CC_CALLBACK_2(RBListControl::onRbSpawnClicked, this));//Add spawn click listener
    _listView->pushBackCustomItem(entry);

    _rbLayoutMap[name] = entry;
}

void RigidbodiesPanelUI::deleteEntry(std::string n)
{
    //If same name entry no found exit
    if (_rbLayoutMap.find(n) == _rbLayoutMap.end())
        return;

    auto a = _rbLayoutMap.at(n);
    //_rbEntriesLayout->removeChild(a);
    //_rbLayoutMap.erase(n);

    if (_rbLayoutMap.size() == 0)
    {
        selectedEntryName = "";
    }
    if (selectedEntryName == n)
    {
        //selectEntry((*_rbLayoutMap.begin()).first);
        selectedEntryName = "";
    }
}

void RigidbodiesPanelUI::addSpwnBtnListener(std::function<void(std::string)> callback)
{
}

void RigidbodiesPanelUI::onRbEntryClicked(Ref* ref, Widget::TouchEventType touchType)
{
    if (touchType == Widget::TouchEventType::ENDED)
    {
        auto t = dynamic_cast<RbEntryLayout*>(ref);
        if (onAListingClicked)
            onAListingClicked(t->listingName);
    }
}

//--------------------------------
//Rigidbodies Toolbar Layout Class
//--------------------------------

bool RbToolbarLayout::init()
{
    if (!Layout::init())
        return false;

    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setLayoutType(Layout::Type::HORIZONTAL);
    setBackGroundImage("Sprites/newicons/round_purple_dark.png");
    setBackGroundImageScale9Enabled(true);
    setBackGroundImageCapInsets(Rect(16, 16, 32, 32));
    setBackGroundColor(Color3B(86, 0, 232));

    auto lp = LinearLayoutParameter::create();
    lp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    lp->setMargin(Margin(3, 0, 3, 0));

    //Add new icon
    {
        auto cmplxBtn = ComplexButton1::create();
        cmplxBtn->setContentSize(Size(63, 27));
        cmplxBtn->setup("Sprites/newicons/ic_plus.png", "Add");
        cmplxBtn->icon->setScale(0.23f);
        addChild(cmplxBtn, 0, "btn_add");
        cmplxBtn->setLayoutParameter(lp);
        _addRbBtn = cmplxBtn;
    }

    //Add delete icon
    {
        auto cmplxBtn = ComplexButton1::create();
        cmplxBtn->setContentSize(Size(70, 27));
        cmplxBtn->setup("Sprites/newicons/ic_trashcanOpen.png", "Delete");
        cmplxBtn->icon->setScale(0.23f);
        cmplxBtn->setLayoutParameter(lp->clone());
        addChild(cmplxBtn, 0, "btn_del");
        _delRbBtn = cmplxBtn;
    }

    //Add rename icon
    {
        auto cmplxBtn = ComplexButton1::create();
        cmplxBtn->setContentSize(Size(85, 27));
        cmplxBtn->setup("Sprites/icons/ic_edit.png", "Rename");
        cmplxBtn->setLayoutParameter(lp->clone());
        addChild(cmplxBtn, 0, "btn_ren");
        _renRbBtn = cmplxBtn;
    }

    return true;
}

void RbToolbarLayout::setupWithSize(Size s)
{
    setContentSize(s);
}

void RbToolbarLayout::onAButtonCallback(Ref* sender, Widget::TouchEventType t)
{
    if (t == Widget::TouchEventType::ENDED)
    {
        auto s = ((Button*)sender)->getName();
        //CCLOG("Call from %s", s.c_str());
        if (_onClickEventFromButtons)
        {
            std::string a{ ((Button*)sender)->getName() };
            _onClickEventFromButtons(a);
        }
    }
}


//----------------------
//RBEntry layout class
//----------------------

bool RbEntryLayout::init()
{
    if (!Layout::init())
        return false;

    setContentSize(Size(100, 40));//Default size

    //Self init
    setLayoutType(Layout::Type::ABSOLUTE);
    setBackGroundImage("Sprites/newicons/round_purple_sbright.png");
    setBackGroundImageCapInsets(Rect(16, 16, 32, 32));
    setBackGroundImageScale9Enabled(true);

    //init Rigidbody icon 
    {
        //_rbNameBannerLayout = Layout::create();
        //_rbNameBannerLayout->setLayoutType(Layout::Type::ABSOLUTE);
        //_rbNameBannerLayout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        //_rbNameBannerLayout->setBackGroundColor(Color3B::WHITE);
        //addChild(_rbNameBannerLayout);

        _rbIcon = ImageView::create("Sprites/newicons/shapeicon.png");
        _rbIcon->setScale(0.2f);
        addChild(_rbIcon);
    }
    //init bodyname text
    {
        TTFConfig tc;
        tc.fontFilePath = "fonts/arial.ttf";
        tc.fontSize = 23;
        tc.distanceFieldEnabled = true;

        _bodyNameText = Label::createWithTTF(tc, "");
        _bodyNameText->setTextColor(Color4B::BLACK);
        _bodyNameText->setDimensions(100, 24);
        addChild(_bodyNameText);
    }

    //Add spawnbutton
    {
        _spwnBtn = Button::create("Sprites/icons/ic_add.png");
        _spwnBtn->setUserData((void*)this);//set buttons user pointer to this layout
        addChild(_spwnBtn, 1);
        _spwnBtn->setVisible(false);
    }

    return true;
}

void RbEntryLayout::setup(Size size, std::string name)
{
    //First time initialize
    listingName = name;
    //Set self size
    setContentSize(size);
    Size s = getContentSize();
   
    //Position icon
    {
        _rbIcon->setPosition(Vec2(25, 20));
        _rbIcon->setColor(Color3B::BLACK);
    }

    //Position _bodyNameText
    {
        _bodyNameText->setPosition(Vec2(100, 20));
        _bodyNameText->setString(name);
    }
}

void RbEntryLayout::enableFocusState(bool enable)
{
    //if (enable)
    //{
    //    _rbNameBannerLayout->setBackGroundColor(Color3B(74, 171, 191));
    //}
    //else
    //{
    //    _rbNameBannerLayout->setBackGroundColor(Color3B::WHITE);
    //}
}
