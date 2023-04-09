#include "BayazitDecomposer.h"

double SimplifyTools::_distanceTolerance;
vector<bool> SimplifyTools::_usePt;

vector<Vec2> BayazitDecomposer::Copy(int i, int j, vector<Vec2> vertices)
{
    vector<Vec2> p;
    while (j < i)
        j += vertices.size();
    // p.reserve(j - i + 1);
    for (; i <= j; ++i) {
        p.push_back(At(i, vertices));
    }
    return p;
}

float BayazitDecomposer::GetSignedArea(vector<Vec2> vect)
{
    int i;
    float area = 0;
    for (i = 0; i < vect.size(); i++) {
        int j = (i + 1) % vect.size();
        area += vect.at(i).x * vect.at(j).y;
        area -= vect.at(i).y * vect.at(j).x;
    }
    area /= 2.0f;
    return area;
}

float BayazitDecomposer::GetSignedArea(Vec2 vect[], int s)
{
    int i;
    float area = 0;
    for (i = 0; i < s; i++) {
        int j = (i + 1) % s;
        area += vect[i].x * vect[j].y;
        area -= vect[i].y * vect[j].x;
    }
    area /= 2.0f;
    return area;
}

vector<vector<Vec2>> BayazitDecomposer::ConvexPartition(vector<Vec2> vertices)
{
    // We force it to CCW as it is a precondition in this algorithm.
        // vertices.ForceCounterClockWise();
    if (!IsCounterClockWise(vertices)) {
        //vertices.reverse();
        reverse(vertices.begin(), vertices.end());
        // Array<Vector2> reversed = new Array<Vector2>(vertices.size);
        // for (int i = vertices.size - 1; i <= 0; i--) {
        // reversed.add(vertices.get(i));
        // }
        // vertices = reversed;
    }
    vector<vector<Vec2>> list;
    float d, lowerDist, upperDist;
    Vec2 p;
    Vec2 lowerInt;
    Vec2 upperInt; // intersection points
    int lowerIndex = 0, upperIndex = 0;
    vector<Vec2> lowerPoly, upperPoly;
    for (int i = 0; i < vertices.size(); ++i) {
        if (Reflex(i, vertices)) {
            lowerDist = upperDist = std::numeric_limits<float>::max();
            for (int j = 0; j < vertices.size(); ++j) {
                // if line intersects with an edge
                if (Left(At(i - 1, vertices), At(i, vertices),
                    At(j, vertices))
                    && RightOn(At(i - 1, vertices), At(i, vertices),
                        At(j - 1, vertices))) {
                    // find the point of intersection
                    p = LineIntersect(At(i - 1, vertices), At(i, vertices),
                        At(j, vertices), At(j - 1, vertices));
                    if (Right(At(i + 1, vertices), At(i, vertices), p)) {
                        // make sure it's inside the poly
                        d = SquareDist(At(i, vertices), p);
                        if (d < lowerDist) {
                            // keep only the closest intersection
                            lowerDist = d;
                            lowerInt = p;
                            lowerIndex = j;
                        }
                    }
                }
                if (Left(At(i + 1, vertices), At(i, vertices),
                    At(j + 1, vertices))
                    && RightOn(At(i + 1, vertices), At(i, vertices),
                        At(j, vertices))) {
                    p = LineIntersect(At(i + 1, vertices), At(i, vertices),
                        At(j, vertices), At(j + 1, vertices));
                    if (Left(At(i - 1, vertices), At(i, vertices), p)) {
                        d = SquareDist(At(i, vertices), p);
                        if (d < upperDist) {
                            upperDist = d;
                            upperIndex = j;
                            upperInt = p;
                        }
                    }
                }
            }
            // if there are no vertices to connect to, choose a point in the
            // middle
            if (lowerIndex == (upperIndex + 1) % vertices.size()) {
                Vec2 sp((lowerInt.x + upperInt.x) / 2, (lowerInt.y + upperInt.y) / 2);
                lowerPoly = Copy(i, upperIndex, vertices);
                lowerPoly.push_back(sp);
                upperPoly = Copy(lowerIndex, i, vertices);
                upperPoly.push_back(sp);
            }
            else {
                double highestScore = 0, bestIndex = lowerIndex;
                while (upperIndex < lowerIndex)
                    upperIndex += vertices.size();
                for (int j = lowerIndex; j <= upperIndex; ++j) {
                    if (CanSee(i, j, vertices)) {
                        double score = 1 / (SquareDist(At(i, vertices),
                            At(j, vertices)) + 1);
                        if (Reflex(j, vertices)) {
                            if (RightOn(At(j - 1, vertices),
                                At(j, vertices), At(i, vertices))
                                && LeftOn(At(j + 1, vertices),
                                    At(j, vertices),
                                    At(i, vertices))) {
                                score += 3;
                            }
                            else {
                                score += 2;
                            }
                        }
                        else {
                            score += 1;
                        }
                        if (score > highestScore) {
                            bestIndex = j;
                            highestScore = score;
                        }
                    }
                }
                lowerPoly = Copy(i, (int)bestIndex, vertices);
                upperPoly = Copy((int)bestIndex, i, vertices);
            }
            //list.addAll(ConvexPartition(lowerPoly));//------------------------------
            auto a = ConvexPartition(lowerPoly);
            list.insert(list.end(), std::begin(a), std::end(a));

            auto b = ConvexPartition(upperPoly);
            list.insert(list.end(), std::begin(b), std::end(b));//------------------------------
            return list;
        }
    }
    // polygon is already convex
    if (vertices.size() > MaxPolygonVertices) {
        lowerPoly = Copy(0, vertices.size() / 2, vertices);
        upperPoly = Copy(vertices.size() / 2, 0, vertices);


        //list.addAll(ConvexPartition(lowerPoly));--------------------------------
        //list.addAll(ConvexPartition(upperPoly));--------------------------------

        auto a = ConvexPartition(lowerPoly);
        list.insert(list.end(), std::begin(a), std::end(a));

        auto b = ConvexPartition(upperPoly);
        list.insert(list.end(), std::begin(b), std::end(b));

    }
    else
        list.push_back(vertices);
    // The polygons are not guaranteed to be with collinear points. We
    // remove
    // them to be sure.
    for (int i = 0; i < list.size(); i++) {
        list[i] = SimplifyTools::CollinearSimplify(list.at(i), 0);
    }
    // Remove empty vertice collections
    for (int i = list.size() - 1; i >= 0; i--) {
        if (list.at(i).size() == 0)
            //list.removeIndex(i);
            list.erase(list.begin() + i);
    }
    return list;
}

