#include "Phys/DefHelper.h"
#include "Phys/Utilities.h"
#include "box2d/include/box2d/box2d.h"
#include "Phys/B2_PhysicsBody.h"

USING_NS_CC;
using namespace rb;

void DefHelper::initWithPos(b2BodyDef& def, const cocos2d::Vec2& pos)
{
	def.position = CcToB2Vec2(pos);
}

b2DistanceJointDef DefHelper::createDistanceJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, Vec2 anchorA, Vec2 anchorB)
{
	b2DistanceJointDef def;
	def.Initialize(bodyA->_body, bodyB->_body, CcToB2Vec2(anchorA), CcToB2Vec2(anchorB));
	return def;
}

b2RevoluteJointDef DefHelper::createRevoluteJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, cocos2d::Vec2 anchor)
{
	b2RevoluteJointDef jointDef;
	jointDef.Initialize(bodyA->_body, bodyB->_body, CcToB2Vec2(anchor));
	return jointDef;
}

b2PrismaticJointDef DefHelper::createPrismaticJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, cocos2d::Vec2 anchor, Vec2 axis)
{
	b2PrismaticJointDef def;
	def.Initialize(bodyA->_body, bodyB->_body, CcToB2Vec2(anchor), Utilities::convertToB2Vec2PTM(1, axis));//axis is a unit vector so the conversion factor is 1.
	return def;
}

b2PulleyJointDef DefHelper::createPulleyJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, cocos2d::Vec2 gancA, cocos2d::Vec2 gancB, Vec2 ancA, Vec2 ancB, float rat)
{
	b2PulleyJointDef def;
	def.Initialize(bodyA->_body, bodyB->_body, CCTOB2VEC2(gancA), CCTOB2VEC2(gancB), CCTOB2VEC2(ancA), CCTOB2VEC2(ancB), rat);
	return def;
}

b2WheelJointDef DefHelper::createWheelJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, Vec2 wAnch, Vec2 wAxis)
{
	b2WheelJointDef def;
	def.Initialize(bodyA->getBox2dBody(), bodyB->getBox2dBody(), CCTOB2VEC2(wAnch), Utilities::convertToB2Vec2PTM(1, wAxis));//Conversion factor 1 for axis
	return def;
}

//Pass by reference functions

void DefHelper::initDistanceJointDef(b2DistanceJointDef& joint, B2PhysicsBody* bA, B2PhysicsBody* bB, const cocos2d::Vec2& ancA, const cocos2d::Vec2& ancB)
{
	joint.Initialize(bA->_body, bB->_body, CCTOB2VEC2(ancA), CCTOB2VEC2(ancB));
}

void DefHelper::initRevoluteJointDef(b2RevoluteJointDef& j, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB,const cocos2d::Vec2& anc)
{
	j.Initialize(bodyA->_body, bodyB->_body, CCTOB2VEC2(anc));
}

void DefHelper::initPrismaticJointDef(b2PrismaticJointDef& def, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, const cocos2d::Vec2& anc, const cocos2d::Vec2& axis)
{
	def.Initialize(bodyA->_body, bodyB->_body, CCTOB2VEC2(anc), Utilities::convertToB2Vec2PTM(1, axis));
}

void DefHelper::initPulleyJointDef(b2PulleyJointDef& def, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, const cocos2d::Vec2& gancA, const cocos2d::Vec2& gancB, const cocos2d::Vec2& ancA, const cocos2d::Vec2& ancB, float rat)
{
	def.Initialize(bodyA->_body, bodyB->_body, CCTOB2VEC2(gancA), CCTOB2VEC2(gancB), CCTOB2VEC2(ancA), CCTOB2VEC2(ancB), rat);
}

void rb::DefHelper::initWheelJointDef(b2WheelJointDef& def, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, const Vec2& wAnch, const Vec2& wAxis)
{
	def.Initialize(bodyA->_body, bodyB->_body, CCTOB2VEC2(wAnch), Utilities::convertToB2Vec2PTM(1, wAxis));//Conversion factor 1 for axis
}
