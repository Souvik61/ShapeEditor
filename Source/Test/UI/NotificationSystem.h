#ifndef __NOTIFICATION_SYSTEM_H__
#define __NOTIFICATION_SYSTEM_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//Notification System
//To display error messages
class NotificationSystem : public ax::Node
{
private:
    enum AnimState { HIDDEN, RUNNING, VISIBLE };
    AnimState _aState;
public:
    //Notification layout will slide along this point.
    ax::Vec2 anchor;

    ax::ui::Layout* notifBoard;
    ax::ui::Text* notifText;
public:
    virtual bool init() override;
    void onEnter() override;
    void addUIComponents();
    //Finalize object setup with anchor point
    void setup(ax::Vec2 anch);

    //Will be called 0.1s after onEnter().
    void point1SecAfteronEnter();

    // implement the "static create()" method manually
    CREATE_FUNC(NotificationSystem);

    //Other funcs

    void startAnimatePanel();
    void showNotification(std::string msg);

    //Callbacks
    void afterNotifActionComplete();

};

#endif // __NOTIFICATION_SYSTEM_H__