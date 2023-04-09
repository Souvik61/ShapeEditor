#ifndef __POINT_BUFFER_H__
#define __POINT_BUFFER_H__

#include "cocos2d.h"

class PointBuffer
{
public:
	//The original point locations 
	std::vector<ax::Vec2> buffer;
public:
	PointBuffer();
};

#endif //__POINT_BUFFER_H__