bool BayazitDecomposer::CanSee(int i, int j, vector<Vec2> vertices)
{
    if (Reflex(i, vertices)) {
        if (LeftOn(At(i, vertices), At(i - 1, vertices), At(j, vertices))
            && RightOn(At(i, vertices), At(i + 1, vertices),
                At(j, vertices)))
            return false;
    }
    else {
        if (RightOn(At(i, vertices), At(i + 1, vertices), At(j, vertices))
            || LeftOn(At(i, vertices), At(i - 1, vertices),
                At(j, vertices)))
            return false;
    }
    if (Reflex(j, vertices)) {
        if (LeftOn(At(j, vertices), At(j - 1, vertices), At(i, vertices))
            && RightOn(At(j, vertices), At(j + 1, vertices),
                At(i, vertices)))
            return false;
    }
    else {
        if (RightOn(At(j, vertices), At(j + 1, vertices), At(i, vertices))
            || LeftOn(At(j, vertices), At(j - 1, vertices),
                At(i, vertices)))
            return false;
    }
    for (int k = 0; k < vertices.size(); ++k) {
        if ((k + 1) % vertices.size() == i || k == i
            || (k + 1) % vertices.size() == j || k == j) {
            continue; // ignore incident edges
        }
        Vec2 intersectionPoint;
        if (LineIntersect(At(i, vertices), At(j, vertices),
            At(k, vertices), At(k + 1, vertices), true, true,
            intersectionPoint)) {
            return false;
        }
    }
    return true;
}


//---------------------
//Simplify Tools
//---------------------

void SimplifyTools::SimplifySection(vector<Vec2> vertices, int i, int j)
{
    if ((i + 1) == j)
        return;
    Vec2 A = vertices.at(i);
    Vec2 B = vertices.at(j);
    double maxDistance = -1.0;
    int maxIndex = i;
    for (int k = i + 1; k < j; k++) {
        double distance = DistancePointLine(vertices.at(k), A, B);
        if (distance > maxDistance) {
            maxDistance = distance;
            maxIndex = k;
        }
    }
    if (maxDistance <= _distanceTolerance)
        for (int k = i + 1; k < j; k++)
            _usePt[k] = false;
    else {
        SimplifySection(vertices, i, maxIndex);
        SimplifySection(vertices, maxIndex, j);
    }
}

