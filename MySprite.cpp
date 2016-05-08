#include "MySprite.h"
#include "MyBodyParser.h"

using namespace cocos2d;

MySprite::MySprite(cocos2d::Layer *layer) 
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

     //add turel head
    MyBodyParser::getInstance()->parseJsonFile( "body/Turel.json" );

    hero = Sprite::create("player2.png");
    hero->setPosition(Point(600,500));
    hero->setScale(0.25, 0.25);
    //radius1 = hero->getContentSize().width*hero->getScaleX();
   // auto physicsBody = MyBodyParser::getInstance()->bodyFormJson(hero, "Hero", PhysicsMaterial( 0, 0, 0.5f ) );
    auto physicsBody = PhysicsBody::createCircle(hero->getBoundingBox().size.width*2, PhysicsMaterial(0.0f, 0.0f, 0.5f));
   
    physicsBody->setContactTestBitmask(true);
    // physicsBody->setCategoryBitmask(0x02);    
    // physicsBody->setCollisionBitmask(0x01);
    physicsBody->setTag(11);
    physicsBody->setRotationEnable(true);
    physicsBody->setDynamic(true);

   
    layer1=layer;

    hero->setPhysicsBody(physicsBody);

    layer->runAction(Follow::create(hero));
    layer->addChild(hero);

}

MySprite::~MySprite() {}

void MySprite::addEvents()
{
    // auto mouseListener = EventListenerMouse::create();
    // mouseListener->onMouseMove = CC_CALLBACK_1(MySprite::onMouseMove, this);
    // _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, layer1);
}


cocos2d::Sprite *MySprite::returnHero()
{
    return hero;
}

float MySprite::returnRadius()
{
    return radius1;
}

void MySprite::onMouseMove(Event *event)
{
    
}