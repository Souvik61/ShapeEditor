#ifndef __SHAPE_MODEL_H__
#define __SHAPE_MODEL_H__

#include "cocos2d.h"

//Shape model base class

class ShapeModel : public cocos2d::Ref {

public:
    enum class Type { POLYGON, CIRCLE };
    Type type;
    bool _closed = false;
    std::vector<cocos2d::Vec2> _vertices;

    ShapeModel(Type type) { this->type = type; }

    Type getType() { return type; }

    void close() { _closed = true; }

    bool isClosed() { return _closed; }
};

class PolygonModel : public ShapeModel {

public:
    std::vector<ax::Vec2> vertices;

    PolygonModel() :ShapeModel(Type::POLYGON) {};

    PolygonModel(const std::vector<ax::Vec2>& verts) :ShapeModel(Type::POLYGON) {
        vertices = verts;
    }
};

class CircleModel : public ShapeModel {

public:
    float radius;
    cocos2d::Vec2 centre, rPoint;
};

#endif // __SHAPE_MODEL_H__