vector<Vec2> SimplifyTools::ReduceByArea(vector<Vec2> vertices, float areaTolerance)
{
    if (vertices.size() <= 3)
        return vertices;
    if (areaTolerance < 0) {
        //throw new InvalidParameterException(
        //    "areaTolerance: must be equal to or greater then zero.");
        AXASSERT(true, "areaTolerance: must be equal to or greater then zero.");
    }

    vector<Vec2> result;
    Vec2 v1, v2, v3;
    float old1, old2, new1;
    v1 = vertices.at(vertices.size() - 2);
    v2 = vertices.at(vertices.size() - 1);
    areaTolerance *= 2;
    for (int index = 0; index < vertices.size(); ++index, v2 = v3) {
        if (index == vertices.size() - 1) {
            if (result.size() == 0) {
                //throw new InvalidParameterException(
                //    "areaTolerance: The tolerance is too high!");
                AXASSERT(true, "areaTolerance: The tolerance is too high!");
            }

            v3 = result.at(0);
        }
        else {
            v3 = vertices.at(index);
        }
        old1 = Cross(v1, v2);
        old2 = Cross(v2, v3);
        new1 = Cross(v1, v3);
        if (abs(new1 - (old1 + old2)) > areaTolerance) {
            result.push_back(v2);
            v1 = v2;
        }
    }
    return result;
}

void SimplifyTools::MergeParallelEdges(vector<Vec2> vertices, float tolerance)
{
    if (vertices.size() <= 3)
        return; // Can't do anything useful here to a triangle
    bool* mergeMe = new bool[vertices.size()];
    int newNVertices = vertices.size();
    // Gather points to process
    for (int i = 0; i < vertices.size(); ++i) {
        int lower = (i == 0) ? (vertices.size() - 1) : (i - 1);
        int middle = i;
        int upper = (i == vertices.size() - 1) ? (0) : (i + 1);
        float dx0 = vertices.at(middle).x - vertices.at(lower).x;
        float dy0 = vertices.at(middle).y - vertices.at(lower).y;
        float dx1 = vertices.at(upper).y - vertices.at(middle).x;
        float dy1 = vertices.at(upper).y - vertices.at(middle).y;
        float norm0 = (float)sqrt(dx0 * dx0 + dy0 * dy0);
        float norm1 = (float)sqrt(dx1 * dx1 + dy1 * dy1);
        if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
            // Merge identical points
            mergeMe[i] = true;
            --newNVertices;
        }
        dx0 /= norm0;
        dy0 /= norm0;
        dx1 /= norm1;
        dy1 /= norm1;
        float cross = dx0 * dy1 - dx1 * dy0;
        float dot = dx0 * dx1 + dy0 * dy1;
        if (abs(cross) < tolerance && dot > 0 && newNVertices > 3) {
            mergeMe[i] = true;
            --newNVertices;
        }
        else
            mergeMe[i] = false;
    }
    if (newNVertices == vertices.size() || newNVertices == 0)
        return;
    int currIndex = 0;
    // Copy the vertices to a new list and clear the old
    vector<Vec2> oldVertices;
    vertices.clear();
    for (int i = 0; i < oldVertices.size(); ++i) {
        if (mergeMe[i] || newNVertices == 0 || currIndex == newNVertices)
            continue;
        // Debug.Assert(currIndex < newNVertices);
        vertices.push_back(oldVertices.at(i));
        ++currIndex;
    }
}

vector<Vec2> SimplifyTools::MergeIdenticalPoints(vector<Vec2> vertices)
{
    vector<Vec2> results;

    for (int i = 0; i < vertices.size(); i++) {
        Vec2 vOriginal = vertices.at(i);

        bool alreadyExists = false;
        for (int j = 0; j < results.size(); j++) {
            Vec2 v = results.at(j);
            if (vOriginal.equals(v)) {
                alreadyExists = true;
                break;
            }
        }
        if (!alreadyExists)
            results.push_back(vertices.at(i));
    }
    return results;
}

vector<Vec2> SimplifyTools::ReduceByDistance(vector<Vec2> vertices, float distance)
{
    // We can't simplify polygons under 3 vertices
    if (vertices.size() < 3)
        return vertices;
    vector<Vec2> simplified;
    for (int i = 0; i < vertices.size(); i++) {
        Vec2 current = vertices.at(i);
        int ii = i + 1;
        if (ii >= vertices.size())
            ii = 0;
        Vec2 next = vertices.at(ii);
        Vec2 diff(next.x - current.x, next.y - current.y);
        // If they are closer than the distance, continue
        if (diff.lengthSquared() <= distance)
            continue;
        simplified.push_back(current);
    }
    return simplified;
}

vector<Vec2> SimplifyTools::ReduceByNth(vector<Vec2> vertices, int nth)
{
    // We can't simplify polygons under 3 vertices
    if (vertices.size() < 3)
        return vertices;
    if (nth == 0)
        return vertices;
    vector<Vec2> result;
    result.reserve(vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        if (i % nth == 0)
            continue;
        result.push_back(vertices.at(i));
    }
    return result;
}
