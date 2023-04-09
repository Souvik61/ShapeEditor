#ifndef __RB_UTILITIES_H__
#define __RB_UTILITIES_H__

#include "RbMacros.h"
#include "axmol.h"
#include "box2d/include/box2d/b2_draw.h"

struct b2Color;
struct b2Vec2;
class b2Body;

namespace rb {

    class Utilities
    {
    public:

        static inline ax::Color4F rb::Utilities::convertToCCColor(b2Color col)
        {
            return ax::Color4F(col.r, col.g, col.b, col.a);
        }

        static float convertToCCFloat(float in) { return in * RB_PTM; };
        static float convertToB2Float(float in) { return in / RB_PTM; };
        //static cocos2d::Vec2 convertToCCVec2(float, b2Vec2);

        static inline ax::Vec2 rb::Utilities::convertToCCVec2(b2Vec2 vec)
        {
            return ax::Vec2(vec.x * RB_PTM, vec.y * RB_PTM);
        }

        static inline b2Vec2 rb::Utilities::convertToB2Vec2(ax::Vec2 vec)
        {
            return b2Vec2(vec.x / RB_PTM, vec.y / RB_PTM);
        }

        static inline ax::Vec2 rb::Utilities::convertToCCVec2PTM(float ptm, b2Vec2 vec)
        {
            return ax::Vec2(vec.x * ptm, vec.y * ptm);
        }

        static inline b2Vec2 rb::Utilities::convertToB2Vec2PTM(float ptm, ax::Vec2 vec)
        {
            return b2Vec2(vec.x / ptm, vec.y / ptm);
        }

        //static cocos2d::Vec2* convertToCCVecArr(const b2Vec2*,int size,float ptm_ratio);
        //static b2Vec2* convertToB2VecArr(cocos2d::Vec2* inArray, int size, float ptm_ratio);

        //Takes a b2Vec2 array as input and convert each b2vec2 to CCVec2 and fills the out array
        //both arrays must have same size
        static void convertAndFillToCCVecArr(const b2Vec2 in[], ax::Vec2 out[], int size);

        //Takes a CCVec2 array as input and convert each CCVec2 to b2Vec2 and fills the out array
        //both arrays must have same size
        static void convertAndFillToB2VecArr(const ax::Vec2 in[], b2Vec2 out[], int size);

        //Unknown function

    };
}

#endif //__RB_UTILITIES_H__
