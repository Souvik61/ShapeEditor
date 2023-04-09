#ifndef __TEST_INPUT_PROCESSOR_H__
#define __TEST_INPUT_PROCESSOR_H__

#include "cocos2d.h"
#include "EditorInputProcessor.h"

class EditorPanel;
class B2DManager;

//Test Input processor
//Input processor during play mode
class TestInputProcessor : public EditorInputProcessor
{
public:
	B2DManager* b2dManager;
	TestInputProcessor();
	//Init with box2d manager
	void init(B2DManager* bMan) { b2dManager = bMan; };
public:
	virtual void onMouseUp(CustomMouseEvent);
	virtual void onMouseMoved(CustomMouseEvent);
	virtual void onMouseDown(CustomMouseEvent);
	virtual void onMouseDragged(CustomMouseEvent);
	virtual void onMouseScroll(CustomMouseEvent);

	//Utility methods

	void processPanning(CustomMouseEvent);
	void processZooming(CustomMouseEvent);

};

#endif // __TEST_INPUT_PROCESSOR_H__
