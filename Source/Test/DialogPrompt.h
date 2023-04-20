#ifndef __DIALOG_PROMPT_H__
#define __DIALOG_PROMPT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//        /*Visible Size*/
// _______________________________
//| /*Dialog Prompt               |
//|       _________________       |
//|      |                 |      |
//|      |/*Dialog Window*/|      |
//|      |                 |      |
//|      |                 |      |
//|      |_________________|      |
//|                               |
//|_______________________________|


//Base Layout class of Dialog Window
class DialogWindowBase : public ax::ui::Layout
{


};

//The prompt window layout itself.
//Its name should be RenameDialogWindow
class DialogPromptWindow : public DialogWindowBase
{
	ax::EventListenerTouchOneByOne* _tListener;
public:

	ax::ui::Text* _windowNameTextField;
	ax::ui::TextField* _textField;
	ax::ui::ImageView* _tipImg;
	ax::ui::Text* tipText;//Warning text
	std::function<void(std::string)> OnAButtonClicked; //Listen to this event for button press event

	virtual bool init() override;
	CREATE_FUNC(DialogPromptWindow);
	void runPromptAnim();

	//Set window display name
	void setWindowName(std::string n);
	void showWarning(std::string warning);
	void hideWarning() { _tipImg->setVisible(false); tipText->setVisible(false); }

	//Events
	void onButtonClicked(ax::Ref*, ax::ui::Widget::TouchEventType);
	bool onTouchBegan(ax::Touch*, ax::Event*);
};

//Image select windows
class ImageSelectDialogWindow : public DialogWindowBase
{
	ax::EventListenerTouchOneByOne* _tListener;
public:
	ax::ui::Text* _windowNameTextField;
	ax::ui::Text* pathTextDisplay;
	std::function<void(std::string)> OnAButtonClicked; //Listen to this event for button press event

	virtual bool init() override;
	CREATE_FUNC(ImageSelectDialogWindow);
	void runPromptAnim();

	//Events
	void onButtonClicked(ax::Ref*, ax::ui::Widget::TouchEventType);
	bool onTouchBegan(ax::Touch*, ax::Event*);

};

//Dialog prompt (encapsualtor)
//This fills entire screen
//It is the SceneGraph parent of DialogPromptWindow
class DialogPrompt : public ax::Node
{
public:
	//Current displaying dialog window
	DialogWindowBase* dialogWindow;

	ax::EventListenerTouchOneByOne* _tListener;
	virtual bool init() override;
	CREATE_FUNC(DialogPrompt);

	//Events
	bool onTouchBegan(ax::Touch*, ax::Event*);
};

#endif // __DIALOG_PROMPT_H__
