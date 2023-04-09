#ifndef __TESTSCENE_9_H__
#define __TESTSCENE_9_H__

#include "cocos2d.h"
#include "Test/UISubsystem.h"

class OverallManager;
class NewEditorPanelUI;

class TestScene9 : public cocos2d::Scene
{
public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    OverallManager* _manager;
    //EditorPanel* _editorPanel;
    //RBPanel* _rbPanel;
    //ProjectPanel* _prjPanel;
    UISubsystem* _uiSystem;
    NewEditorPanelUI* panelUI;
    ax::Camera* b2Cam;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    

    void addUISubsystem();
    void addB2DSystem();
    void addGridDraw();

    void addCloseButton();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene9);
};

#endif // __TESTSCENE_9_H__
