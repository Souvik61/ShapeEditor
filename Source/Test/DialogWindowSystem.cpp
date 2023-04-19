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
	Size s = _director->getVisibleSize();
	Vec2 o = _director->getVisibleOrigin();
	//Create a new dialog prompt
	_diaPrompt = DialogPrompt::create();
	addChild(_diaPrompt);
	_diaPrompt->setPosition(s.width / 2 + o.x, s.height / 2 + o.y);

	//Link onRenameWinBtnPress to promptWindow btn press
	_diaPrompt->_promptWindow->onAButtonClicked = CC_CALLBACK_1(DialogWindowSystem::onRenameWinBtnPress, this);

}

void DialogWindowSystem::showImgSelectionDialog()
{
	Size s = _director->getVisibleSize();
	Vec2 o = _director->getVisibleOrigin();
	//Create a new dialog prompt
	_diaPrompt = DialogPrompt::create();
	addChild(_diaPrompt);
	_diaPrompt->setPosition(s.width / 2 + o.x, s.height / 2 + o.y);

	//Link onRenameWinBtnPress to promptWindow btn press
	_diaPrompt->_promptWindow->onAButtonClicked = CC_CALLBACK_1(DialogWindowSystem::onRenameWinBtnPress, this);
}

bool DialogWindowSystem::isShowingDialog()
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
	if (onRenameWindowBtnEvent)
		onRenameWindowBtnEvent(s);
}
