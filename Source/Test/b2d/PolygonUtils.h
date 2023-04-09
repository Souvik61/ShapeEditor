#ifndef __POLYGON_UTILS_H__
#define __POLYGON_UTILS_H__

#include "cocos2d.h"

class PolygonUtils {
public:
    static float getPolygonSignedArea(ax::Vec2 points[], int size);

    static float getPolygonArea(ax::Vec2 points[],int s) {
        return abs(getPolygonSignedArea(points, s));
    }

    static bool isPolygonCCW(ax::Vec2 points[],int s) {
        return getPolygonSignedArea(points, s) > 0;
    }

};

#endif