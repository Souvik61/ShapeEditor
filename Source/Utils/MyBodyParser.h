//
//  MyBodyParser.h
//
//  Created by Jason Xu.
//
//

#pragma once

#include <string>
#include "cocos2d.h"
#include "rapidjson/document.h"

USING_NS_CC;

class B2_PhysicsBody;
class B2_WorldNode;

class MyBodyParser {
    MyBodyParser(){}
    rapidjson::Document doc;
public:
    static MyBodyParser* getInstance();
    bool parseJsonFile(const std::string& pFile);
    bool parse(unsigned char* buffer, long length);
    void clearCache();
    PhysicsBody* bodyFormJson(Node* pNode, const std::string& name, PhysicsMaterial material);
	//added ----
	PhysicsBody* bodyFromJsonWithTag(Node* pNode, const std::string& name, PhysicsMaterial material);
	//added-end----
    
    //Some helpers
    B2_PhysicsBody* bodyFromJsonB2d(Node* pNode, const std::string& name, B2_WorldNode* wN);
    //Some helpers -end

	Vec2 getOriginPoint(Size size,const std::string& name);
	Vec2 getNormalizedOrigin(Size size, std::string name);
};