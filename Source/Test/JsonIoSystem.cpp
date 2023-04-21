#include "JsonIoSystem.h"
#include "OverallManager.h"
#include "RigidBodyModel.h"
#include "ShapeModel.h"

using namespace rapidjson;

std::string JsonIoSystem::serialize()
{
    //Create root object
    Document doc;
    doc.SetObject();

    rapidjson::Value rigidBodyArr;
    rigidBodyArr.SetArray();
    doc.AddMember("rigidBodies", rigidBodyArr, doc.GetAllocator());

    
    //For each rigidbody in rbManager
    for (auto iter : _oManager->rbManager->_rbModelsMap) {

        RigidBodyModel* model = iter.second;
        //Create a json object
        rapidjson::Value rbObj;
        rbObj.SetObject();

        //Add name key:val pair
        {
            rapidjson::Value v; v.SetString(model->getName().c_str(), doc.GetAllocator());
            rbObj.AddMember("name", v, doc.GetAllocator());
        }
        //Add imgPath key:val pair
        rbObj.AddMember("imagePath", "", doc.GetAllocator());
        //Add origin object
        {
            rapidjson::Value orgObj;
            orgObj.SetObject();
            orgObj.AddMember("x", model->origin.x, doc.GetAllocator());
            orgObj.AddMember("y", model->origin.y, doc.GetAllocator());
            rbObj.AddMember("origin", orgObj, doc.GetAllocator());
        }
        
        //No need to serialize polygons now will do later

        //Serialize polygon array with key polygon
        //rapidjson::Value polyArr;
        //polyArr.SetArray();
        //rbObj.AddMember("polygons", polyArr, doc.GetAllocator());
        ////Foreach polygon in rigidbody model
        //for (auto polygon : model->_polygons) {
        //
        //    //Create an array object
        //    rapidjson::Value vertArr;
        //    vertArr.SetArray();
        //    //Foreach vertex push a vector object
        //    for (Vec2 vertex : polygon->vertices)
        //    {
        //        rapidjson::Value vecObj;
        //        vecObj.SetObject();
        //
        //        vecObj.AddMember("x", vertex.x, doc.GetAllocator());
        //        vecObj.AddMember("y", vertex.y, doc.GetAllocator());
        //
        //        vertArr.PushBack(vecObj, doc.GetAllocator()); //Push to vert array
        //    }
        //
        //    polyArr.PushBack(vertArr, doc.GetAllocator());
        //}

        ////////Serialize Shape array with key shapes
        //For each Shape in rigidbodymodel
        rapidjson::Value shapeArr;
        shapeArr.SetArray();
        //For each shapes
        for (auto shape : model->_shapes) {

            //Create shape DOM
            rapidjson::Value shapeObj;
            shapeObj.SetObject();
            //Add type key:val
            {
                shapeObj.AddMember("type", "", doc.GetAllocator());
            }
            //Add vertices field in array
            {
                rapidjson::Value vertArr;
                vertArr.SetArray();
                shapeObj.AddMember("vertices", vertArr, doc.GetAllocator());
            }
            //Add vertices to array
            for (Vec2 vertex : shape->_vertices)
            {
                rapidjson::Value vec;
                vec.SetObject();
                vec.AddMember("x", vertex.x, doc.GetAllocator());
                vec.AddMember("y", vertex.y, doc.GetAllocator());
                shapeObj["vertices"].PushBack(vec, doc.GetAllocator());
            }

            shapeArr.PushBack(shapeObj, doc.GetAllocator());
        }
       rbObj.AddMember("shapes", shapeArr, doc.GetAllocator());
       
       //Push this rbObj to "rigidBodiesArray"
       doc["rigidBodies"].PushBack(rbObj, doc.GetAllocator());
    }
 

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

rapidjson::Document JsonIoSystem::deserialize()
{
    //auto json = FileUtils::getInstance()->getStringFromFile("F:/Cocos_projects/NewProject_7/build.win32/TestJSON.json");

    auto json = FileUtils::getInstance()->getStringFromFile(prjFilePath + projectName);
    //bool fg = FileUtils::getInstance()->isFileExist("TestJSON");
    //FileUtils::getInstance()->writeStringToFile("a", "Test.json");
    Document document;
    document.Parse(json.c_str());

    return document;
}

std::string JsonIoSystem::newSerialize()
{
    //Create root object
    Document doc;
    doc.SetObject();

    //Add rigidBodies array
    rapidjson::Value rigidBodyArr;
    rigidBodyArr.SetArray();
    doc.AddMember("rigidBodies", rigidBodyArr, doc.GetAllocator());

    //For each rigidbody in rbManager
    for (auto iter : _oManager->rbManager->_rbModelsMap) {

        RigidBodyModel* model = iter.second;
        //Create a json object
        rapidjson::Value rbObj;
        rbObj.SetObject();

        setupJSONValFromRbIter(rbObj, model, doc);

        //Push this rbObj to "rigidBodiesArray"
        doc["rigidBodies"].PushBack(rbObj, doc.GetAllocator());
    }

    //Add dynamicObjects array (actually unused)
    rapidjson::Value dynObjectArr;
    dynObjectArr.SetArray();
    doc.AddMember("dynamicObjects", dynObjectArr, doc.GetAllocator());

    // Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

void JsonIoSystem::setupJSONValFromRbIter(rapidjson::Value& rbObj, RigidBodyModel* model, rapidjson::Document& doc)
{
    //Add "name" key:val pair
    {
        rapidjson::Value v; v.SetString(model->getName().c_str(), doc.GetAllocator());
        rbObj.AddMember("name", v, doc.GetAllocator());
    }
    
    //Add imgPath key:val pair
    {
        auto imgStr = model->getImagePath();

        rapidjson::Value v; v.SetString(imgStr.c_str(), doc.GetAllocator());
        rbObj.AddMember("imagePath", v, doc.GetAllocator());
        //rbObj["imagePath"].SetNull();
    }

    //Add origin key:val pair
    {
        rapidjson::Value orgObj;
        orgObj.SetObject();
        //orgObj.AddMember("x", model->origin.x, doc.GetAllocator());
        //orgObj.AddMember("y", model->origin.y, doc.GetAllocator());
        orgObj.AddMember("x", model->origin.x / SCALE_RATIO, doc.GetAllocator());
        orgObj.AddMember("y", model->origin.y / SCALE_RATIO, doc.GetAllocator());
        rbObj.AddMember("origin", orgObj, doc.GetAllocator());
    }

    //Add polygons key:val pair --start
    {
        rapidjson::Value polyArr;
        polyArr.SetArray();

        for (auto polygon : model->_polygons) {//Foreach polygon in rigidbody model
            //Create an array object
            rapidjson::Value vertArr;
            vertArr.SetArray();
            //Foreach vertex push a vector object
            for (Vec2 vertex : polygon->vertices)
            {
                rapidjson::Value vecObj;
                vecObj.SetObject();

                //vecObj.AddMember("x", vertex.x, doc.GetAllocator());
                //vecObj.AddMember("y", vertex.y, doc.GetAllocator());
                
                vecObj.AddMember("x", vertex.x / SCALE_RATIO, doc.GetAllocator());
                vecObj.AddMember("y", vertex.y / SCALE_RATIO, doc.GetAllocator());

                vertArr.PushBack(vecObj, doc.GetAllocator()); //Push to vert array
            }

            polyArr.PushBack(vertArr, doc.GetAllocator());
        }
        rbObj.AddMember("polygons", polyArr, doc.GetAllocator());//Add key:val pair
    }
    //Add polygons key:val pair --end

     //Add circles key:val pair --start
    {
        rapidjson::Value circArr;
        circArr.SetArray();
        rbObj.AddMember("circles", circArr, doc.GetAllocator());
    }
    //Add circles key:val pair --end

    //Add shapes key:val pair --start
    {
        rapidjson::Value shapeArr;
        shapeArr.SetArray();

        for (auto shape : model->_shapes) { //For each shape in rigidbody model

            //Create shape DOM
            rapidjson::Value shapeObj;
            shapeObj.SetObject();
            
            //Add type key:val
            shapeObj.AddMember("type", "POLYGON", doc.GetAllocator());//Just set POLYGON for now
            
            //Add vertices field in array
            {
                rapidjson::Value vertArr;
                vertArr.SetArray();
                shapeObj.AddMember("vertices", vertArr, doc.GetAllocator());
            }
            //Add vertices to array
            for (Vec2 vertex : shape->_vertices)
            {
                rapidjson::Value vec;
                vec.SetObject();
                //vec.AddMember("x", vertex.x, doc.GetAllocator());
                //vec.AddMember("y", vertex.y, doc.GetAllocator());

                vec.AddMember("x", vertex.x / SCALE_RATIO, doc.GetAllocator());
                vec.AddMember("y", vertex.y / SCALE_RATIO, doc.GetAllocator());

                shapeObj["vertices"].PushBack(vec, doc.GetAllocator());
            }
            shapeArr.PushBack(shapeObj, doc.GetAllocator());
        }
        rbObj.AddMember("shapes", shapeArr, doc.GetAllocator());
    }
    //Add shapes key:val pair --end
}

void JsonIoSystem::exportToFile()
{
    //CC_ASSERT(prjFilePath != "");
    CC_ASSERT(projectName != "");

    //std::string str = serialize();
    
    std::string str = newSerialize();
    
    //FileUtils.writeStringToFile(projectFile, str, StandardCharsets.UTF_8);
    FileUtils::getInstance()->writeStringToFile(str, prjFilePath + projectName);
}

void JsonIoSystem::importFromFile()
{
    CC_ASSERT(projectName != "");

    rapidjson::Document& doc = deserialize();
    setupProject(doc);

}

void JsonIoSystem::setupProject(rapidjson::Document& doc)
{
    //JSONObject json = new JSONObject(str);

    // rigid bodies
    rapidjson::Value& rbArr = doc["rigidBodies"];

    for (int i = 0; i < rbArr.Size(); i++) {

        rapidjson::Value& rbDOM = rbArr[i];

        //Parse name

        std::string name = rbDOM["name"].GetString();
        _oManager->rbManager->addARigidBodyEntry(name);

        RigidBodyModel* rbModel = _oManager->rbManager->getModel(name);

        //Parse image path
        {
            if (rbDOM["imagePath"].IsString())//To set the compatability with previous versions
            {
                rbModel->setImagePath(rbDOM["imagePath"].GetString());
            }
        }

        //Parse origin point
        {
            rapidjson::Value& org = rbDOM["origin"];
            //rbModel->origin.set(org["x"].GetFloat(), org["y"].GetFloat());
            rbModel->origin.set(org["x"].GetFloat() * SCALE_RATIO, org["y"].GetFloat() * SCALE_RATIO);
        }

        //Parse shapes list
        rapidjson::Value& shapeArr = rbDOM["shapes"];

        for (int ii = 0; ii < shapeArr.Size(); ii++) {
            //JSONObject shapeElem = shapesElem.getJSONObject(ii);
            rapidjson::Value& shapeDOM = shapeArr[ii];

            auto shapeModel = new ShapeModel(ShapeModel::Type::POLYGON);

            rapidjson::Value& vertArr = shapeDOM["vertices"];
            //Parse vertices
            for (int iii = 0; iii < vertArr.Size(); iii++) {
                rapidjson::Value& vertDOM = vertArr[iii];
                
                //shape.getVertices().add(new Vector2((float)vertexElem.getDouble("x"), (float)vertexElem.getDouble("y")));
                
                //Vec2 vert(vertDOM["x"].GetFloat(), vertDOM["y"].GetFloat());
                
                Vec2 vert(vertDOM["x"].GetFloat() * SCALE_RATIO, vertDOM["y"].GetFloat() * SCALE_RATIO);
                shapeModel->_vertices.push_back(vert);
            }
            shapeModel->close();
            rbModel->_shapes.pushBack(shapeModel);
        }
    }

}
