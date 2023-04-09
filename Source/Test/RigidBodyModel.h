#ifndef __RIGIDBODY_MODEL_H__
#define __RIGIDBODY_MODEL_H__

#include "cocos2d.h"
#include "ShapeModel.h"

using namespace std;
USING_NS_CC;

class ShapeModel;
class PolygonModel;
class CircleModel;

class RigidBodyModel : public Ref
{
public:
    std::string PROP_NAME = "name";
    std::string PROP_IMAGEPATH = "imagePath";
    std::string PROP_PHYSICS = "physics";

    Vec2 origin;
    Vector<ShapeModel*> _shapes;
    Vector<PolygonModel*> _polygons;
    Vector<CircleModel*> _circles;
    string name = "unamed";
    string imagePath;
    bool _imgPathValid = true;
    bool _shapesValid = false;//Flag to tell if shapes are valid polygons

    bool _isPhysDirty;//Flag to track if physics shape are dirty, if dirty computePhysics
    bool _isSaveDirty;//Flag to track if this rigidbody is saved

    CREATE_FUNC(RigidBodyModel);

    bool init();

    Vec2 getOrigin() { return origin; }

    void setName(string name) {
        this->name = name;
    }

    string getName() { return name; }

    void setImagePath(string imagePath) {
        //this->imagePath = imagePath;
        //this->isImagePathValid = imagePath == null ? true : Ctx.io.getImageFile(imagePath).isFile();
    }

    string getImagePath() { return imagePath; }

    bool isImagePathValid() { return _imgPathValid; }

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
