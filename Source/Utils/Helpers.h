#ifndef __HELPERS_H__
#define __HELPERS_H__

#include "cocos2d.h"

//Helper Class contains few helper functions and variables
class Helper 
{
public:

	//Arduino map function
	static float map(float value, float fromLow, float fromHigh, float  toLow, float toHigh);

	static void makeBound(cocos2d::Node* node, cocos2d::Color4F borderColor = cocos2d::Color4F::RED)
	{
		ax::Size s = node->getContentSize();
		s = (s.equals(ax::Size::ZERO)) ? ax::Size(100, 100) : s;
		auto rectNode = ax::DrawNode::create();
		rectNode->drawRect(ax::Vec2::ZERO, s, borderColor);
		node->addChild(rectNode, 999999);
	}

	/*Converts seconds(int) to hour:minutes:seconds*/
	static std::string timeToString(unsigned int timeInSeconds)
	{
		std::string output;

		int hours = (timeInSeconds / 3600);
		if (hours)
		{
			output += std::to_string(hours) + "h:";
		}

		int minutes = (timeInSeconds - (3600 * hours)) / 60;
		if (minutes)
		{
			output += std::to_string(minutes) + "m:";
		}

		timeInSeconds = (timeInSeconds - (3600 * hours) - (minutes * 60));
		output += std::to_string(timeInSeconds) + "s";

		return output;

	}

	// Print useful error message instead of segfaulting when files are not there.
	static void problemLoading(const char* filename)
	{
		printf("Error while loading: %s\n", filename);
		printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
	}

	//Compares two floats within certain tolerence
	static bool floatAlmostEquals(float input, float compareTo, float tolerence)
	{
		float difference = std::fabsf(compareTo - input);
		return ((difference < tolerence) ? true : false);
	}

};


#endif // !__HELPERS_H__
