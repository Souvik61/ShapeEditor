#ifndef __CREATION_INPUT_PROCESSOR_H__
#define __CREATION_INPUT_PROCESSOR_H__

#include "cocos2d.h"
#include "EditorInputProcessor.h"

USING_NS_CC;

class EditorPanel;

//Creation Input processor
class CreationInputProcessor : public EditorInputProcessor
{
	virtual void onMouseUp(CustomMouseEvent) override;
	virtual void onMouseMoved(CustomMouseEvent) override;
	virtual void onMouseDown(CustomMouseEvent) override;
	virtual void onMouseScroll(CustomMouseEvent) override;

	void processPanning(CustomMouseEvent);
	void processZooming(CustomMouseEvent);

};

#endif // __CREATION_INPUT_PROCESSOR_H__
