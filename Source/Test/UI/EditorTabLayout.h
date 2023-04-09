#ifndef __EDITOR_TAB_LAYOUT_H__
#define __EDITOR_TAB_LAYOUT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//The tab to be used with tab group in editor panel.
class EditorTabLayout : public ax::ui::Layout
{
public: 
	//Holds the viewSize in pixels.
	ax::Size viewSize;
	ax::Label* modeLabel;
public:
	bool init() override;
	CREATE_FUNC(EditorTabLayout);

	void initLayout();

	void addModeDisplay();

};
#endif // __EDITOR_TAB_LAYOUT_H__
