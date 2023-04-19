#ifndef __DIALOG_PROMPT_H__
#define __DIALOG_PROMPT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

//        /*Visible Size*/
// _______________________________
//| /*Dialog Prompt               |
//|       _________________       |
//|      |                 |      |
//|      |/*Dialog Prompt*/|      |
//|      |/*Window*/       |      |
//|      |                 |      |
//|      |_________________|      |
//|                               |
//|_______________________________|


//The prompt window layout itself.
class DialogPromptWindow : public ui::Layout
{
	EventListenerTouchOneByOne* _tListener;
public:
	ui::TextField* _textField;
	ui::ImageView* _tipImg;
	ui::Text* tipText;//Warning text
	std::function<void(std::string)> onAButtonClicked; //Listen to this event for button press event

	virtual bool init() override;
	CREATE_FUNC(DialogPromptWindow);
	void runPromptAnim();

	void showWarning(std::string warning);
	void hideWarning() { _tipImg->setVisible(false); tipText->setVisible(false); }

	//Events
	void onButtonClicked(Ref*, Widget::TouchEventType);

	bool onTouchBegan(Touch*, Event*);
};

//Dialog prompt
//This fills entire screen
//It is the SceneGraph parent of DialogPromptWindow
class DialogPrompt : public cocos2d::Node
{
public:
	DialogPromptWindow* _promptWindow;

	EventListenerTouchOneByOne* _tListener;
	virtual bool init() override;
	CREATE_FUNC(DialogPrompt);

	//Events
	bool onTouchBegan(Touch*, Event*);
};

#endif // __DIALOG_PROMPT_H__
