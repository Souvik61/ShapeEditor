#ifndef __EDITOR_DRAW_H__
#define __EDITOR_DRAW_H__

#include "cocos2d.h"

class EditorManager;

//This class is responsible for drawing from the Editor Manager
//This draws selectedVerts, nearestPoint
class EditorDraw : public ax::Node
{
public:
	bool _pauseDraw;
	ax::DrawNode* _vertDraw;
	ax::DrawNode* _selectionDraw;
	ax::DrawNode* _trDraw;
	EditorManager* editManager;

	//There vertices sprites
	ax::Sprite* v00;
	ax::Sprite* v10;
	ax::Sprite* v01;
public:
	bool init() override;
	void update(float dt) override;
	CREATE_FUNC(EditorDraw);

	void clearDrawNodes();
	void drawModels();
	
	void drawSelectedVerts();
	void drawUnitVectors();
	void drawSelectionBox();
	void positionSprites();

	void pauseDrawing(bool val);

};

#endif // __EDITOR_DRAW_H__
