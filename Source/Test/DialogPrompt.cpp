#include "DialogPrompt.h"
#include "Utils/Helpers.h"

USING_NS_AX;
USING_NS_CC::ui;

//-------------------
//Dialog Prompt Node
//-------------------

bool DialogPrompt::init()
{
    setContentSize(_director->getVisibleSize());
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    //Setup touch listener
    {
        _tListener = EventListenerTouchOneByOne::create();
        _tListener->setSwallowTouches(true);
        _tListener->onTouchBegan = CC_CALLBACK_2(DialogPrompt::onTouchBegan, this);
        //_eventDispatcher->addEventListenerWithSceneGraphPriority(_tListener, this);
    }

    //dialogWindow = DialogPromptWindow::create();
    //addChild(dialogWindow);
    //dialogWindow->setPosition(getContentSize() / 2);

    return true;
}

bool DialogPrompt::onTouchBegan(Touch* t, Event* e)
{
    auto bounds = e->getCurrentTarget()->getBoundingBox();

    if (bounds.containsPoint(t->getLocationInView())) {
        
        CCLOG("Touched");
    }
    return true;
}

//-----------------------------
//Image Select Dialog Window
//-----------------------------

bool ImageSelectDialogWindow::init()
{
    if (!Layout::init())
        return false;

    Size s = Size(360, 225);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //setBackGroundImage("Sprites/background.png");
    setBackGroundImage("Sprites/newicons/round_purple_sbright.png");
    setBackGroundImageCapInsets(Rect(16, 16, 32, 32));
    setBackGroundImageScale9Enabled(true);
    setContentSize(s);

    Vec2 pos;

    //Setup touch listener
    {
        _tListener = EventListenerTouchOneByOne::create();
        _tListener->setSwallowTouches(true);
        _tListener->onTouchBegan = CC_CALLBACK_2(ImageSelectDialogWindow::onTouchBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_tListener, this);
    }
    //Set Window displaytext
    {
        auto t = Text::create("Select Image", "fonts/arial.ttf", 30);
        t->setTextColor(Color4B::BLACK);
        addChild(t);
        _windowNameTextField = t;
        auto tSize = t->getContentSize();
        t->setPosition(Vec2(tSize.width / 2 + 10, s.height - (tSize.height / 2)));
        pos = t->getPosition();
    }

    //Add Path to image text box
    {
        Text* prjLabel = Text::create("Image file:", "fonts/arial.ttf", 18);
        //prjLabel->enableShadow();
        prjLabel->setTextColor(Color4B::BLACK);
        addChild(prjLabel, 1);
        prjLabel->setPosition(Vec2(prjLabel->getContentSize().width / 2 + 10, pos.y - 50));
        pos = prjLabel->getPosition();

        //Text box
        {
            auto textBoxLayout = Layout::create();
            textBoxLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            textBoxLayout->setLayoutType(Layout::Type::ABSOLUTE);
            textBoxLayout->setBackGroundImage("Sprites/newicons/round_purple_dark.png");
            textBoxLayout->setBackGroundImageScale9Enabled(true);
            textBoxLayout->setBackGroundImageCapInsets(Rect(16, 16, 32, 32));
            textBoxLayout->setContentSize(Size(240, 25));
            addChild(textBoxLayout);
            textBoxLayout->setPosition(Vec2(pos.x + (textBoxLayout->getContentSize().width / 2) + 50, pos.y));

            auto text = Text::create("none", "fonts/arial.ttf", 17);
            text->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            text->setTextColor(Color4B::BLACK);
            text->setTextAreaSize(Size(233, 18));
            text->setTextHorizontalAlignment(TextHAlignment::LEFT);
            textBoxLayout->addChild(text);
            text->setPosition(Vec2(7, 12.5));
            pathTextDisplay = text;
            //::Helper::makeBound(textBoxLayout);
            //::Helper::makeBound(text);
            pos = textBoxLayout->getPosition();
        }

    }
    
    //Create clear button
    {
        auto clearBtn = Button::create("Sprites/newicons/round_purple.png", "Sprites/newicons/round_purple_pressed.png");
        clearBtn->setTitleText("Clear");
        clearBtn->setTitleFontSize(22);
        clearBtn->setScale9Enabled(true);
        clearBtn->setCapInsets(Rect(16, 16, 32, 32));
        clearBtn->setContentSize(Size(75, 30));
        addChild(clearBtn, 1, "clear");
        clearBtn->addTouchEventListener(CC_CALLBACK_2(ImageSelectDialogWindow::onButtonClicked, this));
        clearBtn->setPosition(Vec2(pos.x - 40, pos.y - 45));

    }
    //Create browse button
    {
        auto browseBtn = Button::create("Sprites/newicons/round_purple.png", "Sprites/newicons/round_purple_pressed.png");
        browseBtn->setTitleText("Browse");
        browseBtn->setTitleFontSize(22);
        browseBtn->setScale9Enabled(true);
        browseBtn->setCapInsets(Rect(16, 16, 32, 32));
        browseBtn->setContentSize(Size(85, 30));
        addChild(browseBtn, 1, "browse");
        browseBtn->addTouchEventListener(CC_CALLBACK_2(ImageSelectDialogWindow::onButtonClicked, this));
        browseBtn->setPosition(Vec2(pos.x + 50, pos.y - 45));
    }
    //Create ok button
    {
        auto cancelBtn = Button::create("Sprites/newicons/round_purple.png", "Sprites/newicons/round_purple_pressed.png");
        cancelBtn->setTitleText("Ok");
        cancelBtn->setTitleFontSize(22);
        cancelBtn->setScale9Enabled(true);
        cancelBtn->setCapInsets(Rect(16, 16, 32, 32));
        cancelBtn->setContentSize(Size(75, 30));
        addChild(cancelBtn, 1, "ok");
        cancelBtn->addTouchEventListener(CC_CALLBACK_2(ImageSelectDialogWindow::onButtonClicked, this));
        cancelBtn->setPosition(Vec2(s.width / 2, 30));

    }

    return true;
}

