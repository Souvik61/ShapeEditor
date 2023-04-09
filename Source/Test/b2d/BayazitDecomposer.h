#ifndef __BAYAZIT_DECOMPOSER_H__
#define __BAYAZIT_DECOMPOSER_H__

#include "axmol.h"

USING_NS_AX;
using namespace std;

class BayazitDecomposer {

public:
    static constexpr float Epsilon = 1.192092896e-07f;
    static const int MaxPolygonVertices = 8;

    static Vec2 Cross(Vec2 a, float s) {
        return Vec2(s * a.y, -s * a.x);
    }

    static Vec2 At(int i, vector<Vec2> vertices) {
        int s = vertices.size();
        return vertices.at(i < 0 ? s - (-i % s) : i % s);
    }

    static vector<Vec2> Copy(int i, int j, vector<Vec2> vertices);

    static float GetSignedArea(vector<Vec2> vect);

    static float GetSignedArea(Vec2 vect[], int s);

    static bool IsCounterClockWise(vector<Vec2> vect) {
        // We just return true for lines
        if (vect.size() < 3)
            return true;
        return (GetSignedArea(vect) > 0.0f);
    }

    static bool IsCounterClockWise(Vec2 vect[], int size) {
        // We just return true for lines
        if (size < 3)
            return true;
        return (GetSignedArea(vect, size) > 0.0f);
    }

    // / <summary>
    // / Decompose the polygon into several smaller non-concave polygon.
    // / If the polygon is already convex, it will return the original polygon,
    // unless it is over Settings.MaxPolygonVertices.
    // / Precondition: Counter Clockwise polygon
    // / </summary>
    // / <param name="vertices"></param>
    // / <returns></returns>
    static vector<vector<Vec2>> ConvexPartition(vector<Vec2> vertices);

    static bool CanSee(int i, int j, vector<Vec2> vertices);

    static Vec2 LineIntersect(Vec2 p1, Vec2 p2, Vec2 q1, Vec2 q2) {
        Vec2 i;
        float a1 = p2.y - p1.y;
        float b1 = p1.x - p2.x;
        float c1 = a1 * p1.x + b1 * p1.y;
        float a2 = q2.y - q1.y;
        float b2 = q1.x - q2.x;
        float c2 = a2 * q1.x + b2 * q1.y;
        float det = a1 * b2 - a2 * b1;
        if (!FloatEquals(det, 0)) {
            // lines are not parallel
            i.x = (b2 * c1 - b1 * c2) / det;
            i.y = (a1 * c2 - a2 * c1) / det;
        }
        return i;
    }

    static bool FloatEquals(float value1, float value2) {
        return abs(value1 - value2) <= Epsilon;
    }

