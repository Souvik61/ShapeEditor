#include "Phys/DebugDrawNode.h"
#include "Utilities.h"
#include "B2_WorldNode.h"

USING_NS_CC;
using namespace rb;

DebugDrawNode::~DebugDrawNode()
{
	_director->getEventDispatcher()->removeEventListener(_afterDraw);
	_director->getEventDispatcher()->removeEventListener(_beforeUpdate);
}

bool DebugDrawNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	_drawNode = DrawNode::create();
	_drawNode->setGlobalZOrder(9999999);
	this->addChild(_drawNode);

	//Add after draw callback to clear drawNode geometry.
	_beforeUpdate = _director->getEventDispatcher()->addCustomEventListener(Director::EVENT_BEFORE_UPDATE, CC_CALLBACK_1(DebugDrawNode::beforeUpdateCallback, this));
	//_afterDraw = _director->getEventDispatcher()->addCustomEventListener(Director::EVENT_AFTER_DRAW, CC_CALLBACK_1(DebugDrawNode::afterDrawCallback, this));
	scheduleUpdate();

	return true;
}

void DebugDrawNode::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	Vec2* arr = new Vec2[vertexCount];
	Utilities::convertAndFillToCCVecArr(vertices, arr, vertexCount);
	_drawNode->drawPoly(arr, vertexCount, true, Utilities::convertToCCColor(color));
	delete[] arr;
}

void DebugDrawNode::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	Vec2* arr = new Vec2[vertexCount];
	Utilities::convertAndFillToCCVecArr(vertices, arr, vertexCount);
	Color4F fCol = Utilities::convertToCCColor(color);
	Color4F bCol(fCol);
	fCol.a = 0.5f;
	_drawNode->drawPolygon(arr, vertexCount, fCol, 0.5, bCol);

	delete[] arr;
}

void DebugDrawNode::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	Vec2 centr = _worldNode->convertToCCVector(center);
	float rad = radius * RB_PTM;
	_drawNode->drawCircle(centr, rad, 0, 16, true, Utilities::convertToCCColor(color));
}

void DebugDrawNode::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	Vec2 centr = _worldNode->convertToCCVector(center);
	float rad = radius * RB_PTM;
	//_drawNode->drawSolidCircle(centr, rad, 0, 16, 1, 1, Utilities::convertToCCColor(color));
	_drawNode->drawCircle(centr, rad, atan2f(axis.y, axis.x), 16, true, Utilities::convertToCCColor(color));
}

void DebugDrawNode::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	_drawNode->drawSegment(_worldNode->convertToCCVector(p1), _worldNode->convertToCCVector(p2), 1, Utilities::convertToCCColor(color));
}

void rb::DebugDrawNode::DrawTransform(const b2Transform& xf)
{
	Vec2 p1 = _worldNode->convertToCCVector(xf.p), p2;
	const float k_axisScale = 0.4f;
	p2 = p1 + k_axisScale * _worldNode->convertToCCVector(xf.q.GetXAxis());
	_drawNode->drawSegment(p1, p2, 1, Color4F::RED);

	p2 = p1 + k_axisScale * _worldNode->convertToCCVector(xf.q.GetYAxis());
	_drawNode->drawSegment(p1, p2, 1, Color4F::GREEN);
}

void rb::DebugDrawNode::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
	_drawNode->drawPoint(_worldNode->convertToCCVector(p), size, Utilities::convertToCCColor(color));
}

void rb::DebugDrawNode::afterDrawCallback(cocos2d::EventCustom*)
{
	//_drawNode->clear();
}

void rb::DebugDrawNode::beforeUpdateCallback(cocos2d::EventCustom*)
{
	_drawNode->clear();
}


rb::DebugDrawNode* rb::DebugDrawNode::create()
{
	DebugDrawNode* pRet = new(std::nothrow) DebugDrawNode();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}
