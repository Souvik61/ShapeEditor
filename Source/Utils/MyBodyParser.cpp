//
//  MyBodyParser.cpp
//
//  Created by Jason Xu.
//	Slightly Patched
//
//

#include "MyBodyParser.h"

MyBodyParser* MyBodyParser::getInstance()
{
    static MyBodyParser* sg_ptr = nullptr;
    if (nullptr == sg_ptr)
    {
        sg_ptr = new MyBodyParser;
    }
    return sg_ptr;
}

bool MyBodyParser::parse(unsigned char *buffer, long length)
{
    bool result = false;
    std::string js((const char*)buffer, length);
    doc.Parse<0>(js.c_str());
    if(!doc.HasParseError())
    {
        result = true;
    }
    return result;
}

void MyBodyParser::clearCache()
{
    doc.SetNull();
}

bool MyBodyParser::parseJsonFile(const std::string& pFile)
{
    auto content = FileUtils::getInstance()->getDataFromFile(pFile);
    bool result = parse(content.getBytes(), content.getSize());
    return result;
}

//从json文件加载正确的body
PhysicsBody* MyBodyParser::bodyFormJson(cocos2d::Node *pNode, const std::string& name, PhysicsMaterial material)
{
    PhysicsBody* body = nullptr;
    rapidjson::Value &bodies = doc["rigidBodies"];
    if (bodies.IsArray())
    {
        //遍历文件中的所有body
        for (int i=0; i<bodies.Size(); ++i)
        {
            //找到了请求的那一个
            if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
            {
                rapidjson::Value &bd = bodies[i];
                if (bd.IsObject())
                {
                    //创建一个PhysicsBody, 并且根据node的大小来设置
                    body = PhysicsBody::create();
                    float width = pNode->getContentSize().width;
                    float offx = - pNode->getAnchorPoint().x*pNode->getContentSize().width;
                    float offy = - pNode->getAnchorPoint().y*pNode->getContentSize().height;

                    Point origin( bd["origin"]["x"].GetDouble(), bd["origin"]["y"].GetDouble());
                    rapidjson::Value &polygons = bd["polygons"];
                    for (int i = 0; i<polygons.Size(); ++i)
                    {
                        int pcount = polygons[i].Size();
                        Point* points = new Point[pcount];
                        for (int pi = 0; pi<pcount; ++pi)
                        {
                            points[pi].x = offx + width * polygons[i][pcount-1-pi]["x"].GetDouble();
                            points[pi].y = offy + width * polygons[i][pcount-1-pi]["y"].GetDouble();
                        }
                        body->addShape(PhysicsShapePolygon::create(points, pcount, material));
                        delete [] points;
                    }
					//Patch
					rapidjson::Value &circles = bd["circles"];
					for (int i = 0; i<circles.Size(); ++i)
					{
						body->addShape(PhysicsShapeCircle::create(width*circles[i]["r"].GetDouble(),material,Vec2(offx + width*circles[i]["cx"].GetDouble(), offy + width*circles[i]["cy"].GetDouble())));
					}
				}
                else
                {
                    CCLOG("body: %s not found!", name.c_str());
                }
                break;
            }
        }
    }
    return body;
}

PhysicsBody * MyBodyParser::bodyFromJsonWithTag(Node * pNode, const std::string & name, PhysicsMaterial material)
{
	PhysicsBody* body = PhysicsBody::create();
	
	auto pBodyName = name.substr(0,24);
	body->setName(pBodyName);

	std::string bodyGroupName = pBodyName;

	rapidjson::Value &bodies = doc["rigidBodies"];
	if (bodies.IsArray())
	{
		//遍历文件中的所有body
		for (int i = 0; i < bodies.Size(); ++i)
		{
			bool groupFound = false;
			std::string tempStr(bodies[i]["name"].GetString());

			if (tempStr.find(bodyGroupName) != std::string::npos) {
				//.. found.
				groupFound = true;
			}

			//找到了请求的那一个
			if (groupFound)
			{
				char c = tempStr.at(tempStr.length() - 1);
				int tag = std::atoi(std::string(1,c).c_str());
				rapidjson::Value &bd = bodies[i];
				if (bd.IsObject())
				{
					//创建一个PhysicsBody, 并且根据node的大小来设置
					float width = pNode->getContentSize().width;
					float offx = -pNode->getAnchorPoint().x*pNode->getContentSize().width;
					float offy = -pNode->getAnchorPoint().y*pNode->getContentSize().height;
					//Patch
					rapidjson::Value &circles = bd["circles"];
					for (int i = 0; i < circles.Size(); ++i)
					{
						auto shape = PhysicsShapeCircle::create(width*circles[i]["r"].GetDouble(), material, Vec2(offx + width * circles[i]["cx"].GetDouble(), offy + width * circles[i]["cy"].GetDouble()));
						shape->setTag(tag);
						body->addShape(shape);
					}
				}
				else
				{
					body->release();
					CCLOG("body: %s not found!", name.c_str());
				}
			}
		}
	}
	return body;
}

Vec2 MyBodyParser::getOriginPoint(Size size, const std::string & name)
{
	PhysicsBody* body = nullptr;
	rapidjson::Value &bodies = doc["rigidBodies"];
	if (bodies.IsArray())
	{
		//遍历文件中的所有body
		for (int i = 0; i < bodies.Size(); ++i)
		{
			//找到了请求的那一个
			if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
			{
				rapidjson::Value &bd = bodies[i];
				if (bd.IsObject())
				{
					float width = size.width;
					float offx = -0.5*size.width;
					float offy = -0.5*size.height;

					auto x1 = bd["origin"]["x"].GetDouble();
					auto y1 = bd["origin"]["y"].GetDouble();

					Vec2 origin;
					origin.x = width * bd["origin"]["x"].GetDouble();
					origin.y = width * bd["origin"]["y"].GetDouble();
					return origin;
				}
			}
		}
		CCLOG("Origin point of body: %s not found!", name.c_str());
	}
	else
	{
		return Vec2();
	}
}

Vec2 MyBodyParser::getNormalizedOrigin(Size size, const std::string name)
{
	PhysicsBody* body = nullptr;
	rapidjson::Value &bodies = doc["rigidBodies"];
	if (bodies.IsArray())
	{
		//遍历文件中的所有body
		for (u_int i = 0; i < bodies.Size(); ++i)
		{
			//找到了请求的那一个
			if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
			{
				rapidjson::Value &bd = bodies[i];
				if (bd.IsObject())
				{
					Vec2 origin;
					origin.x = bd["origin"]["x"].GetDouble();
					origin.y = bd["origin"]["y"].GetDouble();
					return origin;
				}
			}
		}
	}
	else
	{
		return Vec2();
		CCASSERT(0, "ParsingOriginError");
	}
}
