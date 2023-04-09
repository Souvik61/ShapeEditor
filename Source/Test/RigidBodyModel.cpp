#include "RigidBodyModel.h"
#include "Test/b2d/Clipper.h"

USING_NS_CC;

bool RigidBodyModel::init()
{
    _isSaveDirty = false;
    _isPhysDirty = true;
    return true;
}

void RigidBodyModel::computePhysics()
{
    _polygons.clear();
    _circles.clear();

    for (ShapeModel* shape : _shapes) {//For each shape in _shapes
        if (!shape->isClosed()) continue;

        //if (shape->getType() == ShapeModel::Type::POLYGON) {

            //Vector2[] vertices = shape.getVertices().toArray(new Vector2[0]);
            //Vector2[][] polys = Clipper.polygonize(Settings.polygonizer, vertices);
            //if (polys != null) for (Vector2[] poly : polys) polygons.add(new PolygonModel(poly));

        auto& v = shape->_vertices;
        Vec2* verts = new Vec2[v.size()];
        copy(v.begin(), v.end(), verts);//Copy v to verts array

        vector<vector<Vec2>> polys;
        Clipper::polygonize(Clipper::Polygonizer::BAYAZIT, verts, v.size(), polys);

        if (!polys.empty()) {

            for (vector<Vec2> poly : polys) {
             
                _polygons.pushBack(new PolygonModel(poly));
            }

        }

        _shapesValid = !_polygons.empty();

        //}
        //When we do circles do this
        //if (shape.getType() == ShapeModel.Type.CIRCLE) {
        //    Vector2 center = shape.getVertices().get(0);
        //    float radius = Math.abs(shape.getVertices().get(1).cpy().sub(center).len());
        //    circles.add(new CircleModel(center, radius));
        //}

        _isPhysDirty = false;
    }
}

