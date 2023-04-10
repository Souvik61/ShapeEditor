#ifndef __RBLIST_CONTROL_H__
#define __RBLIST_CONTROL_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class RigidbodiesPanelUI;
class RigidBodiesManager;

//Rigidbodies list controller
//Responsible for syncing RbListUI and RigidbodyManager
class RbListControl : public ax::Node
{
	std::string selectedEntryName;
public:

	virtual bool init() override;
	void onEnter() override;
	CREATE_FUNC(RbListControl);

	//In spawn mode all spawn buttons of rbentrylayout is enabled
	void enableSpawnMode(bool en);

	void addSpwnBtnListener(std::function<void(std::string)> callback);

	//Events

};
#endif//__RBLIST_CONTROL_H__