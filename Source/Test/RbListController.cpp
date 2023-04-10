#include "RbListController.h"
#include "Test/RigidBodiesManager.h"
#include "Test/UI/RigidbodiesPanelUI.h"

USING_NS_AX;

//--------------------------------
//RbListController class
//--------------------------------

bool RbListControl::init()
{
    selectedEntryName = "";

    return true;
}

void RbListControl::onEnter()
{
    Node::onEnter();
   
}

void RbListControl::syncUIwithRbManager()
{
    rbUI->clearAllEntries();

    for each (auto var in rbMan->_rbModelsMap)
    {
        rbUI->addEntry(var.first);
    }
}

void RbListControl::enableSpawnMode(bool en)
{
   
}

//Events
