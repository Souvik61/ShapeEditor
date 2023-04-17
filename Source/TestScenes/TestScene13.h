#ifndef __TESTSCENE_13_H__
#define __TESTSCENE_13_H__

#include "cocos2d.h"
#include "Test/UISubsystem.h"

class OverallManager;
class EditorPanelUI;

class TestScene13 : public ax::Scene
{
public:
    ax::Size visibleSize;
    ax::Vec2 origin;
    OverallManager* _manager;
    UISubsystem* _uiSystem;
    ax::Camera* b2Cam;
    EditorPanelUI* editPanelUI;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    

    void addUISubsystem();
    void addB2DSystem();
    void addGridDraw();
    
    //void addCloseButton();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene13);
};

#endif // __TESTSCENE_13_H__
