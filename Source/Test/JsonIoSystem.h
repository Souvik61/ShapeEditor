#ifndef __JSON_IO_SYSTEM_H__
#define __JSON_IO_SYSTEM_H__

#include <string>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

class OverallManager;
class RigidBodyModel;

//Saves shape data to the disk.
class JsonIoSystem
{
public:
    std::string prjFilePath;//Leaving this empty will place .json file at the project folder.
    std::string projectName;
    //Serialize data to json format
    std::string serialize();
    rapidjson::Document deserialize();
    //New!
    std::string newSerialize();
    
    //Setup a given value object based on a rigidbody model according to aurelienribon
    void setupJSONValFromRbIter(rapidjson::Value& val, RigidBodyModel* model, rapidjson::Document& doc);

    //void setupWithDOM(rapidjson::Document doc);
    //Import/Export
    void exportToFile();
    void importFromFile();

    void setOverallManager(OverallManager* oM) { _oManager = oM; };
    void setProjectPath(std::string path) { prjFilePath = path; }
    void setProjectFilename(std::string name) { projectName = name; }
private:
    OverallManager* _oManager;
    //Why is this function here?
    void setupProject(rapidjson::Document&);

};

#endif // __JSON_IO_SYSTEM_H__
