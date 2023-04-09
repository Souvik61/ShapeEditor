#ifndef __PROJECTPANEL_UI_H__
#define __PROJECTPANEL_UI_H__

#include "axmol.h"
#include "ui/CocosGUI.h"

class ProjectPanelUI : public ax::Node
{
public:
    //On a btn pressed callback 
    //Parameter string has the following vals [ic_add,ic_edit,ic_del];
    std::function<void(std::string)> onBtnPressedCallback;

    ax::ui::Layout* _windowLayout;
    ax::ui::Text* pp_text;
public:

    virtual bool init();
    void addOtherUIComponents();

    void setupWithSize(const ax::Size& size);

    void setProjectNameText(std::string n) { pp_text->setString(n); }
    void onButtonClicked(ax::Ref*, ax::ui::Widget::TouchEventType);
    // implement the "static create()" method manually
    CREATE_FUNC(ProjectPanelUI);
};

#endif // __PROJECTPANEL_UI_H__