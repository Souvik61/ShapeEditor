#include "RbListController.h"
#include "Test/RigidBodiesManager.h"
#include "Test/UI/RigidbodiesPanelUI.h"

USING_NS_AX;

//--------------------------------
//RbListController class
//--------------------------------

bool RbListController::init()
{
    selectedEntryName = "";

    return true;
}

void RbListController::onEnter()
{
    Node::onEnter();
   
}

void RbListController::syncUIwithRbManager()
{
    rbUI->clearAllEntries();

    for each (auto var in rbMan->_rbModelsMap)
    {
        rbUI->addEntry(var.first);
    }
}

void RbListController::enableSpawnMode(bool en)
{
   
}

//----------
//Events
//----------

//-------------------------------------
//Callbacks from Rigidbodies Manager
//-------------------------------------


void RbListController::entryAddedCallback(std::string s)
{
    rbUI->addEntry(s);
}

void RbListController::entryDeletedCallback(std::string s)
{
    rbUI->deleteEntry(s);
}

void RbListController::entrySelectedCallback(std::string s)
{
    //////////////////////////////
}
