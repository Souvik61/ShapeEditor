#include "EditorTabLayout.h"
#include "Utils/Helpers.h"
#include "Test/draw/BackGrid.h"
#include "Test/UI/CustomUI.h"

USING_NS_CC;
USING_NS_CC::ui;

//-----------------
//EditorTabLayout
//-----------------

bool EditorTabLayout::init()
{
	if (!Layout::init())
	{
		return false;
	}

	return true;
}

void EditorTabLayout::initLayout()
{
    //A void pointer for reasons we do not know yet
    void* general;

    Size s = getContentSize();

    //::Helper::makeBound(this);

    //Init clipping node
    auto _clipNode = ClippingNode::create();
    _clipNode->setContentSize(s);
    this->addChild(_clipNode);

    //Init Stencil
    auto _clipStencil = DrawNode::create();
    _clipStencil->drawSolidRect(Vec2::ZERO, Vec2(s.width - 20, s.height - 20), Color4F::MAGENTA);
    _clipStencil->setContentSize(Size(s.width - 20, s.height - 20));
    _clipNode->setStencil(_clipStencil);
    _clipNode->setInverted(1);

    
    viewSize.set(s.width - 20, s.height - 20);

    //Add a black border
    auto border = DrawNode::create();
    border->drawRect(Vec2::ZERO, Vec2(s.width - 20, s.height - 20), Color4F::BLACK);
    border->setPosition(10, 10);
    addChild(border, 3);

    Size s1 = _clipStencil->getContentSize();
    _clipNode->setPosition((s.width - s1.width) / 2, ((s.height - s1.height) / 2));
    
    //Init window layout
    {
        auto _windowLayout = ui::Layout::create();
        _clipNode->addChild(_windowLayout);
        general = _windowLayout;
        //Setup Layout
        _windowLayout->setContentSize(s);
        _windowLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _windowLayout->setLayoutType(ui::Layout::Type::HORIZONTAL);
        _windowLayout->setBackGroundImage("Sprites/background_white.png");
        _windowLayout->setBackGroundImageScale9Enabled(true);
        _windowLayout->setBackGroundImageCapInsets(Rect(3, 3, 10, 10));

        //_windowLayout->setPositionNormalized(Vec2::ANCHOR_MIDDLE);
        _windowLayout->setPosition(Vec2((s.width / 2) - ((s.width - s1.width) / 2), (s.height / 2) - (s.height - s1.height) / 2));
    }

    //Add a second panel
    {
        //Draw gray background
        auto dN = DrawNode::create();
        dN->drawSolidRect(Vec2(-100, -100), s * 10, Color4B(167, 167, 170, 255));
        _clipNode->addChild(dN, -1);
    }

    //Draw checkered background
    {
        auto bG = BackGrid::create();
        bG->setVisible(false);
        addChild(bG, 2);
        bG->setContentSize(viewSize);

        bG->setPosition((s / 2) - (viewSize / 2));

        bG->gridSize = viewSize;//Set total grid size
        bG->cellSize.set(10, 10);//Set cell size
        bG->validateGrid();
    }

    //Add a RenderTexture
    {
        //Render textures and associates
        _rend = RenderTexture::create(viewSize.width, viewSize.height, backend::PixelFormat::RGBA8, true);
        _rend->retain();
        _rend->setKeepMatrix(true);
        _rend->setVirtualViewport(Vec2(0, 0), Rect(0, 0, 1280, 720), Rect(0, 0, viewSize.width, viewSize.height));

        //The actual sprite to be drawn on by rendertex
        auto _spriteDraw = Sprite::createWithTexture(_rend->getSprite()->getTexture());
        auto spSize = _spriteDraw->getContentSize();
        _spriteDraw->setScaleY(-1);
        _spriteDraw->setPosition(s / 2);
        addChild(_spriteDraw, 2);
        renderSprite = _spriteDraw;
        //::Helper::makeBound(_spriteDraw, Color4F::GREEN);

        viewPlaceholder = Node::create();
        viewPlaceholder->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        viewPlaceholder->setContentSize(spSize);
        viewPlaceholder->setPosition(s / 2);
        addChild(viewPlaceholder, 12);
        //::Helper::makeBound(viewPlaceholder, Color4F::GREEN);

    }

    //Add "Press M to change mode" text
    {
        auto lay = static_cast<Layout*>(general);
        auto s = lay->getContentSize();
        auto lab = Label::createWithTTF("Press 'M' to change mode.", "fonts/arial.ttf", 18);
        lab->setTextColor(Color4B::BLACK);
        lay->addChild(lab, 2);

        lab->setPositionX(s.width / 4 + 25);
        lab->setPositionY(s.height - 25);
    }

    addModeDisplay();

    addToolbar();

    //::Helper::makeBound(this);
}

