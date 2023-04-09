#ifndef __FILE_DIALOGS_H__
#define __FILE_DIALOGS_H__

#include "cocos2d.h"

class FileDialogs
{
public:
	static std::string openFile(const char* filter);
	static std::string saveFile(const char* filter);
};

#endif // __FILE_DIALOGS_H__
