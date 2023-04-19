#ifndef __DIALOG_WINDOW_SYSTEM_H__
#define __DIALOG_WINDOW_SYSTEM_H__

#include "cocos2d.h"
#include "DialogPrompt.h"

//Responsible for the prompt window system
//Use this class to show different dialogs
class DialogWindowSystem : public ax::Node
{
public:
	std::function<void(std::string)> onRenameWindowBtnEvent;
	
public:
	DialogPrompt* _diaPrompt;

	bool init() override;
	CREATE_FUNC(DialogWindowSystem);

	//Different Dialog windows

	void showRenameDialog();
	void showImgSelectionDialog();
	
	bool isShowingDialog();
	void closeDialog();
	//will be deprecated soon
	void closeRenameDialog();
	
	DialogPrompt* getCurrentDialog();
	void onRenameWinBtnPress(std::string);

};

#endif // __DIALOG_WINDOW_SYSTEM_H__
