#include "Phys/RbMacros.h"
#include "B2_PhysicsBody.h"
#include "box2d/include/box2d/box2d.h"
#include "Phys/B2_WorldNode.h"
#include "Phys/Utilities.h"

USING_NS_CC;
using namespace rb;

void B2PhysicsBody::updatePos()
{
    CCASSERT(_owner != nullptr, "Must have a owner to update its position.");
    _owner->setPosition(_b2World->convertToCCVector(_body->GetPosition()));
}

inline void rb::B2PhysicsBody::updateTransform()
{
    //updatePos();
    _owner->setPosition(_b2World->convertToCCVector(_body->GetPosition()));
    _owner->setRotation(AX_RADIANS_TO_DEGREES(-_body->GetAngle()));
}

B2PhysicsBody::~B2PhysicsBody()
{
    if (_b2World != nullptr)
        _b2World->getPhysicsWorld()->DestroyBody(_body);
}

// not used
bool B2PhysicsBody::init(b2BodyDef bodyDef)
{	
	return true;
}
//not used
bool B2PhysicsBody::init(b2Body* body)
{
    setName("rb_physicsbody");
    _body = body;
    return true;
}
//used
bool B2PhysicsBody::init(b2Body* body,B2WorldNode* world)
{
    setName("rb_pb");
    _body = body;
    _body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this); //Set user pointer
    _b2World = world;
    return true;
}

void rb::B2PhysicsBody::onAdd()
{
    getOwner()->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    updateTransform();
}

void B2PhysicsBody::update(float)
{
    // updatePos();
    updateTransform();
}

void rb::B2PhysicsBody::setTransform(const Vec2& pos, float angle)
{
    _body->SetTransform(CCTOB2VEC2(pos), angle);
    updateTransform();
}

//Use cocos2d coords.This method will ignore collisions
void B2PhysicsBody::setPosition(Vec2 position)
{
    _body->SetTransform(_b2World->convertToB2Vector(position), _body->GetAngle());
    updatePos();
}
//Faster than setPosition(Vec2)
void rb::B2PhysicsBody::setPosition(float x, float y)
{
    _body->SetTransform(b2Vec2(x / RB_PTM, y / RB_PTM), _body->GetAngle());
    updatePos();
}

//inline cocos2d::Vec2 rb::B2PhysicsBody::getPosition()
//{
//    b2Vec2 a = _body->GetPosition();
//    return cocos2d::Vec2(a.x * _b2World->PTM_RATIO, a.y * _b2World->PTM_RATIO);
//}

void rb::B2PhysicsBody::setBodyType(b2BodyType type)
{
    _body->SetType(type);
}

//void rb::B2PhysicsBody::setLinearVelocity(cocos2d::Vec2 vel)
//{
//    _body->SetLinearVelocity(Utilities::convertToB2Vec2(_b2World->PTM_RATIO, vel));
//}

void rb::B2PhysicsBody::applyForce(Vec2 force, Vec2 wP, bool wake)
{
    _body->ApplyForce(Utilities::convertToB2Vec2PTM(1, force), CCTOB2VEC2(wP), wake);
}

void rb::B2PhysicsBody::setFilterDataAll(b2Filter newFilter)
{
    for (b2Fixture* f = _body->GetFixtureList(); f; f = f->GetNext())
    {
        f->SetFilterData(newFilter);
    }
}

B2PhysicsBody* B2PhysicsBody::create(b2Body* body, B2WorldNode* world)
{
    B2PhysicsBody* pRet = new(std::nothrow) B2PhysicsBody();
    if (pRet && pRet->init(body, world))
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

b2Fixture* rb::B2PhysicsBody::createFixture(const b2Shape* shape, float density)
{
    return _body->CreateFixture(shape, density);
}

b2Fixture* rb::B2PhysicsBody::createFixture(b2FixtureDef* fixtureDef)
{
    return _body->CreateFixture(fixtureDef);
}
