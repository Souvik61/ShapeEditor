#ifndef __EDITOR_SCREEN_INTERFACE_H__
#define __EDITOR_SCREEN_INTERFACE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Test/UtilityClasses.h"

//Editor screen interface(system)
//A simple class that stores input related info
//Get user inputs
class EditorScreenInterface : public ax::Node
{
	ax::EventListenerMouse* _listenerMouse;
public:
	//Mouse Callbacks
	std::function<void(ax::EventMouse* event)> eOnMouseDown;
	std::function<void(ax::EventMouse* event)> eOnMouseUp;
	std::function<void(ax::EventMouse* event)> eOnMouseMove;
	std::function<void(ax::EventMouse* event)> eOnMouseScroll;

	EditorScreenInterface();
	~EditorScreenInterface();
	CREATE_FUNC(EditorScreenInterface);
	bool init() override;

	void pauseInput();
	void unpauseInput();

	//Some helper methods
	bool isRMBPressed() { return _isRMB; }
	bool isLMBPressed() { return _isLMB; }

public:
	//Mouse events
	void onMouseUp(ax::EventMouse*);
	void onMouseMove(ax::EventMouse*);
	void onMouseDown(ax::EventMouse*);
	void onMouseScroll(ax::EventMouse*);

private:
	bool _isRMB;
	bool _isLMB;

};

#endif // __EDITOR_SCREEN_INTERFACE_H__
