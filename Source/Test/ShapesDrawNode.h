#ifndef __SHAPES_DRAWNODE_H__
#define __SHAPES_DRAWNODE_H__

#include "cocos2d.h"
#include "UtilityClasses.h"

USING_NS_CC;

class RigidBodyModel;
class EditorPanel;
class RigidBodiesManager;
class EditorPanelUI;

class ShapesDrawNode : public Node {

protected:
	bool _ready;
	DrawNode* _shapeDraw;
	DrawNode* _vertDraw;
	DrawNode* _selectionDraw;
	RigidBodiesManager* _rbManagerRef;
	EditorPanel* _editPanel;
	EditorPanelUI* _editPanelUI;
public:
	Vec2 _nearestPoint;
public:
	virtual bool init() override;
	virtual void update(float) override;
	CREATE_FUNC(ShapesDrawNode);
	void setRbManager(RigidBodiesManager*);
	void setEditorPanel(EditorPanel* p) { _editPanel = p; };
	void setEditorPanel(EditorPanelUI* p) { _editPanelUI = p; };
	
	virtual void drawShapes();
	virtual void drawModels();
	virtual void drawPolygons();
	virtual void drawCircles();
	virtual void drawVerts();
	virtual void drawSelectedVerts();
	virtual void drawSelectionBox();

};

#endif // __SHAPES_DRAWNODE_H__
