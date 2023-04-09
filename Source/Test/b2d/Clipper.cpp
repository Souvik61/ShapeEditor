#include "Test/b2d/Clipper.h"
#include "Test/b2d/PolygonUtils.h"
#include "BayazitDecomposer.h"

USING_NS_CC;
using namespace std;

void Clipper::polygonize(Polygonizer polygonizer, ax::Vec2 points[], int s, std::vector<std::vector<ax::Vec2>>& dest)
{
    Vec2** polygons = nullptr;

    //if (PolygonUtils::isPolygonCCW(points, s)) {
    //    List<Vector2> vertices = Arrays.asList(points);
    //    Collections.reverse(vertices);
    //    points = vertices.toArray(new Vector2[0]);
    //}

    //create a tmpPoints vector and make a copy of points array
    std::vector<Vec2> tmpPoints;
    tmpPoints.reserve(s);
    //tmpPoints.addAll(points);
    fillVector(tmpPoints, points, s);

    std::vector<std::vector<Vec2>> tmpPolygons;

    //tmpPolygons = BayazitDecomposer::ConvexPartition(tmpPoints);

    try {
        tmpPolygons = BayazitDecomposer::ConvexPartition(tmpPoints);
    }
    catch (...) {
        //tmpPolygons = nullptr;
    }

    //if (!tmpPolygons.empty()) {
    //    polygons = new Vector2[tmpPolygons.size][];
    //    for (int i = 0; i < tmpPolygons.size; i++) {
    //        polygons[i] = new Vector2[tmpPolygons.get(i).size];
    //        for (int ii = 0; ii < tmpPolygons.get(i).size; ii++)
    //            polygons[i][ii] = new Vector2(tmpPolygons.get(i).get(ii));
    //    }
    //}

    if (!tmpPolygons.empty()) {

        dest = tmpPolygons;
    }

    if (!dest.empty()) {
     
        sliceForMax8Vertices(dest);
    }
 
}

void Clipper::sliceForMax8Vertices(std::vector<std::vector<ax::Vec2>>& dest)
{
    for (int i = 0; i < dest.size(); i++) {//For each polygon

        std::vector<Vec2> poly = dest[i];
        
        if (poly.size() > 8) {

            int limit = poly.size() < 15 ? poly.size() / 2 + 1 : 8;

            Vec2* newPoly1 = new Vec2[limit];
            Vec2* newPoly2 = new Vec2[poly.size() - limit + 2];

            //System.arraycopy(poly, 0, newPoly1, 0, limit);
            //System.arraycopy(poly, limit - 1, newPoly2, 0, poly.length - limit + 1);
            //Copy from poly to newPoly1
            fillArray(newPoly1, poly, limit);
            fillArrayN(newPoly2, poly, limit - 1, poly.size() - limit + 1);

            newPoly2[poly.size() - limit + 1] = poly[0];

            //Vec2 newPolys[][] = new Vector2[polygons.length + 1][];
            
            std::vector<std::vector<Vec2>> newPolys;////--------------------------New polys
            
            if (i > 0) {
                //System.arraycopy(polygons, 0, newPolys, 0, i);

                newPolys.insert(newPolys.begin(), std::begin(dest), std::begin(dest) + i + 1);//--------------------------

            }
            if (i < dest.size() - 1) {
                
                //System.arraycopy(polygons, i + 1, newPolys, i + 2, polygons.length - i - 1);
                
                arrayCopyLite(dest, i + 1, newPolys, i + 2, dest.size() - i - 1);

            }

            //newPolys[i] = newPoly1;
            fillVector(newPolys[i], newPoly1, limit);

            //newPolys[i + 1] = newPoly2;
            fillVector(newPolys[i + 1], newPoly2, poly.size() - limit + 2);

            dest = newPolys;

            i -= 1;
        }
    }
}

void Clipper::fillVector(std::vector<ax::Vec2>& dest, ax::Vec2 src[], int size)
{
    for (size_t i = 0; i < size; i++)
    {
        dest.push_back(src[i]);
    }
}

void Clipper::fillArray(ax::Vec2 dest[], const std::vector<ax::Vec2>& src, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        dest[i] = src.at(i);
    }
}

void Clipper::fillArrayN(ax::Vec2 dest[], const std::vector<ax::Vec2>& src, int startIndx, int len)
{
    for (size_t i = startIndx; i < startIndx + len; i++)
    {
        dest[i] = src.at(i);
    }
}

void Clipper::arrayCopyLite(const vector<vector<Vec2>>& source_arr, int sourcePos, vector<vector<Vec2>>& dest_arr, int destPos, int len) {

    int j = destPos;
    for (size_t i = sourcePos; i < sourcePos + len; i++)
    {
        dest_arr[j] = source_arr[i];
        j++;
    }

}