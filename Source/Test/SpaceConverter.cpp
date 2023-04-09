#include "SpaceConverter.h"

USING_NS_CC;

void SpaceConverter::validateMatrices()
{
	//Validate T1 and Inv matrix
	{
		T1Matrix.setIdentity();

		T1Matrix.translate(screenOffset.x, screenOffset.y, 0);
		T1InvMatrix.set(T1Matrix.getInversed());
	}

	//Validate T and Inv matrix
	{
		TMatrix.setIdentity();

		//Translate to offset
		TMatrix.translate((-screenOffset.x) + panOffset.x, (-screenOffset.y) + panOffset.y, 0);
		//Zoom around pan offset
		TMatrix.translate(-panOffset.x, -panOffset.y, 0);
		TMatrix.scale(scale);
		TMatrix.translate(panOffset.x, panOffset.y, 0);

		TInvMatrix.set(TMatrix.getInversed());
	}
}

void SpaceConverter::applyT(ax::Vec2* p)
{
	Vec3 t;
	TMatrix.transformVector(p->x, p->y, 0, 1, &t);
	p->set(t.x, t.y);
}

void SpaceConverter::applyTInv(ax::Vec2* p)
{
	Vec3 t;
	TInvMatrix.transformVector(p->x, p->y, 0, 1, &t);
	p->set(t.x, t.y);
}

void SpaceConverter::applyT1(ax::Vec2* p)
{
	Vec3 t;
	T1Matrix.transformVector(p->x, p->y, 0, 1, &t);
	p->set(t.x, t.y);
}

void SpaceConverter::applyT1Inv(ax::Vec2* p)
{
	Vec3 t;
	T1InvMatrix.transformVector(p->x, p->y, 0, 1, &t);
	p->set(t.x, t.y);
}
