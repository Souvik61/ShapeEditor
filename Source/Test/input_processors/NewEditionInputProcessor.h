#ifndef __NEW_EDITION_INPUT_PROCESSOR_H__
#define __NEW_EDITION_INPUT_PROCESSOR_H__

#include "cocos2d.h"
#include "EditorInputProcessor.h"
#include "Test/UtilityClasses.h"

USING_NS_CC;

class EditorPanel;

//New Edition Input processor
class NewEditionInputProcessor : public EditorInputProcessor
{
	bool _touchDown;
public:
	std::vector<Vec2*> allPointsBuffer;//This vector is used to store points

	NewEditionInputProcessor();
	Vec2** draggedPoint;
	//Vec2* nearestPoint;

	void processPanning(CustomMouseEvent e);
	void processZooming(CustomMouseEvent e);

private:
	virtual void onMouseUp(CustomMouseEvent);
	virtual void onMouseMoved(CustomMouseEvent);
	virtual void onMouseDown(CustomMouseEvent);
	virtual void onMouseScroll(CustomMouseEvent e) override;
	virtual void onMouseDragged(CustomMouseEvent);


	//Utility methods

	void loadSelectedPoints();
	//Calculate nearest point on shape with given mouse position(Given point must be in logic space)
	void calculateNearestPointN(Vec2 v);
	void calculateNearestPoint(Vec2 v);
	void loadAllPoints();
	void unloadPoints() { allPointsBuffer.clear(); }
};

#endif // __NEW_EDITION_INPUT_PROCESSOR_H__
