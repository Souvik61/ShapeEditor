#include "NewShapesDrawNode.h"
#include "RigidBodiesManager.h"
#include "ShapeModel.h"
#include "RigidBodyModel.h"
//#include "EditorPanel.h"
#include "EditorScreenInterface.h"
#include "EditorPanelUI.h"
#include "PointArrayDelegate.h"
#include "OverallManager.h"

USING_NS_CC;

bool NewShapesDrawNode::init()
{
    scheduleUpdate();
    _shapeDraw = DrawNode::create();
	addChild(_shapeDraw);
    _vertDraw = DrawNode::create();
    addChild(_vertDraw, 1);
    _selectionDraw = DrawNode::create();
    addChild(_selectionDraw, 1);
    _trDraw = DrawNode::create();
    addChild(_trDraw, 10);
	return true;
}

void NewShapesDrawNode::update(float)
{
    clearDrawNodes();
    if (!_pauseDraw)
        drawModels();
}

void NewShapesDrawNode::drawModels()
{
    if (_ready)
    {
        drawShapes();
        drawPolygons();
        drawCircles();
        drawVerts();
        drawSelectedVerts();
        drawSelectionBox();
        //drawOrigin();
        //Draw nearest point dot
        //_vertDraw->drawDot(_nearestPoint, 7, Color4F::GREEN); //11

        //Vec2 t = _nearestPoint;
        //_editPanelUI->oManager->spaceConv->applyT(&t);
        //_vertDraw->drawDot(t, 7, Color4F::GREEN); //11

    }
}

//void NewShapesDrawNode::drawShapes()
//{
//    if (_rbManagerRef->getSelectedModel() == nullptr)
//        return;
//    Vector<ShapeModel*>& _shapeList = _rbManagerRef->getSelectedModel()->_shapes;
//
//    for (ShapeModel* shape : _shapeList) {
//        vector<Vec2>& vs = shape->_vertices;
//        if (vs.empty())
//            continue;
//
//        switch (shape->getType()) {
//        case ShapeModel::Type::POLYGON:
//        {
//            //Draw lines
//            for (int i = 1; i < vs.size(); i++)
//                _shapeDraw->drawLine(vs[i], vs[i - 1], Color4F::WHITE);
//
//            //If shape is closed close the loop
//            if (shape->isClosed()) {
//                _shapeDraw->drawLine(vs[0], vs[vs.size() - 1], Color4F::WHITE);
//            }
//            else { //Else
//                _shapeDraw->drawLine(_editPanelUI->_screenInterface->_currentPointerLoc, vs[vs.size() - 1], Color4F::WHITE);
//            }
//        }
//        break;
//        case ShapeModel::Type::CIRCLE:
//        {
//            //Draw circles
//        }
//        break;
//        };
//    }
//}

void NewShapesDrawNode::clearDrawNodes()
{
    _shapeDraw->clear();
    _shapeDraw->setLineWidth(2.f);
    _vertDraw->clear();
    _vertDraw->setLineWidth(2);
    _selectionDraw->clear();
}

void NewShapesDrawNode::drawShapes()
{
    if (_rbManagerRef->getSelectedModel() == nullptr)
        return;

    Vec2* bV = new Vec2();
    Vec2* bV1 = new Vec2();

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
            {
                bV->set(vs[i]);
                bV1->set(vs[i-1]);

                //_editPanelUI->oManager->buffDelegate->applyNewTransform(bV);
                //_editPanelUI->oManager->buffDelegate->applyNewTransform(bV1);

                _editPanelUI->oManager->spaceConv->applyT(bV);
                _editPanelUI->oManager->spaceConv->applyT(bV1);

                _shapeDraw->drawLine(*bV, *bV1, Color4F::BLUE);
            }
            //If shape is closed close the loop
            if (shape->isClosed()) {
                bV->set(vs[0]);
                bV1->set(vs[vs.size() - 1]);
                
                //_editPanelUI->oManager->buffDelegate->applyNewTransform(bV);
                //_editPanelUI->oManager->buffDelegate->applyNewTransform(bV1);
                
                _editPanelUI->oManager->spaceConv->applyT(bV);
                _editPanelUI->oManager->spaceConv->applyT(bV1);

                _shapeDraw->drawLine(*bV, *bV1, Color4F::BLUE);
            }
            else { //Else
                bV->set(vs[vs.size() - 1]);
                //pDelegate->applyTransform(bV);
                
                //_editPanelUI->oManager->buffDelegate->applyNewTransform(bV);
                _editPanelUI->oManager->spaceConv->applyT(bV);
                
                _shapeDraw->drawLine(_editPanelUI->_screenInterface->_currentPointerLoc, *bV, Color4F::GRAY);
            }
        }
        break;
        case ShapeModel::Type::CIRCLE:
        {
            //Draw circles
        }
        break;
        };
    }

    delete bV;
    delete bV1;
}

