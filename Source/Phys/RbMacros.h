#ifndef __RB_MACROS_H__
#define __RB_MACROS_H__

//Set global pixel to meter ratio here
#define RB_PTM 100

//Conversion functions

//Convert b2Vec2 to cocos2d::Vec2 with ptm ratio
#define B2TOCCVEC2(v) cocos2d::Vec2(v.x*RB_PTM,v.y*RB_PTM)

//Convert cocos2d::Vec2 to b2Vec2 with ptm ratio
#define CCTOB2VEC2(v) b2Vec2(v.x/RB_PTM,v.y/RB_PTM)

struct b2Vec2;
namespace ax { class Vec2; }

ax::Vec2 b2ToCcVec2(const b2Vec2& v);

b2Vec2 CcToB2Vec2(const ax::Vec2& v);


#endif //__RB_MACROS_H__
