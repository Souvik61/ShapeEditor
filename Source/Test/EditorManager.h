#ifndef __EDITOR_MANAGER_H__
#define __EDITOR_MANAGER_H__

#include "cocos2d.h"
#include "UtilityClasses.h"


class PointSpaceNode;
class EditorPanelUI;
class OverallManager;
class EditorDraw;

//Represents a mouse selection
class MouseSelection
{
	bool _isValid = false;
public:
	ax::Vec2 p1;
	ax::Vec2 p2;

	bool isValid()
	{
		return _isValid;
	}

	void setValid(bool valid) { _isValid = valid; }
	//Sets selection size to 0 making it invalid
	void setZero()
	{
		p1.setZero();
		p2.setZero();
	}
};

//Editor Manager
//holds point buffers
class EditorManager : public ax::Node
{
public:

	std::vector<ax::Vec2*> selectedPoints;
	//Pointer to the nearest point
	//It directly points to the rigidbody model's vertices array
	ax::Vec2* nearestPoint;

	//Represents current mouse selection
	//The points in screen space
	MouseSelection mSel;
	
public:
	EditorPanelUI* editorUI;
	PointSpaceNode* pointsNode;
	OverallManager* oManager;
	EditorDraw* drawer;
public:
	virtual bool init();
	//virtual void onEnter() override;
    // implement the "static create()" method manually
    CREATE_FUNC(EditorManager);

	void resetPointSpace();

	PointSpaceNode* getPointsSpace() { return pointsNode; }

	//Given a point in logic space calculate the nearest point in rigidbody
	//set the "nearestPoint" to point to the nearest point in the original array
	//Manipulating this  will also change original point
	void validateNearestPoint(const ax::Vec2& pt);

	bool isSelectedPointsContain(ax::Vec2 p);

	void selectedPointsReplaceBy(ax::Vec2* p);

	//Selects(load into selectedPoints array) points that is in the BB of mouse selection
	void selectPointsInMouseSelection();

	void removeSelectedPoints();

	bool isRemoveEnabled();

	//Set nearest point that can close the shape ,set avail to false if none available 
	void setNearestClosingPt(bool avail, const ax::Vec2&);

	//Events

	void onChangeToPlayMode();
	void onChangeFromPlayMode();

public:
	bool _hasNearClosePt;
	ax::Vec2 nearClosePt; //Nearest point that can close the shape in logic space
};

#endif // __EDITOR_MANAGER_H__