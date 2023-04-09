#include "Phys/ShapeHelper.h"
#include "box2d/include/box2d/box2d.h"
#include "Phys/Utilities.h"
#include "Phys/B2_PhysicsBody.h"

USING_NS_CC;
using namespace rb;

void ShapeHelper::attachWithEdgeBox(B2PhysicsBody* body, Vec2 size)
{
	b2EdgeShape shape;
	b2Vec2 vec1;
	b2Vec2 vec2;
	// Floor
	vec1.x = Utilities::convertToB2Float(-size.x / 2);
	vec1.y = Utilities::convertToB2Float(-size.y / 2);

	vec2.x = Utilities::convertToB2Float(size.x / 2);
	vec2.y = Utilities::convertToB2Float(-size.y / 2);

	shape.SetTwoSided(vec1, vec2);
	body->createFixture(&shape, 0);

	// Left wall
	vec2.x = Utilities::convertToB2Float(-size.x / 2);
	vec2.y = Utilities::convertToB2Float(size.y / 2);

	shape.SetTwoSided(vec1, vec2);
	body->createFixture(&shape, 0.0f);

	// Right wall
	vec1.x = Utilities::convertToB2Float(size.x / 2);
	vec1.y = Utilities::convertToB2Float(-size.y / 2);

	vec2.x = Utilities::convertToB2Float(size.x / 2);
	vec2.y = Utilities::convertToB2Float(size.y / 2);

	shape.SetTwoSided(vec1, vec2);
	body->createFixture(&shape, 0.0f);

	// Roof
	vec1.x = Utilities::convertToB2Float(-size.x / 2);
	vec1.y = Utilities::convertToB2Float(size.y / 2);
	shape.SetTwoSided(vec1, vec2);
	body->createFixture(&shape, 0.0f);
}

void ShapeHelper::attachWithEdgeBox(B2PhysicsBody* body, cocos2d::Vec2 size, cocos2d::PhysicsMaterial mat)
{
	b2EdgeShape shape;
	b2Vec2 vec1;
	b2Vec2 vec2;
	b2FixtureDef fD;

	fD.density = mat.density;
	fD.friction = mat.friction;
	fD.restitution = mat.restitution;
	// Floor
	vec1.x = Utilities::convertToB2Float(-size.x / 2);
	vec1.y = Utilities::convertToB2Float(-size.y / 2);
	vec2.x = Utilities::convertToB2Float(size.x / 2);
	vec2.y = Utilities::convertToB2Float(-size.y / 2);

	shape.SetTwoSided(vec1, vec2);
	fD.shape = &shape;
	body->createFixture(&fD);

	// Left wall
	vec2.x = Utilities::convertToB2Float(-size.x / 2);
	vec2.y = Utilities::convertToB2Float(size.y / 2);

	shape.SetTwoSided(vec1, vec2);
	body->createFixture(&fD);

	// Right wall
	vec1.x = Utilities::convertToB2Float(size.x / 2);
	vec1.y = Utilities::convertToB2Float(-size.y / 2);

	vec2.x = Utilities::convertToB2Float(size.x / 2);
	vec2.y = Utilities::convertToB2Float(size.y / 2);

	shape.SetTwoSided(vec1, vec2);
	body->createFixture(&fD);

	// Roof
	vec1.x = Utilities::convertToB2Float(-size.x / 2);
	vec1.y = Utilities::convertToB2Float(size.y / 2);
	shape.SetTwoSided(vec1, vec2);
	body->createFixture(&fD);
}

void ShapeHelper::attachWithEdgeChain(B2PhysicsBody* body, cocos2d::Vec2* points, int count)
{
	b2EdgeShape shape;
	b2Vec2 vec1;
	b2Vec2 vec2;
	for (size_t i = 0; i < count - 1; i++)
	{
		auto pt = points[i];
		auto pt1 = points[i+1];
		// An segment
		vec1.x = Utilities::convertToB2Float(pt.x);
		vec1.y = Utilities::convertToB2Float(pt.y);

		vec2.x = Utilities::convertToB2Float(pt1.x);
		vec2.y = Utilities::convertToB2Float(pt1.y);

		shape.SetTwoSided(vec1, vec2);
		body->createFixture(&shape, 0.0f);
	}

}

b2PolygonShape rb::ShapeHelper::createBoxShape(cocos2d::Size size)
{
	b2PolygonShape shape;
	shape.SetAsBox(size.width / (2 * RB_PTM), size.height / (2 * RB_PTM));
	return shape;
}

b2CircleShape rb::ShapeHelper::createCircleShape(float radius)
{
	b2CircleShape shape;
	shape.m_radius = radius / RB_PTM;
	return shape;
}

b2PolygonShape rb::ShapeHelper::createPolygonShape(cocos2d::Vec2* points, int count)
{
	b2PolygonShape shape;

	b2Vec2 *arr = new b2Vec2[count];
	Utilities::convertAndFillToB2VecArr(points, arr, count);

	shape.Set(arr, count);
	delete[] arr;

	return shape;
}

b2EdgeShape ShapeHelper::createSegmentShape(const Vec2& pointA, const Vec2& pointB)
{
	b2EdgeShape shape;
	shape.SetTwoSided(CCTOB2VEC2(pointA), CCTOB2VEC2(pointB));
	return shape;
}

//----------------------------------
//Initialise by reference functions
//----------------------------------

void ShapeHelper::initCircleShapeBy(b2CircleShape& shape, float radius)
{
	shape.m_radius = radius / RB_PTM;
}

void ShapeHelper::initPolygonShapeWithBox(b2PolygonShape& shape, float hx, float hy, const Vec2& c, float ang)
{
	shape.SetAsBox(hx / RB_PTM, hy / RB_PTM, CCTOB2VEC2(c), ang);
}

void ShapeHelper::initPolygonShapeWithBox(b2PolygonShape& shape, float hx, float hy)
{
	shape.SetAsBox(hx / RB_PTM, hy / RB_PTM);
}

void ShapeHelper::initPolygonShapeSetAsBox(b2PolygonShape& shape, float hx, float hy)
{
	shape.SetAsBox(hx / RB_PTM, hy / RB_PTM);
}

void ShapeHelper::initPolygonShapeSetAsBox(b2PolygonShape& shape, float hx, float hy, const Vec2& c, float ang)
{
	shape.SetAsBox(hx / RB_PTM, hy / RB_PTM, CCTOB2VEC2(c), ang);
}

void ShapeHelper::initPolygonShapeWithVerts(b2PolygonShape& shape, cocos2d::Vec2* points, int count)
{
	b2Vec2* arr = new b2Vec2[count];
	Utilities::convertAndFillToB2VecArr(points, arr, count);
	shape.Set(arr, count);
	delete[] arr;
}

void ShapeHelper::initEdgeShapeSetTwoSided(b2EdgeShape& shape, const Vec2& v1, const Vec2& v2)
{
	shape.SetTwoSided(CCTOB2VEC2(v1), CCTOB2VEC2(v2));
}

//b2ChainShape rb::ShapeHelper::createEdgePolygonShape2(float ptm_ratio, cocos2d::Vec2* points, int count)
//{
//	b2ChainShape shape;
//	auto s = Utilities::convertToB2VecArr(points, count, ptm_ratio);
//	shape.CreateChain(Utilities::convertToB2VecArr(points, count, ptm_ratio), count);
//	return shape;
//}
