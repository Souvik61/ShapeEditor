#ifndef __DIALOG_WINDOW_SYSTEM_H__
#define __DIALOG_WINDOW_SYSTEM_H__

#include "cocos2d.h"
#include "DialogPrompt.h"

USING_NS_CC;

//Responsible for the prompt window system
class DialogWindowSystem : public Node
{
public:
	std::function<void(std::string)> onRenameWindowBtnEvent;
	
public:
	DialogPrompt* _diaPrompt;

	bool init() override;
	CREATE_FUNC(DialogWindowSystem);

	void showRenameDialog();
	bool isShowingDialog();
	void closeRenameDialog();
	DialogPrompt* getCurrentDialog();
	void onRenameWinBtnPress(std::string);

};

#endif // __DIALOG_WINDOW_SYSTEM_H__
