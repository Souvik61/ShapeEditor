#ifndef __SPACE_CONVERTER_H__
#define __SPACE_CONVERTER_H__

#include "cocos2d.h"
#include "UtilityClasses.h"

//Coordinate Spaces convertor
//There are 3 coord spaces:
//i)Logic Space
//i)View Space
//i)Screen Space
class SpaceConverter
{
public:
	float scale = 1, zoom = 1;
	ax::Vec2 offset;
	ax::Vec2 center;
	ax::Vec2 translation;

	//New vars
	ax::Vec2 panOffset;
	ax::Vec2 screenOffset;
	ax::Vec2 newZoom;

public:
	//Matrices

	ax::Mat4 TMatrix;
	ax::Mat4 T1Matrix;
	ax::Mat4 T2Matrix;
	ax::Mat4 TInvMatrix;
	ax::Mat4 T1InvMatrix;
	ax::Mat4 T2InvMatrix;
public:
	void validateMatrices();

	void applyScale(float sc) { scale = sc; };
	void applyOffset(ax::Vec2 off) {  };
	void addOffset(const ax::Vec2& off) { offset += off; panOffset = offset; }

	//Logic Space -> View Space
	void applyT(ax::Vec2*);
	//View Space -> Logic Space
	void applyTInv(ax::Vec2*);

	//Logic Space -> Screen Space
	void applyT1(ax::Vec2*);
	//Screen Space -> Logic Space
	void applyT1Inv(ax::Vec2*);
private:

};

#endif // __SPACE_CONVERTER_H__