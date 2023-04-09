#include "EditorScreenInterface.h"

USING_NS_CC;

//--------------------------------
//Editor Screen Interface
//--------------------------------

EditorScreenInterface::EditorScreenInterface() :
	_listenerMouse(nullptr), _isRMB(false)
{
}

EditorScreenInterface::~EditorScreenInterface()
{
	_eventDispatcher->removeEventListener(_listenerMouse);
}

bool EditorScreenInterface::init()
{

	_listenerMouse = EventListenerMouse::create();
	_listenerMouse->onMouseDown = CC_CALLBACK_1(EditorScreenInterface::onMouseDown,this);
	_listenerMouse->onMouseMove = CC_CALLBACK_1(EditorScreenInterface::onMouseMove,this);
	_listenerMouse->onMouseUp = CC_CALLBACK_1(EditorScreenInterface::onMouseUp,this);
	_listenerMouse->onMouseScroll = CC_CALLBACK_1(EditorScreenInterface::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerMouse, this);


	return true;
}

void EditorScreenInterface::pauseInput()
{
	_listenerMouse->setEnabled(false);
}

void EditorScreenInterface::unpauseInput()
{
	_listenerMouse->setEnabled(true);
}

void EditorScreenInterface::onMouseUp(EventMouse* e)
{
	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		_isRMB = false;
	}
	else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		_isLMB = false;
	}

	if (eOnMouseUp)
		eOnMouseUp(e);
}

void EditorScreenInterface::onMouseMove(EventMouse* e)
{
	if (eOnMouseMove)
		eOnMouseMove(e);
}

void EditorScreenInterface::onMouseDown(EventMouse* e)
{
	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		_isRMB = true;
	}
	else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		_isLMB = true;
	}

	if (eOnMouseDown)
		eOnMouseDown(e);
}

void EditorScreenInterface::onMouseScroll(EventMouse* e)
{
	if (eOnMouseScroll)
		eOnMouseScroll(e);
}


