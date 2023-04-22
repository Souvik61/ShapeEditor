#ifndef __B2D_MANAGER_H__
#define __B2D_MANAGER_H__

#include "cocos2d.h"
#include "box2d/include/box2d/box2d.h"

namespace rb {
	class B2WorldNode;
	class B2PhysicsBody;
}

class OverallManager;

//Box2d Manager
class B2DManager
{
public:
	bool isM1Held = false;
	ax::Vec2 camStart, camOffset;
	ax::Vec2 touchStart, prevTouch, origin;
	ax::Size viewSize;
	float camZoom;

	ax::Vec2 m_mouseWorld;
	b2MouseJoint* m_mouseJoint;
	rb::B2PhysicsBody* m_groundBody;
	rb::B2WorldNode* wN;
	ax::Camera* b2Cam;
	OverallManager* oManager;

	ax::Sprite* spawnPointSp;
public:
	B2DManager();

	ax::Vec2 convertTouchToWorld(const ax::Vec2& v) { return v + camOffset; };

	ax::Vec2 convertTouchToWorldNew(const ax::Vec2& v) 
	{ 
		ax::Vec3 a = b2Cam->unprojectGL(ax::Vec3(v.x, v.y, 0));
		return ax::Vec2(a.x, a.y);
	};

	//Mouse Inputs
	void onMouseDown(ax::EventMouse* event);
	void onMouseMove(ax::EventMouse* event);
	void onMouseUp(ax::EventMouse* event);
	void onMouseScroll(ax::EventMouse* event);

	//Act/Deact
	void activateWorld();
	void deactivateWorld();

	//Remove all physics bodies
	void clearWorld();

};

#endif // __B2D_MANAGER_H__
