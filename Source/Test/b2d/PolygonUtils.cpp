#include "Test/b2d/Clipper.h"
#include "PolygonUtils.h"

USING_NS_CC;

float PolygonUtils::getPolygonSignedArea(ax::Vec2 points[], int s)
{
    if (s < 3)
        return 0;

    float sum = 0;
    for (int i = 0; i < s; i++) {
        ax::Vec2 p1 = points[i];
        ax::Vec2 p2 = i != s - 1 ? points[i + 1] : points[0];
        sum += (p1.x * p2.y) - (p1.y * p2.x);
    }
    return 0.5f * sum;
}