void NewShapesDrawNode::drawPolygons()
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

void NewShapesDrawNode::drawCircles()
{

}

void NewShapesDrawNode::drawVerts()
{
    if (_rbManagerRef->getSelectedModel() == nullptr)
        return;
    Vec2 bV;
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
            {
                //bV->set(vs[i]);
                //pDelegate->applyTransform(bV);
                bV.set(vs[i]);
                //_editPanelUI->oManager->buffDelegate->applyNewTransform(&bV);
                _editPanelUI->oManager->spaceConv->applyT(&bV);
                
                //_vertDraw->drawDot(bV, 7, Color4F::BLUE);
                Size dotSize(5, 5);
                _vertDraw->drawRect(bV - dotSize, bV + dotSize, Color4F::BLUE);

            }
        }
        break;
        case ShapeModel::Type::CIRCLE:
        {
        }
        break;
        };
    }
}

void NewShapesDrawNode::drawSelectedVerts()
{
    std::vector<Vec2*>& points = _editPanelUI->selectedPoints;

    for (auto point : points)
    {
        Vec2 v(*point);
        _editPanelUI->oManager->spaceConv->applyT(&v);

        _vertDraw->drawDot(v, 5, Color4F::GREEN);


    }
}

//void NewShapesDrawNode::drawSelectionBox()
//{
//    Vec2* sP1 = _editPanelUI->_screenInterface->mouseSelectP1;
//    Vec2* sP2 = _editPanelUI->_screenInterface->mouseSelectP2;
//
//    if (sP1 && sP2)
//    {
//        _selectionDraw->drawRect(*sP1, *sP2, Color4F::GREEN);
//        _selectionDraw->drawSolidRect(*sP1, *sP2, Color4F(0, 1, 0, 0.40f));
//    }
//}

void NewShapesDrawNode::drawSelectionBox()
{
    Vec2* sP1 = _editPanelUI->_screenInterface->mouseSelectP1;
    Vec2* sP2 = _editPanelUI->_screenInterface->mouseSelectP2;

    if (sP1 && sP2)
    {
        Vec2 a = *sP1;
        Vec2 b = *sP2;

        //_editPanelUI->oManager->buffDelegate->applyNewInvTransform(&a);
        //_editPanelUI->oManager->buffDelegate->applyNewInvTransform(&b);
        _editPanelUI->oManager->spaceConv->applyT(&a);
        _editPanelUI->oManager->spaceConv->applyT(&b);

        _selectionDraw->drawRect(a, b, Color4F::GREEN);
        _selectionDraw->drawSolidRect(a, b, Color4F(0, 1, 0, 0.40f));
    }
}

void NewShapesDrawNode::drawOrigin()
{
    Vec2 a, b;
    _trDraw->clear();
    _trDraw->setLineWidth(3);
    //Draw X axis
    {
        b.set(77, 0);
        _editPanelUI->oManager->buffDelegate->applyNewTransform(&a);
        _editPanelUI->oManager->buffDelegate->applyNewTransform(&b);
        _trDraw->drawLine(a, b, Color4F::RED);
        _trDraw->drawLine(b, b + Vec2(-10, -10), Color4F::RED);
        _trDraw->drawLine(b, b + Vec2(-10, 10), Color4F::RED);
    }
    //Draw Y axis
    {
        b.set(0, 77);
        _editPanelUI->oManager->buffDelegate->applyNewTransform(&b);
        _trDraw->drawLine(a, b, Color4F::GREEN);
        _trDraw->drawLine(b, b + Vec2(-10, -10), Color4F::GREEN);
        _trDraw->drawLine(b, b + Vec2(10, -10), Color4F::GREEN);
    }

}
