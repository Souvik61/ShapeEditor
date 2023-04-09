#ifndef __TESTSCENE_11_H__
#define __TESTSCENE_11_H__

#include "cocos2d.h"
#include "Test/UISubsystem.h"

class OverallManager;
class EditorPanelUI;

//This marks the begining of a new era, complete ui overhaul
class TestScene11 : public ax::Scene
{
public:
    ax::Size visibleSize;
    ax::Vec2 origin;
    OverallManager* _manager;
    UISubsystem* _uiSystem;
    EditorPanelUI* panelUI;
    ax::Camera* b2Cam;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    

    void addUISubsystem();
    //void addB2DSystem();
    //void addGridDraw();
    //
    //void addCloseButton();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene11);
};

#endif // __TESTSCENE_11_H__
