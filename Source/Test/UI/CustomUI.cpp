#include "CustomUI.h"
#include "Utils/Helpers.h"

USING_NS_AX;
USING_NS_AX::ui;

//---------------------
//Complex button class
//---------------------

bool ComplexButton1::init()
{
    if (!Button::init("Sprites/newicons/round_purple.png", "Sprites/newicons/round_purple_pressed.png", "Sprites/newicons/round_purple_disabled.png"))
    {
        return false;
    }

    setContentSize(Size(80, 40));
    setScale9Enabled(true);
    setCapInsets(Rect(16, 16, 32, 32));

    return true;
}

void ComplexButton1::setup(std::string buttonImgPath, std::string buttonText)
{
    Vec2 prevPos;

    auto s = getContentSize();
    //Add image
    auto imgV = ImageView::create(buttonImgPath);
    imgV->setScale(0.75f);
    addChild(imgV);
    imgV->setPositionX(15);
    imgV->setPositionY(s.height / 2);
    prevPos = imgV->getPosition();
    icon = imgV;

    //Add label
    TTFConfig con;
    con.fontFilePath = "fonts/arial.ttf";
    con.fontSize = 15;
    con.distanceFieldEnabled = true;

    auto label = Label::createWithTTF(con, buttonText);
    auto s1 = label->getContentSize();
    addChild(label);
    label->setPositionX(prevPos.x + 10 + (s1.width / 2));
    label->setPositionY(s.height / 2);
    text = label;
}
