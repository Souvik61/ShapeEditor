#ifndef __EDITION_INPUT_PROCESSOR_V3_H__
#define __EDITION_INPUT_PROCESSOR_V3_H__

#include "cocos2d.h"
#include "EditorInputProcessor.h"
#include "Test/UtilityClasses.h"

class EditorPanel;

//Edition Input processor version 3
class EditionInputProcessorv3 : public EditorInputProcessor
{
	bool _touchDown;
public:
	std::vector<ax::Vec2*> allPointsBuffer;//This vector is used to store points

	EditionInputProcessorv3();
	ax::Vec2* draggedPoint;

	void processPanning(CustomMouseEvent e);
	void processZooming(CustomMouseEvent e);

private:
	virtual void onMouseUp(CustomMouseEvent);
	virtual void onMouseMoved(CustomMouseEvent);
	virtual void onMouseDown(CustomMouseEvent);
	virtual void onMouseScroll(CustomMouseEvent e) override;
	virtual void onMouseDragged(CustomMouseEvent);

	//Keyboard callbacks

	void onKeyUp(ax::EventKeyboard::KeyCode, ax::Event*) override;
	void onKeyDown(ax::EventKeyboard::KeyCode, ax::Event*) override;

	//Utility methods
};

#endif // __NEW_EDITION_INPUT_PROCESSOR_H__
