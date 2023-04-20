#include "DialogWindowSystem.h"
//#include "Helpers.h"

USING_NS_CC;

//--------------------------------
//Dialog Window system
//--------------------------------

bool DialogWindowSystem::init()
{
	_diaPrompt = nullptr;
	return true;
}

void DialogWindowSystem::showRenameDialog()
{
	if (isShowingADialog()) return;

	Size s = _director->getVisibleSize();
	Vec2 o = _director->getVisibleOrigin();

	//Create a new dialog prompt
	_diaPrompt = DialogPrompt::create();
	addChild(_diaPrompt);
	_diaPrompt->setPosition(s.width / 2 + o.x, s.height / 2 + o.y);
	//Create a new window
	auto dialogWindow = DialogPromptWindow::create();
	_diaPrompt->addChild(dialogWindow, 1);
	dialogWindow->setPosition(_diaPrompt->getContentSize() / 2);
	//Link onRenameWinBtnPress to promptWindow btn press
	dialogWindow->OnAButtonClicked = CC_CALLBACK_1(DialogWindowSystem::onRenameWinBtnPress, this);

}

void DialogWindowSystem::showImgSelectionDialog()
{
	if (isShowingADialog()) return;

	Size s = _director->getVisibleSize();
	Vec2 o = _director->getVisibleOrigin();
	//Create a new dialog prompt
	_diaPrompt = DialogPrompt::create();
	addChild(_diaPrompt);
	_diaPrompt->setPosition(s.width / 2 + o.x, s.height / 2 + o.y);

	//Create Image select window
	auto dialogWindow = ImageSelectDialogWindow::create();
	_diaPrompt->addChild(dialogWindow, 1);
	dialogWindow->setPosition(_diaPrompt->getContentSize() / 2);
	//Link onRenameWinBtnPress to promptWindow btn press
	dialogWindow->OnAButtonClicked = CC_CALLBACK_1(DialogWindowSystem::onImgSelWinBtnPress, this);
}

bool DialogWindowSystem::isShowingADialog()
{
	return _diaPrompt != nullptr;
}

void DialogWindowSystem::closeDialog()
{
	removeChild(_diaPrompt);
	_diaPrompt = nullptr;
}

void DialogWindowSystem::closeRenameDialog()
{
	removeChild(_diaPrompt);
	_diaPrompt = nullptr;
}

DialogPrompt* DialogWindowSystem::getCurrentDialog()
{
	return _diaPrompt;
}

void DialogWindowSystem::onRenameWinBtnPress(std::string s)
{
	if (OnRenameWindowBtnEvent)
		OnRenameWindowBtnEvent(s);
}

void DialogWindowSystem::onImgSelWinBtnPress(std::string s)
{
	if (OnImgWindowBtnEvent)
		OnImgWindowBtnEvent(s);
}
