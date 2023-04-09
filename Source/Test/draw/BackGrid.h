#ifndef __BACK_GRID_H__
#define __BACK_GRID_H__

#include "cocos2d.h"

class BackGrid : public ax::Node
{
public:
	ax::Size gridSize;
	ax::Size cellSize;
	ax::Vec2 gridOffset;
	ax::DrawNode* gridDraw;
public:
	bool init() override;

	CREATE_FUNC(BackGrid);

	void validateGrid();
	//Get color(gray/white) for odd and even cells
	ax::Color4F getColorForCell(int cell);
};

#endif // __BACK_GRID_H__
