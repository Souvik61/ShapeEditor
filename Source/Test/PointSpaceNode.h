#ifndef __POINTSPACE_NODE_H__
#define __POINTSPACE_NODE_H__

#include "cocos2d.h"

//No longer used
class PointSpaceNode :public cocos2d::Node
{
public:
	cocos2d::Vec2 offset;
	float zoomScale = 0.0f;
public:
	bool init();
	CREATE_FUNC(PointSpaceNode);

};

#endif //__POINTSPACE_NODE_H__