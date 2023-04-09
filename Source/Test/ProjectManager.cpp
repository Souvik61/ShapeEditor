#include "ProjectManager.h"
#include "JsonIoSystem.h"
#include "Utils/FileDialogs.h"

USING_NS_CC;

ProjectManager::ProjectManager()
{
	prjState = ProjectState::UNLOADED;
	jIOSystem = new JsonIoSystem();
}

void ProjectManager::createFile()
{
	//jIOSystem->exportToFile();
}

void ProjectManager::loadFile() {

	std::string fP = FileDialogs::openFile("JSON (*.json)\0*.json\0");
	
	if (!fP.empty())
	{
		setProjectPath(fP);
		loadProject();
	}

}

void ProjectManager::saveFile()
{
	if (!projectName.empty())
	{
		jIOSystem->exportToFile();
	}
}


void ProjectManager::loadFileNew(std::string fP)
{
	if (!fP.empty())
	{
		setProjectPath(fP);
		loadProject();
	}
}

void ProjectManager::setProjectPath(std::string fP)
{
	if (!fP.empty())
	{
		auto a = fP.find_last_of("\\");
		auto b = fP.substr(a + 1); //Get file name
		auto c = fP.substr(0, a);  //Get file path
		auto d = strReplace(c, "\\", "/");//Replace all occurrences of \\ to /
		d.push_back('/');


		jIOSystem->prjFilePath = prjFilePath = d;
		jIOSystem->projectName = projectName = b;

		prjState = ProjectState::LOADED;
	}
}

void ProjectManager::loadProject()
{
	jIOSystem->importFromFile();
	prjState = ProjectState::LOADED;
	onProjectLoaded();
}

void ProjectManager::onProjectLoaded()
{
	prjState = ProjectState::LOADED;



}

std::string ProjectManager::strReplace(std::string str, const std::string& from, const std::string& to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

//std::string ReplaceAll(std::string str, const std::string & from, const std::string & to) {
//	size_t start_pos = 0;
//	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
//		str.replace(start_pos, from.length(), to);
//		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
//	}
//	return str;
//}


