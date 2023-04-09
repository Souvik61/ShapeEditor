#include "Utilities.h"
#include "cocos2d.h"
#include "box2d/include/box2d/box2d.h"

using namespace rb;

//cocos2d::Vec2* rb::Utilities::convertToCCVecArr(const b2Vec2* bVec, int size, float ptm_ratio)
//{
//	cocos2d::Vec2* vec = new cocos2d::Vec2[size]();
//
//	for (size_t i = 0; i < size; i++)
//	{
//		vec[i] = cocos2d::Vec2(bVec[i].x * ptm_ratio, bVec[i].y * ptm_ratio);
//	}
//	return vec;
//}
//
//b2Vec2* rb::Utilities::convertToB2VecArr(cocos2d::Vec2* inArray, int size, float ptm_ratio)
//{
//	b2Vec2* vec = new b2Vec2[size];
//
//	for (size_t i = 0; i < size; i++)
//	{
//		vec[i].Set(inArray[i].x / ptm_ratio, inArray[i].y / ptm_ratio);
//	}
//	return vec;
//}

void rb::Utilities::convertAndFillToCCVecArr(const b2Vec2 in[], cocos2d::Vec2 out[], int size)
{
	for (size_t i = 0; i < size; i++) {
		out[i].setPoint(in[i].x * RB_PTM, in[i].y * RB_PTM);
	}
}

void rb::Utilities::convertAndFillToB2VecArr(const cocos2d::Vec2 in[], b2Vec2 out[], int size)
{
	for (size_t i = 0; i < size; i++) {
		out[i].Set(in[i].x / RB_PTM, in[i].y / RB_PTM);
	}
}
