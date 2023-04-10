#include "RbListController.h"

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

void RbListControl::enableSpawnMode(bool en)
{
   
}

//Events
