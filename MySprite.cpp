#include "MySprite.h"

using namespace cocos2d;

MySprite::MySprite(cocos2d::Layer *layer) 
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    hero = Sprite::create("player2.png");
    hero->setPosition(Point(600,500));
    hero->setScale(0.25, 0.25);
    //radius1 = hero->getContentSize().width*hero->getScaleX();
    auto physicsBody = PhysicsBody::createCircle(hero->getBoundingBox().size.width*2, PhysicsMaterial(0.0f, 0.0f, 0.5f));
   
    physicsBody->setContactTestBitmask(true);
    // physicsBody->setCategoryBitmask(0x02);    
    // physicsBody->setCollisionBitmask(0x01);
    physicsBody->setTag(11);
    physicsBody->setRotationEnable(true);
    physicsBody->setDynamic(true);

   


    hero->setPhysicsBody(physicsBody);

    //layer->runAction(Follow::create(hero));
    layer->addChild(hero);

}

MySprite::~MySprite() {}

void MySprite::addEvents()
{
 
}


cocos2d::Sprite *MySprite::returnHero()
{
    return hero;
}

float MySprite::returnRadius()
{
    return radius1;
}