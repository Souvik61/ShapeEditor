#ifndef __RB_SUPER_PHYSHELPER_H__
#define __RB_SUPER_PHYSHELPER_H__

#include "cocos2d.h"

USING_NS_CC;

namespace rb {

    class B2PhysicsBody;

    /*Helper class to easily create basic physics components*/
    class SuperPhysHelper
    {
    public:
        static B2PhysicsBody* createBox(B2WorldNode* worldNode, Size size, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT, Vec2 offset = Vec2::ZERO, Vec2 initialPos = Vec2::ZERO);
        static B2PhysicsBody* createCircle(B2WorldNode* worldNode, float radius, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT, Vec2 offset = Vec2::ZERO, Vec2 initialPos = Vec2::ZERO);
        static B2PhysicsBody* createEdgeBox(B2WorldNode* worldNode, Size size, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT, Vec2 offset = Vec2::ZERO, Vec2 initialPos = Vec2::ZERO);
        static B2PhysicsBody* createPolygon(B2WorldNode* worldNode, Vec2* points, int pointCount, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT, Vec2 offset = Vec2::ZERO, Vec2 initialPos = Vec2::ZERO);

    };
}

#endif //__RB_SUPER_PHYSHELPER_H__
