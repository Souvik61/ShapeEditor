#include "ProjectPanelUI.h"
#include "Utils/Helpers.h"
#include "Test/UI/CustomUI.h"

USING_NS_AX;
USING_NS_AX::ui;

// on "init" you need to initialize your instance
bool ProjectPanelUI::init()
{ 
    //282, 178

    setContentSize(Size(282, 178));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    //Setup layout
    _windowLayout = ui::Layout::create();
    addChild(_windowLayout);

    Size selfSize = getContentSize();
    Vec2 abovePos;
    //Setup window Layout
    {
        Size s(selfSize.width - 10, selfSize.height - 50);
        _windowLayout->setContentSize(s);
        _windowLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _windowLayout->setLayoutType(ui::Layout::Type::ABSOLUTE);
        _windowLayout->setBackGroundImage("Sprites/newicons/round_purple_sbright.png");
        _windowLayout->setBackGroundImageScale9Enabled(true);
        _windowLayout->setBackGroundImageCapInsets(Rect(16, 16, 32, 32));

        //Set layout position in parent
        _windowLayout->setPositionX(selfSize.width / 2);
        _windowLayout->setPositionY(s.height / 2 + 5);
    }
    //Add project label
    {
        TTFConfig tc;
        tc.fontFilePath = "fonts/arial.ttf";
        tc.fontSize = 19;
        tc.distanceFieldEnabled = true;

        auto label = Label::createWithTTF(tc, "Project");
        //label->enableBold();
        //label->enableShadow(Color4B::GRAY);
        label->setTextColor(Color4B::BLACK);
        _windowLayout->addChild(label, 1, "label");

        auto s = label->getContentSize();
        auto s1 = _windowLayout->getContentSize();

        float x = s.width / 2 + 10;
        float y = s1.height - (s.height / 2) - 5;
        abovePos.set(x, y);
        label->setPosition(x, y);
    }
    //Add underline
    auto line = DrawNode::create(2);
    _windowLayout->addChild(line, 1, "line");
    //line->drawLine(Vec2::ZERO, Vec2(110, 0), Color4F::GRAY);
    line->setPositionX(7);
    line->setPositionY(abovePos.y - 11);

    addOtherUIComponents();

    //::Helper::makeBound(this);

    auto dN = DrawNode::create();
    dN->drawSolidRect(Vec2::ZERO, Vec2(getContentSize()), Color4B(167, 167, 170, 255));
    addChild(dN, -1);

    return true;
}

