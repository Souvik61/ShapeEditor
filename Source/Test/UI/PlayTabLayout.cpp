#include "PlayTabLayout.h"
#include "box2d/include/box2d/box2d.h"
#include "Test/b2d/B2dManager.h"

USING_NS_CC;
USING_NS_CC::ui;

//--------------------------------
//PlayTabLayout
//--------------------------------

bool PlayTabLayout::init()
{
	if (!Layout::init())
	{
		return false;
	}

	return true;
}

void PlayTabLayout::initLayout()
{
    Size s = getContentSize();


    //Init clipping node
    auto _clipNode = ClippingNode::create();
    _clipNode->setContentSize(s);
    this->addChild(_clipNode);

    //::Helper::makeBound(_clipNode);

    //Init Stencil
    auto _clipStencil = DrawNode::create();
    _clipNode->setStencil(_clipStencil);
    _clipNode->setInverted(1);

    _clipStencil->drawSolidRect(Vec2::ZERO, Vec2(s.width - 20, s.height - 20), Color4F::MAGENTA);
    _clipStencil->setContentSize(Size(s.width - 20, s.height - 50));
    viewSize.setSize(s.width - 20, s.height - 50);

    //Add a black border
    auto border = DrawNode::create();
    border->drawRect(Vec2::ZERO, Vec2(s.width - 20, s.height - 20), Color4F::BLACK);
    border->setPosition(10, 10);
    //addChild(border, 1); temporarily disable for now

    Size s1 = _clipStencil->getContentSize();
    _clipNode->setPosition((s.width - s1.width) / 2, ((s.height - s1.height) / 2) - 15);

    //Init window layout
    {
        auto _windowLayout = ui::Layout::create();
        _clipNode->addChild(_windowLayout);

        //Setup Layout
        _windowLayout->setContentSize(s);
        _windowLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _windowLayout->setLayoutType(ui::Layout::Type::HORIZONTAL);
        _windowLayout->setBackGroundImage("Sprites/background_white.png");
        _windowLayout->setBackGroundImageScale9Enabled(true);
        _windowLayout->setBackGroundImageCapInsets(Rect(3, 3, 10, 10));
        _windowLayout->setPosition(Vec2((s.width / 2) - ((s.width - s1.width) / 2), (s.height / 2) - (s.height - s1.height) / 2 + 15));
    }
    //Add a second panel
    {
        //Draw gray background
        auto dN = DrawNode::create();
        dN->drawSolidRect(Vec2(-100, -100), s * 10, Color4B(167, 167, 170, 255));
        _clipNode->addChild(dN, -1);
    }

    //Add Physics world control panel
    {
        pCtrlPanel = PlayTabCtrlPanel::create();
        addChild(pCtrlPanel, -1);

        pCtrlPanel->setPosition(Vec2(s.width / 2, 25));
    }

}

//-------------------
//PlayTabCtrlPanel
//-------------------

bool PlayTabCtrlPanel::init()
{
    if (!Layout::init())
    {
        return false;
    }

    auto s = Size(200, 50);

    //Setup Layout
    setContentSize(s);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setLayoutType(Layout::Type::ABSOLUTE);
    setBackGroundImage("Sprites/background.png");
    setBackGroundImageScale9Enabled(true);
    setBackGroundImageCapInsets(Rect(3, 3, 10, 10));

    TTFConfig config;
    config.fontSize = 17;
    config.distanceFieldEnabled = true;

    //Add clear button 
    Button* button = Button::create("Sprites/ui/button.png", "Sprites/ui/buttonHighlighted.png");
    button->setContentSize(Size(130, 40));
    button->setTitleText("Clear shapes");
    button->setTitleFontSize(18);
    button->setZoomScale(0.05f);
    button->setScale9Enabled(true);
    button->setPressedActionEnabled(true);
    addChild(button, 0, "clear");
    button->addTouchEventListener([this](Ref* s, Widget::TouchEventType t) {

        if (t == Widget::TouchEventType::ENDED) {
            auto n = dynamic_cast<Button*>(s)->getName();

            std::string nStr{ n };

            this->onAKeyPressed(nStr);
        }

        });

    button->setPosition(Vec2(100, 27));

    return true;

}

void PlayTabCtrlPanel::onAKeyPressed(std::string s)
{
    if (eOnButtonPress)
        eOnButtonPress(s);
}
