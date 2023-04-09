#include "Phys/ShapeHelper.h"
#include "box2d/include/box2d/box2d.h"
#include "Phys/Utilities.h"
#include "Phys/B2_PhysicsBody.h"
#include "SuperPhysHelper.h"
#include "Phys/DefHelper.h"
#include "Phys/B2_WorldNode.h"

USING_NS_AX;
using namespace rb;

B2PhysicsBody* SuperPhysHelper::createBox(B2WorldNode* wN, cocos2d::Size size, cocos2d::PhysicsMaterial mat, cocos2d::Vec2 offset,Vec2 initPos)
{
	b2BodyDef def;
	DefHelper::initWithPos(def, initPos);
	def.type = b2_dynamicBody;

	B2PhysicsBody* bodyComp = wN->createPhysicsBodyComp(def);

	b2PolygonShape sp;
	ShapeHelper::initPolygonShapeSetAsBox(sp, size.width, size.height);

	b2FixtureDef fD;
	fD.shape = &sp;
	fD.density = mat.density;
	fD.friction = mat.friction;
	fD.restitution = mat.restitution;

	bodyComp->createFixture(&fD);

	return bodyComp;
}

B2PhysicsBody* SuperPhysHelper::createCircle(B2WorldNode* wN, float rad, PhysicsMaterial mat, Vec2 offset, Vec2 initPos)
{
	b2BodyDef def;
	DefHelper::initWithPos(def, initPos);
	def.type = b2_dynamicBody;
	B2PhysicsBody* bodyComp = wN->createPhysicsBodyComp(def);
	b2CircleShape sp;
	ShapeHelper::initCircleShapeBy(sp, rad);

	b2FixtureDef fD;
	fD.shape = &sp;
	fD.density = mat.density;
	fD.friction = mat.friction;
	fD.restitution = mat.restitution;
	bodyComp->createFixture(&fD);
	return bodyComp;
}

B2PhysicsBody* SuperPhysHelper::createEdgeBox(B2WorldNode* wN, Size size, PhysicsMaterial mat, Vec2 offset, Vec2 initPos)
{
	b2BodyDef def;
	DefHelper::initWithPos(def, initPos);
	B2PhysicsBody* bodyComp = wN->createPhysicsBodyComp(def);

	ShapeHelper::attachWithEdgeBox(bodyComp, size, mat);
	return bodyComp;
}

B2PhysicsBody* rb::SuperPhysHelper::createPolygon(B2WorldNode* wN, Vec2* pts, int count, PhysicsMaterial mat, Vec2 off, Vec2 initPos)
{
	b2BodyDef def;
	DefHelper::initWithPos(def, initPos);

	def.type = b2_dynamicBody;

	B2PhysicsBody* bodyComp = wN->createPhysicsBodyComp(def);

	b2PolygonShape sp;
	ShapeHelper::initPolygonShapeWithVerts(sp, pts, count);

	b2FixtureDef fD;
	fD.shape = &sp;
	fD.density = mat.density;
	fD.friction = mat.friction;
	fD.restitution = mat.restitution;
	bodyComp->createFixture(&fD);

	return bodyComp;
}
