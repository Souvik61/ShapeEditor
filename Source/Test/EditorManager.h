#ifndef __EDITOR_MANAGER_H__
#define __EDITOR_MANAGER_H__

#include "cocos2d.h"
#include "UtilityClasses.h"


class PointSpaceNode;
class EditorPanelUI;
class OverallManager;
class EditorDraw;
class RigidBodiesManager;
class EditorInputProcessor;
class NewShapesDrawNode;
class CamDelegate;

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
//Send data input processors
//Encapsulates majority logic of editor window
class EditorManager : public ax::Node
{
public:

	std::vector<ax::Vec2*> selectedPoints;
	//Pointer to the nearest point
	//It directly points to the rigidbody model's vertices array
	ax::Vec2* nearestPoint;
	ax::Vec2 prevMousePoint;

	//Represents current mouse selection
	//The points in screen space
	MouseSelection mSel;
	
public:
	EditorPanelUI* editorUI;
	PointSpaceNode* pointsNode;
	OverallManager* oManager;
	RigidBodiesManager* rbManager; //Editor panel interacts with RigidbodyManger about touch coords.
	EditorInputProcessor* _currentInputProcessor;
	EditorDraw* drawer;
	EditorMode _mode;
	EditorMode _prevMode;//Previous mode that active
	NewShapesDrawNode* auxDrawer;//auxilary draw node

	ax::Camera* editorCam;
	ax::Sprite* backgroundSpriteDraw;//This is drawn in RenderTex
	CamDelegate* camDelegate;
	std::string bgSpritePath = "";
public:
	virtual bool init();
	//virtual void onEnter() override;
	virtual void update(float dt) override;
    CREATE_FUNC(EditorManager);

	void updateBackgroundImage();


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

	void setInputProcessor(EditorInputProcessor*);

	//Do not use!
	void changeMode();
	//Change between NONE, EDIT, CREATE
	void changeModeCycle();
	//Change mode by passing in mode enum
	void changeMode(EditorMode mode);
	void changeModeDisabled();
	//This function is useful transitioning from play tab
	//void changeToModeFromPlay();
	//This function is useful transitioning from play tab
	void changeFromPlayMode();

	void changeToPlayMode();
	void onChangeFromPlayMode();

	//Camera related
	void createCamera();
	//Convert world space coord to global screen space coords
	ax::Vec2 convertEditCamToGlobalScreenSpaceCoord(ax::Vec2);
	//Convert global screenspace coord to world coord
	ax::Vec2 convertGlobalScreenSpaceToEditCamCoord(ax::Vec2);

	//Events

	//Mouse Callbacks
	virtual void onMouseUp(ax::EventMouse*);
	virtual void onMouseMoved(ax::EventMouse*);
	virtual void onMouseDown(ax::EventMouse*);
	virtual void onMouseScroll(ax::EventMouse*);

	//Keyboard callbacks
	virtual void onKeyDown(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	virtual void onKeyUp(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

public:
	bool _hasNearClosePt;
	ax::Vec2 nearClosePt; //Nearest point that can close the shape in logic space

public:
	//This vector is visited when RenderTexture is drawn
	std::vector<ax::Node*> rendTexVisitNodes;

};

#endif // __EDITOR_MANAGER_H__