#include "BackGrid.h"

USING_NS_CC;

bool BackGrid::init()
{
	gridDraw = DrawNode::create();
	addChild(gridDraw);

	return true;
}

void BackGrid::validateGrid()
{
	gridDraw->clear();

	float xOff = 0;
	float yOff = 0;

	int rows = gridSize.width / cellSize.width;
	int cols = gridSize.height / cellSize.height;

	for (size_t i = 0; i < cols; i++)
	{
		for (size_t j = 0; j < rows; j++)
		{
			gridDraw->drawSolidRect(Vec2(xOff, yOff), Vec2(xOff + cellSize.width, yOff + cellSize.height), getColorForCell(i + j));

			xOff += cellSize.width;
		}
		xOff = 0;
		yOff += cellSize.height;
	}

}

Color4F BackGrid::getColorForCell(int indx)
{
	if (indx % 2 == 0)
		return Color4F(0.91f, 0.91f, 0.91f, 1);
	else
		return Color4F::WHITE;
}
