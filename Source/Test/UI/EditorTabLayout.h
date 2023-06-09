#ifndef __EDITOR_TAB_LAYOUT_H__
#define __EDITOR_TAB_LAYOUT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//The tab to be used with tab group in editor panel.
class EditorTabLayout : public ax::ui::Layout
{
public: 
	//Holds the viewport size in pixels.
	ax::Size viewSize;
	ax::Label* modeLabel;
	ax::RenderTexture* _rend;
	//Render texture renderer sprite
	ax::Sprite* renderSprite;
	//A place holder that will sit in the place of renderSprite because reasons
	ax::Node* viewPlaceholder;
public:
	bool init() override;
	CREATE_FUNC(EditorTabLayout);

	//set this node's contentSize() and then call this function to auto adjust layout view 
	void initLayout();

	void addModeDisplay();

};
#endif // __EDITOR_TAB_LAYOUT_H__