    // / <summary>
    // / This method detects if two line segments (or lines) intersect,
    // / and, if so, the point of intersection. Use the
    // <paramname="firstIsSegment"/> and
    // / <paramname="secondIsSegment"/> parameters to set whether the
    // intersection point
    // / must be on the first and second line segments. Setting these
    // / both to true means you are doing a line-segment to line-segment
    // / intersection. Setting one of them to true means you are doing a
    // / line to line-segment intersection test, and so on.
    // / Note: If two line segments are coincident, then
    // / no intersection is detected (there are actually
    // / infinite intersection points).
    // / Author: Jeremy Bell
    // / </summary>
    // / <param name="point1">The first point of the first line segment.</param>
    // / <param name="point2">The second point of the first line
    // segment.</param>
    // / <param name="point3">The first point of the second line
    // segment.</param>
    // / <param name="point4">The second point of the second line
    // segment.</param>
    // / <param name="point">This is set to the intersection
    // / point if an intersection is detected.</param>
    // / <param name="firstIsSegment">Set this to true to require that the
    // / intersection point be on the first line segment.</param>
    // / <param name="secondIsSegment">Set this to true to require that the
    // / intersection point be on the second line segment.</param>
    // / <returns>True if an intersection is detected, false
    // otherwise.</returns>
    static bool LineIntersect(Vec2 point1, Vec2 point2, Vec2 point3, Vec2 point4, bool firstIsSegment, bool secondIsSegment, Vec2 point) {

        //point = new Vec2();

        // these are reused later.
        // each lettered sub-calculation is used twice, except
        // for b and d, which are used 3 times
        float a = point4.y - point3.y;
        float b = point2.x - point1.x;
        float c = point4.x - point3.x;
        float d = point2.y - point1.y;
        // denominator to solution of linear system
        float denom = (a * b) - (c * d);
        // if denominator is 0, then lines are parallel
        if (!(denom >= -Epsilon && denom <= Epsilon)) {
            float e = point1.y - point3.y;
            float f = point1.x - point3.x;
            float oneOverDenom = 1.0f / denom;
            // numerator of first equation
            float ua = (c * e) - (a * f);
            ua *= oneOverDenom;
            // check if intersection point of the two lines is on line segment 1
            if (!firstIsSegment || ua >= 0.0f && ua <= 1.0f) {
                // numerator of second equation
                float ub = (b * e) - (d * f);
                ub *= oneOverDenom;
                // check if intersection point of the two lines is on line
                // segment 2
                // means the line segments intersect, since we know it is on
                // segment 1 as well.
                if (!secondIsSegment || ub >= 0.0f && ub <= 1.0f) {
                    // check if they are coincident (no collision in this case)
                    if (ua != 0.f || ub != 0.f) {
                        // There is an intersection
                        point.x = point1.x + ua * b;
                        point.y = point1.y + ua * d;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // precondition: ccw
    static bool Reflex(int i, vector<Vec2> vertices) {
        return Right(i, vertices);
    }

    static bool Right(int i, vector<Vec2> vertices) {
        return Right(At(i - 1, vertices), At(i, vertices), At(i + 1, vertices));
    }

    static bool Left(Vec2 a, Vec2 b, Vec2 c) {
        return Area(a, b, c) > 0;
    }

    static bool LeftOn(Vec2 a, Vec2 b, Vec2 c) {
        return Area(a, b, c) >= 0;
    }

    static bool Right(Vec2 a, Vec2 b, Vec2 c) {
        return Area(a, b, c) < 0;
    }

    static bool RightOn(Vec2 a, Vec2 b, Vec2 c) {
        return Area(a, b, c) <= 0;
    }

    static float Area(Vec2 a, Vec2 b, Vec2 c) {
        return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    }

    static float SquareDist(Vec2 a, Vec2 b) {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        return dx * dx + dy * dy;
    }
};

class SimplifyTools {
    static vector<bool> _usePt;
    static double _distanceTolerance;
public:
    // / <summary>
    // / Removes all collinear points on the polygon.
    // / </summary>
    // / <param name="vertices">The polygon that needs simplification.</param>
    // / <param name="collinearityTolerance">The collinearity tolerance.</param>
    // / <returns>A simplified polygon.</returns>
    static vector<Vec2> CollinearSimplify(vector<Vec2> vertices, float collinearityTolerance) {
        // We can't simplify polygons under 3 vertices
        if (vertices.size() < 3)
            return vertices;
        vector<Vec2> simplified;
        for (int i = 0; i < vertices.size(); i++) {
            int prevId = i - 1;
            if (prevId < 0)
                prevId = vertices.size() - 1;
            int nextId = i + 1;
            if (nextId >= vertices.size())
                nextId = 0;
            Vec2 prev = vertices.at(prevId);
            Vec2 current = vertices.at(i);
            Vec2 next = vertices.at(nextId);
            // If they collinear, continue
            if (Collinear(prev, current, next, collinearityTolerance))
                continue;
            simplified.push_back(current);
        }
        return simplified;
    }

    static bool Collinear(Vec2 a, Vec2 b, Vec2 c, float tolerance) {
        return FloatInRange(BayazitDecomposer::Area(a, b, c), -tolerance, tolerance);
    }

    static bool FloatInRange(float value, float min, float max) {
        return (value >= min && value <= max);
    }

    // / <summary>
    // / Removes all collinear points on the polygon.
    // / Has a default bias of 0
    // / </summary>
    // / <param name="vertices">The polygon that needs simplification.</param>
    // / <returns>A simplified polygon.</returns>
    static vector<Vec2> CollinearSimplify(vector<Vec2> vertices) {
        return CollinearSimplify(vertices, 0);
    }

    // / <summary>
    // / Ramer-Douglas-Peucker polygon simplification algorithm. This is the
    // general recursive version that does not use the
    // / speed-up technique by using the Melkman convex hull.
    // /
    // / If you pass in 0, it will remove all collinear points
    // / </summary>
    // / <returns>The simplified polygon</returns>
    static vector<Vec2> DouglasPeuckerSimplify(vector<Vec2> vertices, float distanceTolerance) {

        _distanceTolerance = distanceTolerance;
        _usePt.reserve(vertices.size());
        for (int i = 0; i < vertices.size(); i++)
            _usePt[i] = true;
        SimplifySection(vertices, 0, vertices.size() - 1);
        vector<Vec2> result;
        for (int i = 0; i < vertices.size(); i++)
            if (_usePt[i])
                result.push_back(vertices.at(i));
        return result;
    }

    static void SimplifySection(vector<Vec2> vertices, int i, int j);

    static double DistancePointPoint(Vec2 p, Vec2 p2) {
        double dx = (double)p.x - p2.x;
        double dy = (double)p.y - p2.x;
        return sqrt(dx * dx + dy * dy);
    }

    static double DistancePointLine(Vec2 p, Vec2 A, Vec2 B) {
        // if start == end, then use point-to-point distance
        if (A.x == B.x && A.y == B.y)
            return DistancePointPoint(p, A);
        // otherwise use comp.graphics.algorithms Frequently Asked Questions
        // method
      /*
       * (1) AC dot AB r = --------- ||AB||^2 r has the following meaning: r=0
       * Point = A r=1 Point = B r<0 Point is on the backward extension of AB
       * r>1 Point is on the forward extension of AB 0<r<1 Point is interior
       * to AB
       */
        double r = ((p.x - A.x) * (B.x - A.x) + (p.y - A.y) * (B.y - A.y))
            / ((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
        if (r <= 0.0)
            return DistancePointPoint(p, A);
        if (r >= 1.0)
            return DistancePointPoint(p, B);
        /*
         * (2) (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay) s = -----------------------------
         * Curve^2 Then the distance from C to Point = |s|*Curve.
         */
        double s = ((A.y - p.y) * (B.x - A.x) - (A.x - p.x) * (B.y - A.y))
            / ((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
        return abs(s)
            * sqrt(((B.x - A.x) * (B.x - A.x) + (B.y - A.y)
                * (B.y - A.y)));
    }

    // From physics2d.net
    static vector<Vec2> ReduceByArea(vector<Vec2> vertices, float areaTolerance);

    static float Cross(Vec2 a, Vec2 b) {
        return a.x * b.y - a.y * b.x;
    }

    // From Eric Jordan's convex decomposition library
    // / <summary>
    // / Merges all parallel edges in the list of vertices
    // / </summary>
    // / <param name="vertices">The vertices.</param>
    // / <param name="tolerance">The tolerance.</param>
    static void MergeParallelEdges(vector<Vec2> vertices, float tolerance);

    // Misc
    // / <summary>
    // / Merges the identical points in the polygon.
    // / </summary>
    // / <param name="vertices">The vertices.</param>
    // / <returns></returns>
    static vector<Vec2> MergeIdenticalPoints(vector<Vec2> vertices);

    // / <summary>
    // / Reduces the polygon by distance.
    // / </summary>
    // / <param name="vertices">The vertices.</param>
    // / <param name="distance">The distance between points. Points closer than
    // this will be 'joined'.</param>
    // / <returns></returns>
    static vector<Vec2> ReduceByDistance(vector<Vec2> vertices, float distance);

    // / <summary>
    // / Reduces the polygon by removing the Nth vertex in the vertices list.
    // / </summary>
    // / <param name="vertices">The vertices.</param>
    // / <param name="nth">The Nth point to remove. Example: 5.</param>
    // / <returns></returns>
    static vector<Vec2> ReduceByNth(vector<Vec2> vertices, int nth);
};

#endif // __BAYAZIT_DECOMPOSER_H__
