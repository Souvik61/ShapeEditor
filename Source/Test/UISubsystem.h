#ifndef __UI_SUBSYSTEM_H__
#define __UI_SUBSYSTEM_H__

#include "cocos2d.h"
#include "Test/UI/EditorPanelUI.h"
#include "Test/UI/RigidbodiesPanelUI.h"
#include "Test/UI/ProjectPanelUI.h"
#include "Test/UI/NotificationSystem.h"

class UISubsystem : public cocos2d::Node
{
public:
    ProjectPanelUI* prjPanelUI;
    RigidbodiesPanelUI* rbPanelUI;
    EditorPanelUI* editPanelUI;
    NotificationSystem* notifSys;

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(UISubsystem);

private:

};

#endif // __UI_SUBSYSTEM_H__