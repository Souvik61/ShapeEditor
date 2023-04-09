#ifndef __PROJECT_MANAGER_H__
#define __PROJECT_MANAGER_H__

#include "cocos2d.h"

class JsonIoSystem;

//Used for creating, opening and saving projects.
class ProjectManager
{
public:
	enum class ProjectState { UNLOADED, LOADED };
	ProjectState prjState;
	std::string prjFilePath;//Leaving this empty will place .json file at the project folder.
	std::string projectName;
	JsonIoSystem* jIOSystem;
public:
	ProjectManager();

	void createFile();
	//The whole load file procedure
	void loadFile();
	void saveFile();

	void loadFileNew(std::string path);
	//Load actual project with given path
	void setProjectPath(std::string absolute_path);
	void loadProject();

	bool isProjectLoaded() { return prjState == ProjectState::LOADED; }

private:
	std::string strReplace(std::string str, const std::string& from, const std::string& to);

	//Event 

	void onProjectLoaded();
};

#endif // __PROJECT_MANAGER_H__
