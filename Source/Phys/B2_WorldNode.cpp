#include "Phys/B2_WorldNode.h"
#include "Phys/B2_PhysicsBody.h"
#include "box2d/include/box2d/box2d.h"
#include "DebugDrawNode.h"

USING_NS_CC;
using namespace rb;

B2WorldNode::B2WorldNode()
{
	//B2WorldNode::PTM_RATIO = 1;
}

B2WorldNode::~B2WorldNode()
{
	custScheduler->unscheduleAllForTarget(this);
	delete _b2World;
}

// on "init" you need to initialize your instance
bool B2WorldNode::init()
{
	_hasStepCallback = false;
	//Create a custom scheduler
	custScheduler = new Scheduler();
	_director->getScheduler()->scheduleUpdate(custScheduler, -1, false);

	//Schedule world update method every 1/60 s
	custScheduler->schedule(CC_SCHEDULE_SELECTOR(B2WorldNode::updateWorld), this, 1 / 60.f, false);
	custScheduler->setTimeScale(1.f);

	return true;
}

void rb::B2WorldNode::setPosition(float x, float y)
{
	//Do nothing
}

void B2WorldNode::updateWorld(float dt)
{
	_b2World->Step(timeStep,velIters,posIters);
	//CCLOG("Update world");
	//_b2World->DrawDebugData();
	_b2World->DebugDraw();

	//Callback for step
	if (_hasStepCallback)
		_stepCallback(dt);
}

void rb::B2WorldNode::pauseWorld(bool pause)
{
	timeStep = (pause) ? 0 : (1 / 60.0f);
}


void rb::B2WorldNode::setDebugDrawNode(DebugDrawNode* draw)
{
	_b2World->SetDebugDraw(draw);
}


//inline b2Vec2 B2WorldNode::convertToB2Vector(cocos2d::Vec2 vec)
//{
//	return b2Vec2(vec.x / PTM_RATIO, vec.y / PTM_RATIO);
//}
//
//inline cocos2d::Vec2 B2WorldNode::convertToCCVector(b2Vec2 vec)
//{
//	return cocos2d::Vec2(vec.x * PTM_RATIO, vec.y * PTM_RATIO);
//}

//Create functions

B2WorldNode* B2WorldNode::create(Vec2 gravity)
{
	B2WorldNode* pRet = new(std::nothrow) B2WorldNode();
	if (pRet && pRet->init())
	{
		pRet->_b2World = new b2World(CCTOB2VEC2(gravity));
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
	return pRet;
}

//-------------------------
//Factory functions
//-------------------------

B2PhysicsBody* rb::B2WorldNode::createPhysicsBodyComp(b2BodyDef bodyDef)
{
	auto body = _b2World->CreateBody(&bodyDef);
	B2PhysicsBody* rbBody = B2PhysicsBody::create(body, this);
	return rbBody;
}

rb::B2PhysicsBody* rb::B2WorldNode::createPhysicsBodyComp(const b2BodyDef* bodyDef)
{
	auto body = _b2World->CreateBody(bodyDef);
	return B2PhysicsBody::create(body, this);
}

b2Joint* rb::B2WorldNode::createJoint(b2JointDef* jDef)
{
	return _b2World->CreateJoint(jDef);
}

