#include "MapGenerator.h"
#include "MyBodyParser.h"

USING_NS_CC;

MapGenerator::MapGenerator(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    layer1=layer;

    createBoxBlock1(15, Vec2(0,0), true, true);
    createBoxBlock1(12, end_point, false, false);
    createBoxBlock1(12, Vec2(0,0), false, false);
    createBoxBlock1(15, end_point, true, true);
    createBoxBlock1(1, Vec2(200,98), true, true);


	MyBodyParser::getInstance()->parseJsonFile( "maps/map1.json" );

	MyBodyParser::getInstance()->generateMap(layer);


}

MapGenerator::~MapGenerator(){}



// int n - number of walls blocks;
// Vec2 start_value - start with x and y point;
// bool xORy - count with x or y coordinate.; true - x, false -y;
// bool jumpHero. if true -> after collision hero can jump

void MapGenerator::createBoxBlock1(int n, cocos2d::Vec2 start_value, bool xORy, bool jumpHero)
{
	for(int i=0; i<n; i++)
	{
		auto wall_point = Sprite::create("wall1.png");
		auto physicsBody = PhysicsBody::createBox(Size(wall_point->getContentSize().width*fabs(wall_point->getScaleX()),
															wall_point->getContentSize().height*fabs(wall_point->getScaleY())), 
													PhysicsMaterial(0.0f, 0.0f, 1.0f));
		wall_point->setScale(visibleSize.width/wall_point->getContentSize().width*0.1,visibleSize.width/wall_point->getContentSize().width*0.1);

		if(xORy)
			wall_point->setPosition(start_value.x+wall_point->getContentSize().width*fabs(wall_point->getScaleX())*i, start_value.y);
		else
			wall_point->setPosition(start_value.x, start_value.y+wall_point->getContentSize().height*fabs(wall_point->getScaleY())*i);

    	physicsBody->setContactTestBitmask(true);
    	physicsBody->setDynamic(false);
    	if(jumpHero)
    		physicsBody->setTag(10);
    	wall_point->setPhysicsBody(physicsBody);
		

		layer1->addChild(wall_point);

		if(i==n-1)
			end_point = wall_point->getPosition();
	}
}