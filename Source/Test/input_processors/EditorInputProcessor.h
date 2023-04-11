#ifndef __EDITOR_INPUT_PROCESSOR_H__
#define __EDITOR_INPUT_PROCESSOR_H__

#include "cocos2d.h"
#include "../UtilityClasses.h"

class EditorPanelUI;
class EditorManager;

//Input processor
//Encapsulates logic that will occur when an editor input occurs
//Different editor modes has different processors each inherits from this class
class EditorInputProcessor
{
public:
	EditorPanelUI* _editorPanel;
	EditorManager* editManager;
public:
	virtual void onMouseUp(CustomMouseEvent);
	virtual void onMouseMoved(CustomMouseEvent);
	virtual void onMouseDown(CustomMouseEvent);
	virtual void onMouseScroll(CustomMouseEvent);

	virtual void onKeyDown(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	virtual void onKeyUp(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
public:
	void setEditorPanel(EditorPanelUI* p) { _editorPanel = p; }
	void setEditorManager(EditorManager* man) { editManager = man; }
};

#endif // __EDITOR_INPUT_PROCESSOR_H__
