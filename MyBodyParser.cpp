
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


PhysicsBody* MyBodyParser::bodyFormJson(cocos2d::Node *pNode, const std::string& name, PhysicsMaterial material)
{
    PhysicsBody* body = nullptr;
    rapidjson::Value &bodies = doc["rigidBodies"];
    if (bodies.IsArray())
    {

        for (unsigned int i=0; i<bodies.Size(); ++i)
        {

            if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
            {
                rapidjson::Value &bd = bodies[i];
                if (bd.IsObject())
                {
                    body = PhysicsBody::create();
                    float width = pNode->getContentSize().width;
                    float offx = - pNode->getAnchorPoint().x*pNode->getContentSize().width;
                    float offy = - pNode->getAnchorPoint().y*pNode->getContentSize().height;

                    Point origin( bd["origin"]["x"].GetDouble(), bd["origin"]["y"].GetDouble());
                    rapidjson::Value &polygons = bd["polygons"];
                    for (unsigned int i = 0; i<polygons.Size(); ++i)
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

void MyBodyParser::generateMap(cocos2d::Layer *layer)
{
    rapidjson::Value &map = doc["map"];

    if(map.IsArray())
    {
        for (unsigned int i = 0; i < map.Size(); i++)
        {
            rapidjson::Value &material = map[i]["material"];

            if(material.IsObject())
            {
                if(!material["weapon"].GetBool())
                {
                    std::string res = material["resource"].GetString();
                    rapidjson::Value &horiz = material["horizontal"];

                    for (unsigned int j = 0; j < horiz.Size(); j++)
                    {
                        auto line = Sprite::create(res);
                        line->setAnchorPoint(Vec2(0,0));

                        auto physicsBody = PhysicsBody::createBox(Size(line->getContentSize().width,
                                                            line->getContentSize().height), 
                                                    PhysicsMaterial(0.0f, 0.0f, 1.0f));
                        physicsBody->setDynamic(false);
                       
                        
                        
                        line->setScale(horiz[j][1].GetInt()*horiz[j][2].GetInt()/line->getContentSize().width, 
                                        horiz[j][2].GetInt()/line->getContentSize().height);

                        line->setPosition(horiz[j][2].GetInt()*horiz[j][0][0].GetInt(), horiz[j][2].GetInt()*horiz[j][0][1].GetInt());
                        
                        line->setPhysicsBody(physicsBody);
                        layer->addChild(line);


                    }

                    rapidjson::Value &vertic = material["vertical"];

                    for (unsigned int j = 0; j < vertic.Size(); j++)
                    {
                        auto line = Sprite::create(res);
                        line->setAnchorPoint(Vec2(0,0));

                        auto physicsBody = PhysicsBody::createBox(Size(line->getContentSize().width*fabs(line->getScaleX()),
                                                            line->getContentSize().height*fabs(line->getScaleY())), 
                                                    PhysicsMaterial(0.0f, 0.0f, 1.0f));
                        physicsBody->setDynamic(false);
                        

                       
                        line->setScale(vertic[j][2].GetInt()/line->getContentSize().width,
                                        vertic[j][1].GetInt()*vertic[j][2].GetInt()/line->getContentSize().height);
                        line->setPosition(vertic[j][2].GetInt()*vertic[j][0][0].GetInt(), vertic[j][2].GetInt()*vertic[j][0][1].GetInt());
                        
                        line->setPhysicsBody(physicsBody);
                        layer->addChild(line);

                    }
                 }
            }
        }
    }
}