void ImageSelectDialogWindow::runPromptAnim()
{
    auto a = ScaleTo::create(0.09, 1.1f);
    auto b = ScaleTo::create(0.09, 1);
    runAction(Sequence::create(a, b, nullptr));
}

void ImageSelectDialogWindow::onButtonClicked(Ref* s, Widget::TouchEventType t)
{
    if (t == Widget::TouchEventType::ENDED)
    {
        auto a = dynamic_cast<Button*>(s);
        //Callback
        if (OnAButtonClicked)
        {
            std::string b{ a->getName() };
            OnAButtonClicked(b);
        }
    }
}

bool ImageSelectDialogWindow::onTouchBegan(ax::Touch* t, ax::Event* e)
{
    auto target = static_cast<ImageSelectDialogWindow*>(e->getCurrentTarget());
    Vec2 locationInNode = target->convertToNodeSpace(t->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);

    if (rect.containsPoint(locationInNode))
    {
        return true;
    }
    target->runPromptAnim();
    return true;
}

//----------------------
//Dialog Prompt Window 
//----------------------

bool DialogPromptWindow::init()
{
    if (!Layout::init())
        return false;

    Size s = Size(360, 225);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setBackGroundImage("Sprites/background.png");
    setBackGroundImageCapInsets(Rect(3, 3, 10, 10));
    setBackGroundImageScale9Enabled(true);
    setContentSize(s);

    Vec2 pos;

    //Setup touch listener
    {
        _tListener = EventListenerTouchOneByOne::create();
        _tListener->setSwallowTouches(true);
        _tListener->onTouchBegan = CC_CALLBACK_2(DialogPromptWindow::onTouchBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_tListener, this);
    }
    //Set Window displaytext
    {
        auto t = Text::create("Rename", "fonts/arial.ttf", 45);
        t->setTextColor(Color4B::BLACK);
        t->enableShadow(Color4B::WHITE);
        addChild(t);
        _windowNameTextField = t;
        t->setPosition(Vec2(s.width / 2, s.height - (t->getContentSize().height / 2)));
    }
    //Set text field background
    {
        Scale9Sprite* sp = Scale9Sprite::create("Sprites/buttonBackground.png");
        sp->setContentSize(Size(200, 40));
        sp->setCapInsets(Rect(3, 3, 10, 10));
        sp->setPosition(s / 2);
        addChild(sp);
        pos = sp->getPosition();
    }
    // Create the textfield
    {
        _textField = TextField::create("Type here", "fonts/arial.ttf", 30);
        _textField->setPosition(s / 2);
        //textField->addEventListener(CC_CALLBACK_2(UITextFieldTest::textFieldEvent, this));
        _textField->setMaxLengthEnabled(true);
        _textField->setMaxLength(8);//Maximum name size 8 chars.
        _textField->setCursorEnabled(true);
        addChild(_textField);
    }
    //Create warning img
    {
        _tipImg = ImageView::create("Sprites/icons/ic_warning.png");
        _tipImg->setScale(0.4f);
        addChild(_tipImg, 2);
        _tipImg->setPosition(pos + Vec2(-150, -35));
        pos = _tipImg->getPosition();
    }
    //Create warning text
    {
        tipText = Text::create("Name must not start or end with (WHITESPACE).", "fonts/arial.ttf", 15);
        tipText->setTextColor(Color4B::RED);
        addChild(tipText);
        tipText->setPosition(pos + Vec2(tipText->getContentSize().width / 2 + 15, 0));
    }
    //Create ok button
    {
        auto _okBtn = Button::create("Sprites/background1.png");
        _okBtn->setTitleText("Ok");
        _okBtn->getTitleRenderer()->enableBold();
        _okBtn->setTitleFontSize(25);
        _okBtn->setScale9Enabled(true);
        _okBtn->setCapInsets(Rect(3, 3, 10, 10));
        _okBtn->setContentSize(Size(100, 35));
        addChild(_okBtn, 0, "ok");
        _okBtn->setPosition(Vec2(s.width / 4, 30));
        _okBtn->addTouchEventListener(CC_CALLBACK_2(DialogPromptWindow::onButtonClicked, this));

    }
    //Create cancel button
    {
        auto _cancelBtn = Button::create("Sprites/background1.png");
        _cancelBtn->setTitleText("Cancel");
        _cancelBtn->getTitleRenderer()->enableBold();
        _cancelBtn->setTitleFontSize(25);
        _cancelBtn->setScale9Enabled(true);
        _cancelBtn->setCapInsets(Rect(3, 3, 10, 10));
        _cancelBtn->setContentSize(Size(100, 35));
        addChild(_cancelBtn, 0, "cancel");
        _cancelBtn->setPosition(Vec2(s.width - s.width / 4, 30));
        _cancelBtn->addTouchEventListener(CC_CALLBACK_2(DialogPromptWindow::onButtonClicked, this));
    }
    //Do not show warning at init
    hideWarning();
    return true;
}

