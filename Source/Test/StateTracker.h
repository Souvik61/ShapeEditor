#ifndef __STATE_TRACKER_H__
#define __STATE_TRACKER_H__

#include "cocos2d.h"

class OverallManager;
class RigidBodiesManager;

//Responsible for tracking file save status of the rigidbodies
class StateTracker
{
public:
	OverallManager* oManager;
	RigidBodiesManager* rbManager;

public:
	//If the project needs to be saved ie. unsaved changes remain
	bool isSaveDirty();
	//Wht it is here?
	void setAllModelClean();
};

#endif // __STATE_TRACKER_H__
