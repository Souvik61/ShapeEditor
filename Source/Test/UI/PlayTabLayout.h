#ifndef __PLAY_TAB_LAYOUT_H__
#define __PLAY_TAB_LAYOUT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class B2DManager;
class PlayTabCtrlPanel;

//The tab to be used with tab group in editor panel.
class PlayTabLayout : public ax::ui::Layout
{
public:
	bool isM1Held;
	ax::Vec2 touchStart, prevTouch, origin;
	ax::Size viewSize;
	ax::EventListenerMouse* mListen;
	B2DManager* bManager;
	ax::Sprite* spawnPointer;

	PlayTabCtrlPanel* pCtrlPanel;
public:
	bool init() override;
	CREATE_FUNC(PlayTabLayout);

	void initLayout();

	//Callbacks


	//test

	ax::Vec2 convertTouchToWorld(const ax::Vec2& inp)
	{
		return inp;
	}

};

//A layout class for physics world control panel
class PlayTabCtrlPanel : public ax::ui::Layout 
{
public:
	std::function<void(std::string)> eOnButtonPress;
public:
	bool init() override;
	CREATE_FUNC(PlayTabCtrlPanel);

	//void initLayout();

	//Called when a button is pressed on the panel with btnname passed as argument
	void onAKeyPressed(std::string);

};

#endif // __PLAY_TAB_LAYOUT_H__
