#include "MySprite.h"

using namespace cocos2d;

MySprite::MySprite(cocos2d::Layer *layer) 
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    hero = Sprite::create("player1.png");
    hero->setPosition(Point(600,500));
    
    hero->setScale(visibleSize.width/(hero->getContentSize().width)*0.1, visibleSize.width/(hero->getContentSize().width)*0.1);
    radius1 = hero->getContentSize().width*hero->getScaleX();
    auto physicsBody = PhysicsBody::createCircle(hero->getContentSize().width*hero->getScaleX(), PhysicsMaterial(0.0f, 0.0f, 0.2f));
    physicsBody->setContactTestBitmask(true);
    // physicsBody->setCategoryBitmask(0x02);    
    // physicsBody->setCollisionBitmask(0x01);
    physicsBody->setTag(11);
    physicsBody->setRotationEnable(true);
    physicsBody->setDynamic(true);

    hero->setPhysicsBody(physicsBody);

    layer->runAction(Follow::create(hero));
    layer->addChild(hero);


    // auto some = Sprite::create("player1.png");
    // some->setPosition(Vec2(500,500));
    // auto physicsBody2 = PhysicsBody::createBox(Size(200,200), PhysicsMaterial(0.0f, 0.0f, 0.0f));
    // some->setScale(visibleSize.width/(hero->getContentSize().width)*0.1, visibleSize.width/(hero->getContentSize().width)*0.1);
    
    // physicsBody2->setContactTestBitmask(true);
    // physicsBody2->setDynamic(true);
    // some->setPhysicsBody(physicsBody2);

   
    // layer->addChild(some);

   // auto pin1 = PhysicsJointPin::construct(hero->getPhysicsBody(), some->getPhysicsBody(), hero->getPosition());
   // Director::getInstance()->getRunningScene()->getPhysicsWorld()->addJoint(pin1);

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