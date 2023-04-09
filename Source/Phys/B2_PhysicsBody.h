#ifndef __B2_PHYSICSBODY_H__
#define __B2_PHYSICSBODY_H__

#include "cocos2d.h"
#include "Phys/RbMacros.h"
#include "box2d/include/box2d/box2d.h"
#include "Phys/B2_WorldNode.h"
#include "box2d/include/box2d/b2_body.h"

USING_NS_CC;

    struct b2Vec2;
    class b2Body;
    class b2World;
    struct b2BodyDef;
    struct b2FixtureDef;
    class b2Shape;
    class b2Fixture;
    enum b2BodyType;
    struct b2Filter;

    namespace rb {

        class B2WorldNode;

        /// <summary>
        /// Physics Body component.
        /// You do not create objects of this class manually instead use B2WorldNode::createPhysicsBody()
        /// Component name is:"rb_pb",Incase of searching from component container.
        /// </summary>
        class B2PhysicsBody : public cocos2d::Component
        {
        private:
            B2WorldNode* _b2World;
            void updatePos();
            void updateTransform();
        public:
            b2Body* _body;
        public:
            ~B2PhysicsBody();

            virtual bool init(b2BodyDef bodyDef);
            virtual bool init(b2Body*);
            virtual bool init(b2Body*, B2WorldNode*);
            virtual void onAdd();
            virtual void update(float) override;

            //Getters and Setters
            B2WorldNode* getWorldNode() { return _b2World; };
            void setWorldNode(B2WorldNode* world) { _b2World = world; };
            b2Body* getBox2dBody() { return _body; };

            //set body transform in cocos2d coordinates
            void setTransform(const Vec2& position,float angle);

            //Use cocos2d coords.This method will ignore collisions
            void setPosition(cocos2d::Vec2 position);
            //Faster than Vec2 version
            void setPosition(float x, float y);
            inline float getPositionX() { return _body->GetPosition().x * RB_PTM; };
            inline float getPositionY() { return _body->GetPosition().y * RB_PTM; };
            inline cocos2d::Vec2 getPosition() { return Vec2(getPositionX(), getPositionY()); }
            void setBodyType(b2BodyType type);
            void setLinearVelocity(cocos2d::Vec2 velocity) { _body->SetLinearVelocity(CCTOB2VEC2(velocity)); }
            inline void setAngularVelocity(float vel) { _body->SetAngularVelocity(vel); }

            //getters
            
            //Get velocity in pixel unit 
            cocos2d::Vec2 getLinearVelocity() { return B2TOCCVEC2(_body->GetLinearVelocity()); }
            //Get angular velocity in radians
            float getAngularVelocity() { return _body->GetAngularVelocity(); }

            //Add force
            //Note this uses box2d units for forces but worldPoint is in cocos2d coords
            void applyForce(Vec2 force, Vec2 worldPoint, bool wake);

            //Dumb functions

            //Used for setting bitmasks of all fixtures
            void setFilterDataAll(b2Filter newFilter);

            //Create functions

            //static B2PhysicsBody* create(b2BodyDef bodyDef);
            //static B2PhysicsBody* create(b2Body*);
            static B2PhysicsBody* create(b2Body*, B2WorldNode*);

            //Calls b2createfixture internally
            b2Fixture* createFixture(const b2Shape*, float density);
            b2Fixture* createFixture(b2FixtureDef* fixtureDef);

            //CreateWithShape Helpers

        };
    }
#endif // __B2_PHYSICSBODY_H__