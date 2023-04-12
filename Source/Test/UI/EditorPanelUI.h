#ifndef __EDITORPANEL_UI_H__
#define __EDITORPANEL_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Test/UI/EditorScreenInterface.h"
#include "Test/UtilityClasses.h"

class OverallManager;
//class EditorInputProcessor;
class EditorManager;
class EditorTabLayout;
class PlayTabLayout;

//EditorUI Panel just the UI Panel
class EditorPanelUI : public ax::Node
{
public:
	//Callbacks
	std::function<void(int)> OnTabChanged;
public:
	EditorMode mode;
	OverallManager* oManager;
	PlayTabLayout* playTab;
	ax::Size viewSize;
	EditorMode _prevMode;//Previous mode that was active
	ax::DrawNode* _mousePointer;
	ax::ui::Layout* _windowLayout;
	ax::EventListenerKeyboard* _listenerKey;
	EditorScreenInterface* _screenInterface;
	ax::Label* _modeLabel; //Label to display mode status
	EditorManager* editManager;

public:
	
	bool init();
	CREATE_FUNC(EditorPanelUI);
	void addNewUI();
	void initWithManager(OverallManager* manager);

	//@unimplemented implement later
	ax::Vec2 getWorldViewPortMidpoint() { return this->convertToWorldSpace(viewMid->getPosition()); }

	//Callbacks
	
	//On tab changed
	void onTabChanged(int, ax::ui::TabControl::EventType evtType);

	//Mouse Callbacks
	virtual void onMouseDown(ax::EventMouse*);
	virtual void onMouseMoved(ax::EventMouse*);
	virtual void onMouseUp(ax::EventMouse*);
	virtual void onMouseScroll(cocos2d::EventMouse*);
	
	//Keyboard callbacks
	void onKeyDown(ax::EventKeyboard::KeyCode, ax::Event*);
	void onKeyUp(ax::EventKeyboard::KeyCode, ax::Event*);

	//Change mode by passing in mode enum
	void changeModeUI(EditorMode mode);
	//This function is useful when transitioning from play tab
	void changeToModeFromPlay();

private:
	//This node is kept at the mid of viewport because reasons
	ax::DrawNode* viewMid;
};

#endif // __NEW_EDITORPANEL_UI_H__