#ifndef __OVERALL_MANAGER_H__
#define __OVERALL_MANAGER_H__

#include "cocos2d.h"
#include "Globals.h"
#include "ProjectManager.h"
#include "RigidBodiesManager.h"
//#include "UIInputManager.h"
#include "EventManager.h"
#include "DialogWindowSystem.h"
#include "JsonIoSystem.h"
#include "UISubsystem.h"
//#include "ProjectPanel.h"
#include "EditorManager.h"
#include "PointBuffer.h"
#include "PointArrayDelegate.h"
#include "Test/b2d/B2dManager.h"
#include "Test/SpaceConverter.h"
#include "Test/b2d/SpawnManager.h"
#include "StateTracker.h"
//patch
#include "draw/BackGrid.h"


//It is like the main context of this program.
class OverallManager
{
	bool _inited;
public:
	//Project manager(not used)
	ProjectManager* prjManager;
	//Project save system as well as a panel
	//ProjectPanel* prjPanelSys;
	//Rigidbodies manager
	RigidBodiesManager* rbManager;
	//UIInput Manager
	//UIInputManager* uiInManager;
	//Event manager
	EventManager* eventManager;
	//Dialog window manager
	DialogWindowSystem* dialogWindowSystem;
	//Editor Window(System)
	EditorPanel* editorPanel;
	//State Tracker for saves
	StateTracker* sTracker;
	//JsonIo System
	JsonIoSystem* jsonIo;
	//UI Subsystem
	UISubsystem* uiSystem;
	//Editor Subsystem
	EditorManager* editSystem;
	//Point Buffer
	PointBuffer* pointBuffer;
	//Point Buffer Delegate
	PointArrayDelegate * buffDelegate;
	//Box2d Manager
	B2DManager* b2dManager;
	//Spawn Manager
	SpawnManager* spwnManager;
	//Coordinate spaces converter
	SpaceConverter* spaceConv;

	//Patch!!
	BackGrid* backGrid;

public:
	OverallManager();
	//Call this function after all core modules are inited and assigned.
	void init();
};

#endif // __OVERALL_MANAGER__
