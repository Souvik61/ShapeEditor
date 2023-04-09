#include "RbMacros.h"
#include "math/Vec2.h"
#include "box2d/include/box2d/b2_math.h"

ax::Vec2 b2ToCcVec2(const b2Vec2& v) { return ax::Vec2(v.x * RB_PTM, v.y * RB_PTM); }

b2Vec2 CcToB2Vec2(const ax::Vec2& v) { return b2Vec2(v.x / RB_PTM, v.y / RB_PTM); }