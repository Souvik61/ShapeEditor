#ifndef __RB_DEBUGDRAW_NODE_H__
#define __RB_DEBUGDRAW_NODE_H__

#include "axmol.h"
#include "box2d/include/box2d/box2d.h"

namespace rb {

    class B2WorldNode;

    class DebugDrawNode : public b2Draw, public ax::Node
    {
    private:
        ax::DrawNode* _drawNode;
        B2WorldNode* _worldNode;
    public:
        ~DebugDrawNode();

        virtual bool init() override;

        void setWorld(B2WorldNode* world) { _worldNode = world; };

        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);
        void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
        inline void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
        void DrawTransform(const b2Transform& xf);
        void DrawPoint(const b2Vec2& p, float size, const b2Color& color);

        void afterDrawCallback(ax::EventCustom*);
        void beforeUpdateCallback(ax::EventCustom*);

        //Create methods
        static DebugDrawNode* create();


        // Event for after draw 
        ax::EventListenerCustom* _beforeUpdate;
        ax::EventListenerCustom* _afterDraw;
    };
}

#endif // __RB_DEBUGDRAW_NODE_H__
