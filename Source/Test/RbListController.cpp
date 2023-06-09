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

    syncToolbarWithRbManager();

}

void RbListController::syncToolbarWithRbManager()
{
    rbUI->_rbToolbarLayout->_addRbBtn->setEnabled(rbMan->inState.canAdd);
    rbUI->_rbToolbarLayout->_delRbBtn->setEnabled(rbMan->inState.canDelete);
    rbUI->_rbToolbarLayout->_renRbBtn->setEnabled(rbMan->inState.canRename);
}

void RbListController::enableSpawnMode(bool en)
{
    //Enable spawn mode for UI
    rbUI->enableSpawnModeUI(en);
}

void RbListController::addSpwnBtnListener(std::function<void(std::string)> callback)
{
    OnASpawnClicked = callback;
}

void RbListController::addImgBtnListener(std::function<void(std::string)> callback)
{
    OnAImgClicked = callback;
}

void RbListController::rbSpawnCallback(Ref* ref, ui::Widget::TouchEventType touchType)
{
    if (touchType == ui::Widget::TouchEventType::ENDED)
    {
        auto t = dynamic_cast<ui::Button*>(ref);
        auto t1 = static_cast<RbEntryLayout*>(t->getUserData());
        //t->removeFromParent();
        if (OnASpawnClicked)
            OnASpawnClicked(t1->listingName);
    }
}

void RbListController::rbImgCallback(Ref* ref, ui::Widget::TouchEventType touchType)
{
    if (touchType == ui::Widget::TouchEventType::ENDED)
    {
        auto t = dynamic_cast<ui::Button*>(ref);
        auto t1 = static_cast<RbEntryLayout*>(t->getUserData());
        if (OnAImgClicked)
            OnAImgClicked(t1->listingName);
    }
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
    rbUI->selectEntry(s);
}

void RbListController::rbManagerStateChangeCallback()
{
    rbUI->_rbToolbarLayout->_addRbBtn->setEnabled(rbMan->inState.canAdd);
    rbUI->_rbToolbarLayout->_delRbBtn->setEnabled(rbMan->inState.canDelete);
    rbUI->_rbToolbarLayout->_renRbBtn->setEnabled(rbMan->inState.canRename);
}