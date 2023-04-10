#ifndef __RIGIDBODIESPANEL_UI_H__
#define __RIGIDBODIESPANEL_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//All classes are in the UI domain

class RbToolbarLayout;
class RbEntryLayout;

//Encapsulates whole UI logic of Rigidbodies panel
class RigidbodiesPanelUI : public ax::Node
{
public:
	std::string selectedEntryName;
	std::map<std::string, RbEntryLayout*> _rbLayoutMap;//A map that associates rb name to entry layout
public:
	ax::ui::ListView* _listView;
	cocos2d::ui::Layout* _windowLayout;
	//RBListControl* _rbListController;
	RbToolbarLayout* _rbToolbarLayout;

	std::function<void(std::string)> onAListingClicked;
	std::function<void(std::string)> onASpawnClicked;
public:

    virtual bool init();
    void addOtherUIComponents();
	void update(float dt)override;
	// implement the "static create()" method manually
	CREATE_FUNC(RigidbodiesPanelUI);

	ax::ui::ListView* createTheListView(ax::Size s);

	void setupWithSize(ax::Size size);

	//Entry related
	void addEntry(std::string name);
	void deleteEntry(std::string name);

	//RBListControl* getRbListController() { return _rbListController; }
	void addSpwnBtnListener(std::function<void(std::string)> callback);

private:
	void RigidbodiesPanelUI::onRbEntryClicked(ax::Ref* ref, ax::ui::Widget::TouchEventType touchType);
};

//Rigidbody tool bar layout class
class RbToolbarLayout : public ax::ui::Layout
{
public:
	ax::ui::Button* _addRbBtn;
	ax::ui::Button* _delRbBtn;
	ax::ui::Button* _renRbBtn;

	std::function<void(std::string)> _onClickEventFromButtons; //Sub. to this function listen to toolbar button events.

	CREATE_FUNC(RbToolbarLayout);
	virtual bool init() override;

	void setupWithSize(ax::Size s);

private:
	void onAButtonCallback(ax::Ref*, ax::ui::Widget::TouchEventType);


};

//Layout class for each rigidbodyentry
class RbEntryLayout : public ax::ui::Layout
{
private:
	ax::Label* _bodyNameText;
	ax::ui::ImageView* _rbIcon;
public:
	int id;
	ax::ui::Button* _spwnBtn;
	std::string listingName;
	CREATE_FUNC(RbEntryLayout);

	virtual bool init() override;
	//Initial setup
	void setup(ax::Size size, std::string);

	void enableFocusState(bool enable);
	void enableSpawnBtn(bool en) { _spwnBtn->setVisible(en); }

};

#endif // __RIGIDBODIESPANEL_UI_H__