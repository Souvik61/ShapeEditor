#include "StateTracker.h"
#include "OverallManager.h"
#include "RigidBodiesManager.h"
#include "Test/models/RigidBodyModel.h"

bool StateTracker::isSaveDirty()
{
	for (auto i : rbManager->_rbModelsMap) {

		//CCLOG("%s", i.first.c_str());

		if (i.second->_isSaveDirty)
			return true;
	}
	return false;
}

void StateTracker::setAllModelClean()
{
	for (auto i : rbManager->_rbModelsMap) {

		i.second->setSaveDirty(false);
	}
}