void ProjectPanelUI::addOtherUIComponents()
{
    auto line = _windowLayout->getChildByName("line");
    auto abovePos = line->getPosition();

    // Create the icons layout
    Layout* layout = Layout::create();
    layout->setContentSize(Size(225, 50));
    layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    layout->setLayoutType(Layout::Type::HORIZONTAL);
    //layout->setBackGroundImage("Sprites/round_violet.png");
    //layout->setBackGroundImageScale9Enabled(true);
    //layout->setBackGroundImageCapInsets(Rect(3, 3, 10, 10));
    _windowLayout->addChild(layout, 4);

    layout->setPosition(Vec2(layout->getContentSize().width / 2 + 5, abovePos.y - layout->getContentSize().height / 2 - 7));

    auto lp = LinearLayoutParameter::create();
    lp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    lp->setMargin(Margin(5, 0, 5, 0));

    //Add new icon
    {
        auto cmplxBtn = ComplexButton1::create();
        cmplxBtn->setContentSize(Size(63, 30));
        cmplxBtn->setup("Sprites/icons/ic_new.png", "New");
        layout->addChild(cmplxBtn, 0, "ic_new");
        cmplxBtn->setLayoutParameter(lp);
    }

    //Add load icon
    {
        auto cmplxBtn = ComplexButton1::create();
        cmplxBtn->setContentSize(Size(63, 30));
        cmplxBtn->setup("Sprites/newicons/ic_import.png", "Load");
        layout->addChild(cmplxBtn, 0, "ic_load");
        cmplxBtn->setLayoutParameter(lp);
        cmplxBtn->icon->setScale(0.23f);
    }
    //Add save icon
    {
        auto cmplxBtn = ComplexButton1::create();
        cmplxBtn->setContentSize(Size(63, 30));
        cmplxBtn->setup("Sprites/newicons/ic_save.png", "Save");
        layout->addChild(cmplxBtn, 0, "ic_save");
        cmplxBtn->setLayoutParameter(lp);
        cmplxBtn->icon->setScale(0.23f);
    }

    abovePos = layout->getPosition();

    //Add help button
    {
        auto cmplxBtn = ComplexButton1::create();
        cmplxBtn->setContentSize(Size(63, 30));
        cmplxBtn->setup("Sprites/newicons/ic_ques.png", "Help");
        _windowLayout->addChild(cmplxBtn, 0, "ic_help");
        cmplxBtn->icon->setScale(0.23f);

        float x = _windowLayout->getContentSize().width - 31.5 - 10;
        float y = _windowLayout->getContentSize().height - 15 - 5;

        cmplxBtn->setPosition(Vec2(x, y));
    }

    //Add Project file text box
    {
        // Create the icons layout
        Layout* layout = Layout::create();
        layout->setContentSize(Size(270, 32));
        layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        //layout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        //layout->setBackGroundColor(Color3B(86, 0, 232));
        layout->setLayoutType(Layout::Type::HORIZONTAL);
        //layout->setBackGroundImage("Sprites/round_violet.png");
        //layout->setBackGroundImageScale9Enabled(true);
        //layout->setBackGroundImageCapInsets(Rect(3, 3, 10, 10));
        _windowLayout->addChild(layout, 4);
        layout->setPosition(Vec2(layout->getContentSize().width / 2 + 5, abovePos.y - layout->getContentSize().height - 15));

        auto lp = LinearLayoutParameter::create();
        lp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        lp->setMargin(Margin(5, 0, 5, 0));

        Text* prjLabel = Text::create("Project file:", "fonts/arial.ttf", 18);
        //prjLabel->enableShadow();
        prjLabel->setTextColor(Color4B::BLACK);
        layout->addChild(prjLabel);
        prjLabel->setLayoutParameter(lp);

        //Text box
        {
            auto textBoxLayout = Layout::create();
            textBoxLayout->setLayoutType(Layout::Type::HORIZONTAL);
            textBoxLayout->setBackGroundImage("Sprites/newicons/round_purple_dark.png");
            textBoxLayout->setBackGroundImageScale9Enabled(true);
            textBoxLayout->setBackGroundImageCapInsets(Rect(16, 16, 32, 32));
            textBoxLayout->setContentSize(Size(127, 25));
            textBoxLayout->setLayoutParameter(lp->clone());
            layout->addChild(textBoxLayout);

            auto text = Text::create("none", "fonts/arial.ttf", 17);
            text->setTextColor(Color4B::BLACK);
            text->setLayoutParameter(lp->clone());
            text->setTextAreaSize(Size(120, 18));
            text->setTextHorizontalAlignment(TextHAlignment::LEFT);
            textBoxLayout->addChild(text);
            pp_text = text;
            //::Helper::makeBound(text);
        }

        //Add file open button
        {
            Button* button = Button::create("Sprites/icons/ic_open.png");
            button->addTouchEventListener(CC_CALLBACK_2(ProjectPanelUI::onButtonClicked, this));
            //button->setLayoutParameter(lp->clone());
            layout->addChild(button, 0, "ic_fopen");
        }

    }

}

void ProjectPanelUI::setupWithSize(const Size& size)
{
}

void ProjectPanelUI::onButtonClicked(Ref* sender, Widget::TouchEventType t)
{
    if (t == Widget::TouchEventType::ENDED)
    {
        Node* n = dynamic_cast<Node*>(sender);
        if (onBtnPressedCallback)
        {
            std::string a{ n->getName() };
            onBtnPressedCallback(a);//This is linked to event manager
        }
    }
}