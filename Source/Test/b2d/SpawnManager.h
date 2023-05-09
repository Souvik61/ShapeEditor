#ifndef __SPAWN_MANAGER_H__
#define __SPAWN_MANAGER_H__

#include "cocos2d.h"
#include "box2d/include/box2d/box2d.h"

namespace rb {
	class B2WorldNode;
	class B2PhysicsBody;
}

class RigidBodiesManager;
class RigidBodyModel;

//Spawn Manager
//Responsible for spawning and deleting items from b2d world
class SpawnManager
{
public:
	rb::B2WorldNode* wN;
	RigidBodiesManager* rbManager;
	ax::Scene* runningScene;
public:

	//Spawn a physics body with given name at position pos in global space
	//Return true if success else false
	bool spawnBody(std::string name, ax::Vec2 pos);

	rb::B2PhysicsBody* createBodyFromModel(RigidBodyModel* model, ax::Vec2 pos);
	rb::B2PhysicsBody* createBodyFromModelwithOrigin(RigidBodyModel* model, ax::Vec2 pos);

private:
	//A helper
	void fillArray(ax::Vec2 dest[], std::vector<ax::Vec2> src, int size);
	void fillArrayWithOriginOffset(ax::Vec2 dest[], std::vector<ax::Vec2> src, int size,const ax::Vec2& origin);
	//A function to calculate polygon area
	float getPolygonArea(ax::Vec2[], int s);
	float getPolygonSignedArea(ax::Vec2 points[], int s);
};

#endif // __SPAWN_MANAGER_H__
