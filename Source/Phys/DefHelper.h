#ifndef __RB_DEFHELPER_H__
#define __RB_DEFHELPER_H__

#include "RbMacros.h"
#include "cocos2d.h"
#include "box2d/include/box2d/box2d.h"
#include "Utilities.h"
#include "Phys/B2_PhysicsBody.h"

USING_NS_AX;

namespace rb {

    class B2PhysicsBody;

    class DefHelper
    {
    public:

        //init body def given the reference
        static void initWithPos(b2BodyDef& def,const cocos2d::Vec2& position);

        //Joint helpers

        /*Create a b2DistantJointDef*/
        static b2DistanceJointDef createDistanceJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, cocos2d::Vec2 anchorA, cocos2d::Vec2 anchorB);
        static b2RevoluteJointDef createRevoluteJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, cocos2d::Vec2 anchor);
        static b2PrismaticJointDef createPrismaticJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, cocos2d::Vec2 anchor, cocos2d::Vec2 axis);
        static b2PulleyJointDef createPulleyJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, cocos2d::Vec2 groundAnchorA, cocos2d::Vec2 groundAnchorB, cocos2d::Vec2 anchorA, cocos2d::Vec2 anchorB, float ratio);
        static b2WheelJointDef createWheelJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, Vec2 worldAnchor, Vec2 worldAxis);

        //static b2FrictionJointDef createFrictionJointDef(float ptm_ratio, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, Vec2 anchor);

        static inline b2FrictionJointDef rb::DefHelper::createFrictionJointDef(B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, Vec2 anch)
        {
            b2FrictionJointDef def;
            def.Initialize(bodyA->getBox2dBody(), bodyB->getBox2dBody(), CcToB2Vec2(anch));
            return def;
        }
    
        //Joint helpers --pass by reference
        
        static void initDistanceJointDef(b2DistanceJointDef& joint, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, const cocos2d::Vec2& anchorA, const cocos2d::Vec2& anchorB);
        
        static void initRevoluteJointDef(b2RevoluteJointDef& joint, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, const cocos2d::Vec2& anchor);
        
        static void initPrismaticJointDef(b2PrismaticJointDef& def, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, const cocos2d::Vec2& anchor, const cocos2d::Vec2& axis);

        static void initPulleyJointDef(b2PulleyJointDef& def, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, const cocos2d::Vec2& groundAnchorA, const cocos2d::Vec2& groundAnchorB, const cocos2d::Vec2& anchorA, const cocos2d::Vec2& anchorB, float ratio);

        static void initWheelJointDef(b2WheelJointDef& def, B2PhysicsBody* bodyA, B2PhysicsBody* bodyB, const Vec2& worldAnchor, const Vec2& worldAxis);

        //Others

        //static void setMassDataDef(b2MassData data,);
    
    };
}

#endif //__RB_DEFHELPER_H__
