#ifndef __CAM_DELEGATE_H__
#define __CAM_DELEGATE_H__

#include "axmol.h"

//A helper class to hack visitingCamera in the Camera class
class CamDelegate : public ax::Camera
{
public:
	bool init() override;
	CREATE_FUNC(CamDelegate);

	void setVisitingCamera(ax::Camera* cam);
};

#endif  // __CAM_DELEGATE_H__
