#ifndef __VIEW_INPUT_PROCESSOR_H__
#define __VIEW_INPUT_PROCESSOR_H__

#include "cocos2d.h"
#include "EditorInputProcessor.h"

class EditorPanel;

//View Input processor
class ViewInputProcessor : public EditorInputProcessor
{
	virtual void onMouseUp(CustomMouseEvent) override;
	virtual void onMouseMoved(CustomMouseEvent) override;
	virtual void onMouseDown(CustomMouseEvent) override;
	virtual void onMouseScroll(CustomMouseEvent) override;

	void processPanning(CustomMouseEvent);
	void processZooming(CustomMouseEvent);

};
#endif // __VIEW_INPUT_PROCESSOR_H__