#ifndef __UTILITY_CLASSES_H__
#define __UTILITY_CLASSES_H__

#include <iostream>
#include <vector>
#include "math/Vec2.h"

class Shape;
namespace ax { class EventMouse; }

struct RBInfo {
	std::string name;
	std::vector<Shape*> shapeList;
};

struct CustomMouseEvent {

    enum class EventType
    {
        DOWN, MOVED, UP
    };

    EventType type;
    ax::EventMouse* mEvent;
    ax::Vec2 alignedPos;

};

// Editor modes
// VIEW-> Only Viewing(Zooming,Panning)
// CREATE-> Viewing+Adding Vertices
// EDIT-> Viewing+Moving Vertices+Delete Verts
// TEST-> Drag&Drop bodies in physics world
enum EditorMode { VIEW, CREATE, EDIT, TEST };    

#endif