#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include "cocos2d.h"
#include "UtilityClasses.h"

USING_NS_CC;

class DialogWindowSystem;
class OverallManager;
class ProjectPanelUI;

class EventManager : public ax::Node
{

public:
	enum State { NONE, WAIT_FOR_ADD, WAIT_FOR_REN, WAIT_FOR_IMG };
public:
	State currentState;

	ProjectPanelUI* panelUI;
	OverallManager* oManager;
	DialogWindowSystem* _dialogSystem;

	EventManager();

	bool init() override;
	void update(float dt) override;
	void onEnter() override; //On enter
	void onExit() override; //On exit
	CREATE_FUNC(EventManager);

	void setDialogWindowSystem(DialogWindowSystem* dS);

	//Events

	//Rbpanel button callbacks --start

	void onButtonPressFromRbPanel(std::string);
	void onAListingClickedFromRbPanel(std::string n);
	void onSpwnButtonFromRbPanel(std::string n);
	void onImgButtonFromRbPanel(std::string n);
	//Rbpanel individual button
	void onAddButtonPressedOnRbPanel();
	void onDelButtonPressedOnRbPanel();
	void onRenButtonPressedOnRbPanel();
	
	//Rbpanel button callbacks --end
	
	//Project panel events

	//On button pressed from project panel
	void onBtnPressedFromPrjPanel(std::string btnName);
	//On Save button pressed on ProjectPanel
	void onSaveBtnPressed();
	//On Load button pressed on ProjectPanel
	void onLoadBtnPressed();
	//On New button pressed on ProjectPanel
	void onNewBtnPressed();
	//Function to be called when openinexplorer button is pressed
	void onOpenInExplorer();

	//Project panel events -end

	//Dialog window events
	void onBtnPressFromWindow(std::string);
	void onRenameOkBtnPress();
	void onRenameCancelBtnPress();

	//ImageSelectWindow Events
	void onBtnPressFromImgSelectWindow(std::string);
	void onImgSelectBrowseBtnPress();
	void onImgSelectClearBtnPress();
	void onImgSelectOkBtnPress();

	//On tab changed event
	void onTabChanged(int index);

	//PlayTab Control Panel events
	 
	//When any button on playtab control panel is pressed 
	void onPlayTabCtrlEvent(std::string);

	//Core events

	//Called when the windows close button is pressed
	void onWinCloseBtnPressed();

	void onShowRenameDialog();
	void onHideRenameDialog();

	void onNewProject();
	void onSaveToDisk();
	void onLoadFromDisk();

	void addRbEntry();
	void renRbEntry();

	//Others

	//Procedure for "Do you want to save?" Message box
	int savePromptRoutine();

private:
	ax::EventListenerCustom* _listener;

};
#endif // __EVENT_MANAGER_H__
