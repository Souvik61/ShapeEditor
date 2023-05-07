#ifndef __RIGIDBODY_MODEL_H__
#define __RIGIDBODY_MODEL_H__

#include "cocos2d.h"
#include "ShapeModel.h"

class ShapeModel;
class PolygonModel;
class CircleModel;

class RigidBodyModel : public ax::Ref
{
public:
    ax::Vec2 originPoint;
    ax::Vector<ShapeModel*> _shapes;
    ax::Vector<PolygonModel*> _polygons;
    ax::Vector<CircleModel*> _circles;
    std::string name = "unamed";

    std::string imagePath;
    bool _shapesValid = false;//Flag to tell if shapes are valid polygons

    bool _isPhysDirty;//Flag to track if physics shape are dirty, if dirty computePhysics
    bool _isSaveDirty;//Flag to track if this rigidbody is saved

    CREATE_FUNC(RigidBodyModel);

    bool init();

    ax::Vec2 getOrigin() { return originPoint; }
    ax::Vec2* getOriginPtr() { return &originPoint; }

    void setName(std::string name) {
        this->name = name;
    }

    std::string getName() { return name; }

    void setImagePath(std::string imagePath);

    std::string getImagePath() { return imagePath; }

    bool isImagePathValid();

    void clear() {
        _shapes.clear();
        _polygons.clear();
        _circles.clear();
    }

    void clearPhysics() {
        _polygons.clear();
        _circles.clear();
    }

    void computePhysics();

    //Dirty flags

    void setSaveDirty(bool val) { _isSaveDirty = val; };


};
#endif // __RIGIDBODY_MODEL_H__
