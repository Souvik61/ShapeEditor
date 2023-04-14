#ifndef __RBLIST_CONTROL_H__
#define __RBLIST_CONTROL_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class RigidbodiesPanelUI;
class RigidBodiesManager;

//Rigidbodies list controller
//Responsible for syncing RbListUI and RigidbodyManager
class RbListController : public ax::Node
{
public:
	std::string selectedEntryName;
	RigidbodiesPanelUI* rbUI;
	RigidBodiesManager* rbMan;
public:

	virtual bool init() override;
	void onEnter() override;
	CREATE_FUNC(RbListController);

	void syncUIwithRbManager();

	//In spawn mode all spawn buttons of rbentrylayout is enabled
	void enableSpawnMode(bool en);

	void addSpwnBtnListener(std::function<void(std::string)> callback);

	//Events
	void rbSpawnCallback(ax::Ref* ref, ax::ui::Widget::TouchEventType touchType);

	void entryAddedCallback(std::string);
	void entryDeletedCallback(std::string);
	void entrySelectedCallback(std::string);

private:
	std::function<void(std::string)> OnASpawnClicked;

};
#endif//__RBLIST_CONTROL_H__