void EditorTabLayout::addModeDisplay()
{
    Size s = getContentSize();

    auto _modeDisplay = DrawNode::create();
    _modeDisplay->setContentSize(Size(150, 25));
    _modeDisplay->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(_modeDisplay, 4);
    _modeDisplay->drawSolidRect(Vec2::ZERO, Vec2(150, 25), Color4F::GRAY);

    TTFConfig con;
    con.fontFilePath = "fonts/arial.ttf";
    con.fontSize = 22;
    con.distanceFieldEnabled = true;

    //Add mode status label
    modeLabel = Label::createWithTTF(con, "t");
    //_modeLabel->enableBold();
    modeLabel->enableShadow(Color4B::GRAY);
    modeLabel->setTextColor(Color4B::GREEN);
    _modeDisplay->addChild(modeLabel, 1, 'm');
    modeLabel->setPosition(75, 12.5f);
    modeLabel->setAlignment(TextHAlignment::LEFT);
    modeLabel->setDimensions(140, 24);

    //::Helper::makeBound(modeLabel);

    _modeDisplay->setPosition(80, s.height - 40);
}

void EditorTabLayout::addToolbar()
{
    auto s = getContentSize();

    editorTabToolbar = EditorTabToolbarLayout::create();
    editorTabToolbar->initWithSize(Vec2(110, 70));
    addChild(editorTabToolbar, 3);
    //Set pos
    {
        editorTabToolbar->setPositionX(s.width - 55 - 15);
        editorTabToolbar->setPositionY(s.height - 35 - 15);
    }
}

//------------------------
//EditorTabToolbarLayout
//------------------------

bool EditorTabToolbarLayout::init()
{
    if (!Layout::init())
    {
        return false;
    }
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    return true;
}

void EditorTabToolbarLayout::initWithSize(Vec2 size)
{
    setContentSize(size);
    setLayoutType(ui::Layout::Type::CENTER_VERTICAL);
    setBackGroundImage("Sprites/newicons/round_purple_selected.png");
    setBackGroundImageScale9Enabled(true);
    setBackGroundImageCapInsets(Rect(16, 16, 32, 32));

    auto lp = LinearLayoutParameter::create();
    lp->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);

    {
        auto text = Text::create("Actions", "fonts/arial.ttf", 17);
        text->setTextColor(Color4B::BLACK);
        text->setLayoutParameter(lp);
        addChild(text, 1);
    }

    //Add insert points button
    {
        auto btn = Button::create("Sprites/newicons/round_purple.png", "Sprites/newicons/round_purple_pressed.png", "Sprites/newicons/round_purple_disabled.png");
        btn->setScale9Enabled(true);
        btn->setCapInsets(Rect(16, 16, 32, 32));
        btn->setContentSize(Size(100, 27));
        btn->setTitleText("Insert points");
        btn->setTitleFontSize(16);
        addChild(btn, 2, "");
        btn->setLayoutParameter(lp->clone());
        //cmplxBtn->addTouchEventListener(CC_CALLBACK_2(RbToolbarLayout::onAButtonCallback, this));
        insertPointsButton = btn;
    }
    
}
