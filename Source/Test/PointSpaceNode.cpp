#include "PointSpaceNode.h"

USING_NS_CC;

bool PointSpaceNode::init()
{
	auto dN = DrawNode::create();
	addChild(dN);
	dN->drawDot(Vec2::ZERO, 5, Color4F::BLUE);

	return true;
}
