#include "OverallManager.h"

USING_NS_CC;

OverallManager::OverallManager()
{
	prjManager = new ProjectManager();
	rbManager = new RigidBodiesManager();
	//uiInManager = new UIInputManager();
	//uiInManager->oManager = this;
	//eventManager = new EventManager();
	//eventManager->oManager = this;
	prjManager = new ProjectManager();
	prjManager->jIOSystem->setOverallManager(this);
}

void OverallManager::init()
{
	_inited = true;
}

