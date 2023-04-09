#ifndef __NEW_SHAPES_DRAWNODE_H__
#define __NEW_SHAPES_DRAWNODE_H__


#include "ShapesDrawNode.h"


class RigidBodyModel;
class EditorPanel;
class RigidBodiesManager;
class EditorPanelUI;
class PointArrayDelegate;

class NewShapesDrawNode : public ShapesDrawNode {
	
	bool _pauseDraw = false;
	DrawNode* _trDraw;
public:
	PointArrayDelegate* pDelegate;
public:
	virtual bool init() override;
	virtual void update(float) override;
	CREATE_FUNC(NewShapesDrawNode);
	
	void clearDrawNodes();
	void drawShapes() override;
	void drawModels() override;
	void drawPolygons() override;
	void drawCircles() override;
	void drawVerts() override;
	void drawSelectedVerts() override;
	void drawSelectionBox() override;
	void drawOrigin();

	void pauseDrawing(bool pause) { _pauseDraw = pause; };

};

#endif // __NEW_SHAPES_DRAWNODE_H__
