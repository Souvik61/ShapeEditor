#include "CamDelegate.h"

USING_NS_AX;

bool CamDelegate::init()
{
    if (!Camera::init())
    {
        return false;
    }

    return true;
}

void CamDelegate::setVisitingCamera(ax::Camera* cam)
{
    Camera::_visitingCamera = cam;
}
