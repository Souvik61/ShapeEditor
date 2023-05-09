#include "SpawnManager.h"
#include "Phys/B2_WorldNode.h"
#include "Phys/B2_PhysicsBody.h"
#include "Test/b2d/B2dMisc.h"
#include "Test/RigidBodiesManager.h"
#include "Test/models/RigidBodyModel.h"
#include "Test/models/ShapeModel.h"
#include "Phys/DefHelper.h"
#include "Phys/ShapeHelper.h"

USING_NS_CC;
using namespace rb;

bool SpawnManager::spawnBody(std::string name, ax::Vec2 pos)
{
	//If we try to spawn below ground prevent it
	if (pos.y < 0)
	{
		pos.y = 10;
	}

	//Get model
	auto rbModel = rbManager->getModel(name);

	if (rbModel->_isPhysDirty)
		rbModel->computePhysics();//Refresh polygon shapes

	if (!rbModel->_shapesValid)
		return false;

	//Create a rigidbody
	B2PhysicsBody* rB = createBodyFromModelwithOrigin(rbModel, pos);

	auto n = Node::create();
	n->addComponent(rB);
	runningScene->addChild(n);

	//Testing
	//auto l = DrawNode::create();
	//l->setCameraMask((unsigned short)CameraFlag::USER1);
	//l->drawDot(Vec2::ZERO, 10, Color4B::RED);
	//l->setPosition(pos);
	//runningScene->addChild(l, 100);

	return true;
}

//rb::B2PhysicsBody* SpawnManager::createBodyFromModel(RigidBodyModel* model, Vec2 pos)
//{
//	b2BodyDef def;
//	DefHelper::initWithPos(def, pos);
//	def.type = b2_dynamicBody;//create dynamic body
//	auto body = wN->createPhysicsBodyComp(def);
//
//
//	//For each shape in model
//	for (auto shape : model->_shapes) {
//
//		int s = shape->_vertices.size();
//		Vec2* verts = new Vec2[s];
//		fillArray(verts, shape->_vertices, s);
//
//		b2PolygonShape shape1;
//		ShapeHelper::initPolygonShapeWithVerts(shape1, verts, s);
//
//		body->createFixture(&shape1, 1);
//
//	}
//	return body;
//}

rb::B2PhysicsBody* SpawnManager::createBodyFromModel(RigidBodyModel* model, Vec2 pos)
{
	b2BodyDef def;
	DefHelper::initWithPos(def, pos);
	def.type = b2_dynamicBody;//create dynamic body
	auto body = wN->createPhysicsBodyComp(def);


	//For each polygons in model
	for (auto poly : model->_polygons) {

		int s = poly->vertices.size();
		Vec2* verts = new Vec2[s];
		fillArray(verts, poly->vertices, s);

		if (getPolygonArea(verts, s) < 0.00001f)
			continue;

		b2PolygonShape shape1;
		ShapeHelper::initPolygonShapeWithVerts(shape1, verts, s);

		body->createFixture(&shape1, 1);

	}
	return body;
}

rb::B2PhysicsBody* SpawnManager::createBodyFromModelwithOrigin(RigidBodyModel* model, ax::Vec2 pos)
{
	b2BodyDef def;
	DefHelper::initWithPos(def, pos);
	def.type = b2_dynamicBody;//create dynamic body
	auto body = wN->createPhysicsBodyComp(def);


	//For each polygons in model
	for (auto poly : model->_polygons) {

		int s = poly->vertices.size();
		Vec2* verts = new Vec2[s];

		//fillArray(verts, poly->vertices, s);
		fillArrayWithOriginOffset(verts, poly->vertices, s, model->getOrigin());

		if (getPolygonArea(verts, s) < 0.00001f)
			continue;

		b2PolygonShape shape1;
		ShapeHelper::initPolygonShapeWithVerts(shape1, verts, s);

		body->createFixture(&shape1, 1);

	}
	return body;
}

void SpawnManager::fillArray(ax::Vec2 dest[], std::vector<ax::Vec2> src, int size)
{
	for (int i = 0; i < size; i++) {
		dest[i].set(src.at(i));
	}
}

void SpawnManager::fillArrayWithOriginOffset(ax::Vec2 dest[], std::vector<ax::Vec2> src, int size, const Vec2& origin)
{
	for (int i = 0; i < size; i++) {
		dest[i].set(src.at(i) - origin);
	}
}

float SpawnManager::getPolygonArea(ax::Vec2 points[], int s)
{
	return abs(getPolygonSignedArea(points, s));;
}

float SpawnManager::getPolygonSignedArea(Vec2 points[], int s) {
	if (s < 3)
		return 0;

	float sum = 0;
	for (int i = 0; i < s; i++) {
		Vec2 p1 = points[i];
		Vec2 p2 = i != s - 1 ? points[i + 1] : points[0];
		sum += (p1.x * p2.y) - (p1.y * p2.x);
	}
	return 0.5f * sum;
}
