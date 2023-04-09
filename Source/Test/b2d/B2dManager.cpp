#include "B2dManager.h"
#include "Phys/B2_WorldNode.h"
#include "Phys/B2_PhysicsBody.h"
#include "Test/b2d/B2dMisc.h"
#include "Test/OverallManager.h"

USING_NS_CC;

B2DManager::B2DManager() :m_mouseJoint(nullptr)
{
    camZoom = 1;
}

//Events

void B2DManager::onMouseDown(EventMouse* event)
{
    //Camera panning
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        isM1Held = true;
        prevTouch = touchStart = event->getLocationInView();
    }

    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        //Pick objects

        //auto p = convertTouchToWorld(event->getLocationInView());

        Vec2 a = event->getLocationInView();
        Vec3 b = b2Cam->unprojectGL(Vec3(a.x, a.y, 0));

        Vec2 p(b.x, b.y);

        m_mouseWorld = p;

        if (m_mouseJoint != NULL)
        {
            return;
        }

        // Make a small box.
        b2AABB aabb;
        Vec2 d = Vec2(0.1, 0.1);
        aabb.lowerBound = wN->convertToB2Vector(p - d);
        aabb.upperBound = wN->convertToB2Vector(p + d);

        // Query the world for overlapping shapes.
        QueryCallback callback(wN->convertToB2Vector(p));

        wN->getB2World()->QueryAABB(&callback, aabb);

        if (callback.m_fixture)
        {
            float frequencyHz = 5.0f;
            float dampingRatio = 0.7f;

            b2Body* body = callback.m_fixture->GetBody();
            b2MouseJointDef jd;
            jd.bodyA = m_groundBody->getBox2dBody();
            jd.bodyB = body;
            jd.target = wN->convertToB2Vector(p);
            jd.maxForce = 100.0f * body->GetMass();//1000

            b2LinearStiffness(jd.stiffness, jd.damping, frequencyHz, dampingRatio, jd.bodyA, jd.bodyB);

            m_mouseJoint = (b2MouseJoint*)wN->getB2World()->CreateJoint(&jd);
            body->SetAwake(true);
        }
    }
}

void B2DManager::onMouseMove(EventMouse* event)
{
     //Touch handling
    Vec2 dir, delta;
    if (isM1Held)
    {
        delta = prevTouch - event->getLocationInView();

        b2Cam->setPosition(b2Cam->getPosition() + (delta * (1 / camZoom)));
        camOffset = b2Cam->getPosition() - camStart;
        prevTouch = event->getLocationInView();
    }

    //spawnPointSp->setPosition(-camOffset);

    //mouse joint move
    //Vec2 p = convertTouchToWorld(event->getLocationInView());
    
    Vec2 a = event->getLocationInView();
    Vec3 p = b2Cam->unprojectGL(Vec3(a.x, a.y, 0));

    m_mouseWorld.set(p.x, p.y);

    if (m_mouseJoint)
    {
        m_mouseJoint->SetTarget(CCTOB2VEC2(p));
    }
}

void B2DManager::onMouseUp(EventMouse* event)
{
    //Touch handling
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
        isM1Held = false;

    //Mouse joint code
    if (m_mouseJoint)
    {
        wN->getB2World()->DestroyJoint(m_mouseJoint);
        m_mouseJoint = NULL;
    }
}

void B2DManager::onMouseScroll(EventMouse* event)
{
    Size s = Director::getInstance()->getWinSize();

    (event->getScrollY() < 0) ? camZoom *= 1.1f : camZoom /= 1.1f;
    camZoom = clampf(camZoom, 0.1f, 10.0f);
    b2Cam->initOrthographic(s.width * (1 / camZoom), s.height * (1 / camZoom), 1, 1000);
}

//Others

void B2DManager::activateWorld()
{
    wN->pauseWorld(false);
    b2Cam->setVisible(true);
}

void B2DManager::deactivateWorld()
{
    b2Cam->setVisible(false);
    wN->pauseWorld(true);
}

void B2DManager::clearWorld()
{
    //Destroy all bodies except the ground

    auto world = wN->getB2World();
    
    auto it = world->GetBodyList();
    int n = world->GetBodyCount();
    for (int i = 0; i < n; i++)
    {
        auto a = it;
        it = it->GetNext();
        auto rm = reinterpret_cast<rb::B2PhysicsBody*>(a->GetUserData().pointer);
        
        if (rm->getOwner() && rm->getOwner()->getName() == "ground")
            continue;
       

        if (rm->getOwner())
            rm->getOwner()->removeFromParent();
        
    }

    oManager->uiSystem->notifSys->showNotification("All bodies removed.");

}
