#include "PointArrayDelegate.h"
#include "PointBuffer.h"

USING_NS_AX_MATH;

PointArrayDelegate::PointArrayDelegate() :scale(1), pBuffer(nullptr)
{
	outBuffer.reserve(100);
}

void PointArrayDelegate::applyScale(float sc)
{
	scale = sc;

	//outBuffer.clear();
	//
	//for (size_t i = 0; i < pBuffer->buffer.size(); i++)
	//{
	//	NS_CC::Vec2& p = pBuffer->buffer[i];
	//	outBuffer[i].setPoint(p.x * sc, p.y * sc);
	//}
}

void PointArrayDelegate::applyOffset(float x, float y)
{
	offset.setPoint(x, y);

	//outBuffer.clear();
	//
	//for (size_t i = 0; i < pBuffer->buffer.size(); i++)
	//{
	//	NS_CC::Vec2& p = pBuffer->buffer[i];
	//	outBuffer[i].setPoint(p.x * sc, p.y * sc);
	//}
}

void PointArrayDelegate::applyTransform()
{
	outBuffer.clear();

	for (size_t i = 0; i < pBuffer->buffer.size(); i++)
	{
		ax::Vec2& p = pBuffer->buffer[i];
		outBuffer[i].setPoint((p.x * scale) + offset.x, (p.y * scale) + offset.y);
	}
}

void PointArrayDelegate::refreshMat()
{
	tMatrix.setIdentity();
	
	tMatrix.translate(center.x, center.y, 0);
	//tMatrix.scale(zoom);
	tMatrix.scale(scale);
	tMatrix.translate(-center.x, -center.y, 0);
	tMatrix.translate(offset.x, offset.y, 0);
	//tMatrix.transformVector(Vec4(p.x, p.y, 0, 1), &o);
}

void PointArrayDelegate::applyTransformN(ax::Vec2* v)
{
	v->setPoint((v->x * scale) + offset.x, (v->y * scale) + offset.y);
}

void PointArrayDelegate::applyTransform(ax::Vec2* p)
{
	tMatrix.transformVector(p->x, p->y, 0, 1, (Vec3*)p);
}

void PointArrayDelegate::applyNewTransform(ax::Vec2* p)
{
	Vec3 t;
	newMatrix.transformVector(p->x, p->y, 0, 1, &t);
	p->setPoint(t.x, t.y);
}

void PointArrayDelegate::applyNewInvTransform(ax::Vec2* p)
{
	Vec3 t;
	newMatrixInv.transformVector(p->x, p->y, 0, 1, &t);
	p->setPoint(t.x, t.y);
}

void PointArrayDelegate::applyPartTransform(ax::Vec2* p)
{
	Vec3 t;
	partMatrix.transformVector(p->x, p->y, 0, 1, &t);
	p->setPoint(t.x, t.y);
}

void PointArrayDelegate::applyPartInvTransform(ax::Vec2* p)
{
	Vec3 t;
	partMatrixInv.transformVector(p->x, p->y, 0, 1, &t);
	p->setPoint(t.x, t.y);
}

void PointArrayDelegate::validateNewTransform()
{
	newMatrix.setIdentity();

	//Translate to offset
	newMatrix.translate((-screenOffset.x) + panOffset.x, (-screenOffset.y) + panOffset.y, 0);
	partMatrix.set(newMatrix);
	//Zoom around pan offset
	newMatrix.translate(-panOffset.x, -panOffset.y, 0);
	newMatrix.scale(scale);
	newMatrix.translate(panOffset.x, panOffset.y, 0);

	newMatrixInv.set(newMatrix.getInversed());   //Set inversed of both
	partMatrixInv.set(partMatrix.getInversed()); //Set inversed of both
}
