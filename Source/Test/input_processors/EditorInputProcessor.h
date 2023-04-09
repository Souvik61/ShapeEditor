#ifndef __EDITOR_INPUT_PROCESSOR_H__
#define __EDITOR_INPUT_PROCESSOR_H__

#include "cocos2d.h"
#include "../UtilityClasses.h"

class EditorPanelUI;

//Input processor
class EditorInputProcessor
{
protected:
	EditorPanelUI* _editorPanel;
protected:
	virtual void onMouseUp(CustomMouseEvent);
	virtual void onMouseMoved(CustomMouseEvent);
	virtual void onMouseDown(CustomMouseEvent);
	virtual void onMouseScroll(CustomMouseEvent);

	virtual void onKeyDown(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	virtual void onKeyUp(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
public:
	void setEditorPanel(EditorPanelUI* p) { _editorPanel = p; }

	friend class EditorPanelUI;
};

#endif // __EDITOR_INPUT_PROCESSOR_H__
