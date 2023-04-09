#ifndef __RB_SHAPEHELPER_H__
#define __RB_SHAPEHELPER_H__

#include "cocos2d.h"

class b2PolygonShape;
class b2ChainShape;
class b2CircleShape;
class b2EdgeShape;

USING_NS_AX;

namespace rb {

    class B2PhysicsBody;

    class ShapeHelper
    {
    public:
        /*
        *Attach shape to a physics body
        */

        /*
        *For complex shapes
        */
        static void attachWithEdgeBox(B2PhysicsBody* body, cocos2d::Vec2 size);
        static void attachWithEdgeBox(B2PhysicsBody* body, cocos2d::Vec2 size, ax::PhysicsMaterial material);
        static void attachWithEdgeChain(B2PhysicsBody* body, cocos2d::Vec2* points, int count);

        /*
        *For simple shapes
        */
        static b2PolygonShape createBoxShape(ax::Size size);
        static b2CircleShape createCircleShape(float radius);
        static b2PolygonShape createPolygonShape(cocos2d::Vec2* points, int count);
        static b2EdgeShape createSegmentShape(const cocos2d::Vec2& pointA, const cocos2d::Vec2& pointB);
        //static b2ChainShape createEdgePolygonShape2(float ptm_ratio, cocos2d::Vec2* points, int count);

        /*
        *For simple shapes --set by reference
        */

        static void initCircleShapeBy(b2CircleShape& shape, float radius);

        //Box
        
        //Use initPolygonShapeSetAsBox not this!
        static void initPolygonShapeWithBox(b2PolygonShape& shape, float hx, float hy, const Vec2& center, float angle);
        //Use initPolygonShapeSetAsBox not this!
        static void initPolygonShapeWithBox(b2PolygonShape& shape, float hx, float hy);

        static void initPolygonShapeSetAsBox(b2PolygonShape& shape, float hx, float hy);
        static void initPolygonShapeSetAsBox(b2PolygonShape& shape, float hx, float hy, const Vec2& center, float angle);

        static void initPolygonShapeWithVerts(b2PolygonShape& shape, cocos2d::Vec2* points, int count);

        //Edge

        static void initEdgeShapeSetTwoSided(b2EdgeShape& shape, const Vec2& v1, const Vec2& v2);

    };
}

#endif //__RB_SHAPEHELPER_H__
