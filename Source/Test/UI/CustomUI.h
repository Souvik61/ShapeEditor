#ifndef __CUSTOM_UI_H__
#define __CUSTOM_UI_H__

#include "axmol.h"
#include "ui/CocosGUI.h"

class ComplexButton1 : public ax::ui::Button
{
public:
    ax::ui::ImageView* icon;
    ax::Label* text;
public:
    bool init() override;
    CREATE_FUNC(ComplexButton1);

    void setup(std::string buttonImgPath, std::string buttonText);

};

#endif //__CUSTOM_UI_H__