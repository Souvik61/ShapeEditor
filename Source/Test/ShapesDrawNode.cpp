#include "ShapesDrawNode.h"
#include "RigidBodiesManager.h"
#include "ShapeModel.h"
#include "RigidBodyModel.h"
#include "Test/UI/EditorScreenInterface.h"
#include "Test/UI/EditorPanelUI.h"

using namespace std;
USING_NS_CC;

bool ShapesDrawNode::init()
{
    scheduleUpdate();
	_shapeDraw = DrawNode::create();
	addChild(_shapeDraw);
    _vertDraw = DrawNode::create();
    addChild(_vertDraw, 1);
    _selectionDraw = DrawNode::create();
    addChild(_selectionDraw, 1);
	return true;
}

void ShapesDrawNode::update(float)
{
    drawModels();
}

void ShapesDrawNode::setRbManager(RigidBodiesManager* man)
{
	_rbManagerRef = man;
    _ready = true;
}

//void ShapesDrawNode::drawShapes()
//{
//    Vector<ShapeModel*>& _shapeList = _rbManagerRef->getSelectedModel()->_shapes;
//    cocos2d::Vector<ShapeModel*>::iterator it = _shapeList.begin();
//    for (; it != _shapeList.end(); it++) {
//        vector<Vec2> vs = (*it)->_vertices;
//        for (int i = 1, n = vs.size(); i < n; i++) {
//            _shapeDraw->drawLine(vs[i], vs[i - 1], Color4F::WHITE);
//        }
//    }
//}

void ShapesDrawNode::drawModels()
{
    _shapeDraw->clear();
    _vertDraw->clear();
    _selectionDraw->clear();
    if (_ready)
    {
        drawShapes();
        drawPolygons();
        drawCircles();
        drawVerts();
        drawSelectedVerts();
        drawSelectionBox();
        //Draw nearest point dot
        _vertDraw->drawDot(_nearestPoint, 7, Color4F::GREEN); //11

    }
}

void ShapesDrawNode::drawShapes()
{
    if (_rbManagerRef->getSelectedModel() == nullptr)
        return;
    Vector<ShapeModel*>& _shapeList = _rbManagerRef->getSelectedModel()->_shapes;

    for (ShapeModel* shape : _shapeList) {
        vector<Vec2>& vs = shape->_vertices;
        if (vs.empty())
            continue;

        switch (shape->getType()) {
        case ShapeModel::Type::POLYGON:
        {
            //Draw lines
            for (int i = 1; i < vs.size(); i++)
                _shapeDraw->drawLine(vs[i], vs[i - 1], Color4F::WHITE);

            //If shape is closed close the loop
            if (shape->isClosed()) {
                _shapeDraw->drawLine(vs[0], vs[vs.size() - 1], Color4F::WHITE);
            }
            else { //Else
                //_shapeDraw->drawLine(_editPanelUI->_screenInterface->_currentPointerLoc, vs[vs.size() - 1], Color4F::WHITE);
            }
        }
        break;
        case ShapeModel::Type::CIRCLE:
        {
            //if (shape.isClosed()) {
            //    Vector2 center = shape.getVertices().get(0);
            //    float radius = shape.getVertices().get(1).cpy().sub(center).len();
            //    if (radius > 0.0001f) {
            //        drawer.begin(ShapeRenderer.ShapeType.Line);
            //        drawer.setColor(SHAPE_COLOR);
            //        drawer.circle(center.x, center.y, radius, 20);
            //        drawer.end();
            //    }
            //}
            //else {
            //    Vector2 center = shape.getVertices().get(0);
            //    float radius = nextPoint.cpy().sub(center).len();
            //
            //    if (radius > 0.0001f) {
            //        drawer.begin(ShapeRenderer.ShapeType.Line);
            //        drawer.setColor(SHAPE_LASTLINE_COLOR);
            //        drawer.circle(center.x, center.y, radius, 20);
            //        drawer.end();
            //    }
            //}
        }
        break;
        };
    }
}

void ShapesDrawNode::drawPolygons()
{
    if (_rbManagerRef->getSelectedModel() == nullptr)
        return;
    Vector<PolygonModel*>& _polygonList = _rbManagerRef->getSelectedModel()->_polygons;
    cocos2d::Vector<PolygonModel*>::iterator it = _polygonList.begin();
    for (; it != _polygonList.end(); it++) {
        vector<Vec2> vs = (*it)->_vertices;
        for (int i = 1, n = vs.size(); i < n; i++) {
            //drawer.line(vs.get(i).x, vs.get(i).y, vs.get(i - 1).x, vs.get(i - 1).y);
            _shapeDraw->drawLine(vs[i], vs[i - 1], Color4F::GREEN);
        }
        if (vs.size() > 1);
            //drawer.line(vs.get(0).x, vs.get(0).y, vs.get(vs.size() - 1).x, vs.get(vs.size() - 1).y);
            //_shapeDraw->drawLine(vs[0], vs[vs.size() - 1], Color4F::GREEN);
    }
}

void ShapesDrawNode::drawCircles()
{

}

void ShapesDrawNode::drawVerts()
{
    if (_rbManagerRef->getSelectedModel() == nullptr)
        return;

    Vector<ShapeModel*>& _shapeList = _rbManagerRef->getSelectedModel()->_shapes;

    for (ShapeModel* shape : _shapeList) {
        vector<Vec2>& vs = shape->_vertices;
        if (vs.empty())
            continue;

        switch (shape->getType()) {
        case ShapeModel::Type::POLYGON:
        {
            //Draw vertices
            for (int i = 0; i < vs.size(); i++)
                _vertDraw->drawDot(vs[i], 7, Color4F::BLUE);
        }
        break;
        case ShapeModel::Type::CIRCLE:
        {
        }
        break;
        };
    }
}

void ShapesDrawNode::drawSelectedVerts()
{
    //std::vector<Vec2*>& points = _editPanelUI->selectedPoints;
    //
    //for (auto point : points)
    //{
    //    _vertDraw->drawDot(*point, 5, Color4F::GREEN);
    //}
}

void ShapesDrawNode::drawSelectionBox()
{
    //Vec2* sP1 = _editPanelUI->_screenInterface->mouseSelectP1;
    //Vec2* sP2 = _editPanelUI->_screenInterface->mouseSelectP2;
    //
    //if (sP1 && sP2)
    //{
    //    _selectionDraw->drawRect(*sP1, *sP2, Color4F::GREEN);
    //    _selectionDraw->drawSolidRect(*sP1, *sP2, Color4F(0, 1, 0, 0.40f));
    //}
}
