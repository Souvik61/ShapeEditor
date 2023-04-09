#ifndef __POINTARRAY_DELEGATE_H__
#define __POINTARRAY_DELEGATE_H__

#include "cocos2d.h"

class PointBuffer;

//ScreenSpace -> LogicSpace Non-Inv
//LogicSpace -> ScreenSpace Inv
class PointArrayDelegate
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

	PointBuffer* pBuffer;

	std::vector<ax::Vec2> outBuffer;

	ax::Mat4 tMatrix;
	
	ax::Mat4 newMatrix;
	ax::Mat4 partMatrix;
	ax::Mat4 partMatrixInv;
	ax::Mat4 newMatrixInv;
public:
	PointArrayDelegate();

	//Modify these 2 functions
	void applyScale(float);
	void applyOffset(float x, float y);

	void incrScale(float s = 0.1f) { scale += s; }
	void decrScale(float s = 0.1f) { scale -= s; }
	void resetScale() { scale = 1; }

	void addOffset(const ax::Vec2& off) { offset += off; panOffset = offset; }
	void resetOffset() { offset.setZero(); }
	//Call this to apply transform.
	void applyTransform();
	void refreshMat();
	
	//Pass an vector to apply the transformation(deprecated)
	void applyTransformN(ax::Vec2*);
	//(deprecated)
	void applyTransform(ax::Vec2*);

	//Logic Space -> Screen Space
	void applyNewTransform(ax::Vec2*);
	//Screen Space -> Logic Space
	void applyNewInvTransform(ax::Vec2*);

	//Apply Partial Logic Space -> Screen Space
	void applyPartTransform(ax::Vec2*);
	//Apply Partial Screen Space -> Logic Space
	void applyPartInvTransform(ax::Vec2*);

	void validateNewTransform();
};

#endif //__POINTARRAY_DELEGATE_H__