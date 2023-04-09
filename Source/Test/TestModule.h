#ifndef __TEST_MODULE_H__
#define __TEST_MODULE_H__

#include "cocos2d.h"

//Testing purpose
class TestModule : public ax::Node
{
public:
	ax::DrawNode* ptr;
public:

	bool init() override;
	CREATE_FUNC(TestModule);

	ax::EventListenerMouse* mListener;

	//Mouse callbacks
	void onMouseMove(ax::EventMouse*);
};

#endif // __TEST_MODULE_H__
