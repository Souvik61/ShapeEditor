#ifndef __CLIPPER_H__
#define __CLIPPER_H__

#include "cocos2d.h"
#include "box2d/include/box2d/box2d.h"


class Clipper {
public:
    enum Polygonizer { EWJORDAN, BAYAZIT };

    static void polygonize(Polygonizer polygonizer, ax::Vec2 points[], int s, std::vector<std::vector<ax::Vec2>>& dest);

private:
    static void sliceForMax8Vertices(std::vector<std::vector<ax::Vec2>>& dest);

    //Utility Methods
    static void fillVector(std::vector<ax::Vec2>& dest, ax::Vec2 src[], int size);
    static void fillArray(ax::Vec2 dest[], const std::vector<ax::Vec2>& src, int size);
    static void fillArrayN(ax::Vec2 dest[], const std::vector<ax::Vec2>& src, int startIndx, int size);
    static void arrayCopyLite(const std::vector<std::vector<ax::Vec2>>& source_arr, int sourcePos, std::vector<std::vector<ax::Vec2>>& dest_arr, int destPos, int len);

};

#endif