void DialogPromptWindow::runPromptAnim()
{
    auto a = ScaleTo::create(0.09, 1.1f);
    auto b = ScaleTo::create(0.09, 1);
    //this->runAction(a);
    this->runAction(Sequence::create(a, b, nullptr));
}

void DialogPromptWindow::setWindowName(std::string n)
{
    _windowNameTextField->setString(n);
}

void DialogPromptWindow::showWarning(std::string warning)
{
    tipText->setString(warning);
    tipText->setPosition(_tipImg->getPosition() + Vec2(tipText->getContentSize().width / 2 + 15, 0));//Calculate pos
    _tipImg->setVisible(true);
    tipText->setVisible(true);
}

void DialogPromptWindow::onButtonClicked(Ref* s, Widget::TouchEventType t)
{
    if (t == Widget::TouchEventType::ENDED)
    {
        auto a = dynamic_cast<Button*>(s);
        //Callback
        if (OnAButtonClicked)
        {
            std::string b{ a->getName() };
            OnAButtonClicked(b);
        }
    }
}

bool DialogPromptWindow::onTouchBegan(Touch* t, Event* e)
{
    auto target = static_cast<DialogPromptWindow*>(e->getCurrentTarget());

    Vec2 locationInNode = target->convertToNodeSpace(t->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);

    if (rect.containsPoint(locationInNode))
    {
        return true;
    }
    target->runPromptAnim();
    return true;
}