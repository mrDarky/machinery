#include "WorldScene.h"



USING_NS_CC;

Scene* WorldScene::createScene()
{
    auto scene = Scene::createWithPhysics( );
    scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    scene->getPhysicsWorld( )->setGravity(Vec2(0, -2000));

    auto layer = WorldScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ) );

    scene->addChild(layer);
    return scene;
}

bool WorldScene::init()
{

    if( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    jumpHero = false;

    // auto background = Sprite::create("blue_fon1.jpg");
    // background->setPosition( Vec2(visibleSize.width, 
    //                             visibleSize.height));
    // background->setScale(2,2);
    // this->addChild(background, 0);


    //generate map
    _map_create = new MapGenerator(this);
    //generate Circle elements, camera following, skills elements
    _circlePoint = new Circle(this);

    //create main hero
    _mySprite = new MySprite(this);
    _mySprite->addEvents();



////[start] Keybord event
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = CC_CALLBACK_2(WorldScene::onKeyPressed, this);
    eventListener->onKeyReleased = CC_CALLBACK_2(WorldScene::onKeyReleased, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);
////[end] keybordEvent

////[start] mouseEvent
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(WorldScene::onMouseMove, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
////[end] mouseEvent


////[start] contacts event
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(WorldScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
////[end] contacts event


////[start] click event
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(WorldScene::onTouchEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
////[end] click event

    this->schedule(schedule_selector(WorldScene::updateSec), 0.3f);
    this->schedule(schedule_selector(WorldScene::update_delSec), 0.01f);
    this->scheduleUpdate();


    return true;
}




void WorldScene::update(float delta)
{

    _circlePoint->getCircle()->setPosition(Vec2(_mySprite->returnHero()->getPosition().x-100,
                                    _mySprite->returnHero()->getPosition().y-100));
    _circlePoint->getCircle_Sector()->setPosition(Vec2(_mySprite->returnHero()->getPosition().x-100,
                                    _mySprite->returnHero()->getPosition().y-100));

    if(_circlePoint->getCircleOverload()>0)
        _circlePoint->setCircleOverload(_circlePoint->getCircleOverload()-0.5);
    _circlePoint->reloadSector_new();

    

    Node::update(delta);
    Layer::update(delta);

    if (!isKeyPressed(EventKeyboard::KeyCode::KEY_D) && !isKeyPressed(EventKeyboard::KeyCode::KEY_A) )
    {
        _mySprite->returnHero()->getPhysicsBody()->setVelocity(Vec2(0, _mySprite->returnHero()->getPhysicsBody()->getVelocity().y));
    }

    for (unsigned int i = 0; i < Turel::get_allTurel().size(); ++i)
    {
        Turel::get_allTurel()[i]->followHero(_mySprite->returnHero()->getPosition());
    }


    

        if(_circlePoint->getFocusVec().x >= visibleSize.width/2)
            _circlePoint->getFollowCircle()->setPosition( Vec2 (_mySprite->returnHero()->getPosition().x+200*cosf(_circlePoint->getFocusAngle() ),
                                                        _mySprite->returnHero()->getPosition().y-200*sinf(-_circlePoint->getFocusAngle()) ) );
        else
            _circlePoint->getFollowCircle()->setPosition( Vec2 (_mySprite->returnHero()->getPosition().x-200*cosf(-_circlePoint->getFocusAngle() ),
                                                        _mySprite->returnHero()->getPosition().y-200*sinf(_circlePoint->getFocusAngle()) ) );

  
}



void WorldScene::onEnter()
{
    Layer::onEnter();


   


     // auto joint = PhysicsJointDistance::construct(_mySprite->returnHero()->getPhysicsBody(), eye->getPhysicsBody(), Vec2(0,0), Vec2(0,0));
     // joint->setCollisionEnable(false);

     // Director::getInstance()->getRunningScene()->getPhysicsWorld()->addJoint(joint);

}



void WorldScene::updateSec(float delta)
{

    
     for (unsigned int i = 0; i < Turel::get_allTurel().size(); ++i)
    {
        Turel::get_allTurel()[i]->add_Bullet();
    }

}
void WorldScene::update_delSec(float delta)
{

}


void WorldScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


bool WorldScene::isKeyPressed(EventKeyboard::KeyCode code) {
    if(keys.find(code) != keys.end())
        return true;
    return false;
}


void WorldScene::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;

        
    float angle = (atanf((visibleSize.height/2 - e->getCursorY())/(visibleSize.width/2 - e->getCursorX())));
    _circlePoint->setFocusAngle(angle);
    _circlePoint->setFocusVec( Vec2 (e->getCursorX(), e->getCursorY() ));
    if(e->getCursorX() >= visibleSize.width/2){
        _circlePoint->getFollowCircle()->setPosition( Vec2 (_mySprite->returnHero()->getPosition().x+200*cosf(angle),
                                            _mySprite->returnHero()->getPosition().y-200*sinf(-angle) ) );
        
    }else if(e->getCursorX() < visibleSize.width/2){
        _circlePoint->getFollowCircle()->setPosition( Vec2 (_mySprite->returnHero()->getPosition().x-200*cosf(-angle),
                                            _mySprite->returnHero()->getPosition().y-200*sinf(angle) ) );
    }
}


void WorldScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keys.find(keyCode) == keys.end()){
        keys[keyCode] = std::chrono::high_resolution_clock::now();
    }

    if(keyCode == EventKeyboard::KeyCode::KEY_W && jumpHero) {
        _mySprite->returnHero()->getPhysicsBody()->applyImpulse(Vec2(0, 1000));
        jumpHero=false;

    }
    if(keyCode == EventKeyboard::KeyCode::KEY_D) 
    {
        _mySprite->returnHero()->getPhysicsBody()->setVelocity(Vec2(500, _mySprite->returnHero()->getPhysicsBody()->getVelocity().y));

    }
    if(keyCode == EventKeyboard::KeyCode::KEY_A) 
    {
        _mySprite->returnHero()->getPhysicsBody()->setVelocity(Vec2(-500, _mySprite->returnHero()->getPhysicsBody()->getVelocity().y));

    }
}

void WorldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{ 
    keys.erase(keyCode); 
};

bool WorldScene::onContactBegin(PhysicsContact& contact)
{

        auto shapeA = contact.getShapeA();
        auto bodyA = shapeA->getBody();
        auto shapeB = contact.getShapeB();
        auto bodyB = shapeB->getBody();

        if(bodyA->getTag()==5)
        {
            // if(bodyB->getTag()==11)
            //     _mySprite->returnHero()->setPosition(Vec2(600,600));
            bodyA->getNode()->removeFromParentAndCleanup(true);
            
        } 

        if( bodyB->getTag()==5)
        {
            bodyB->getNode()->removeFromParentAndCleanup(true);
            // if(bodyA->getTag()==11){

            // }
            
            
        }

        if(bodyA->getTag()==10 && bodyB->getTag()==11)
        {
            
            if(bodyB->getNode()->getPosition().y >= bodyA->getNode()->getPosition().y+bodyA->getNode()->getBoundingBox().size.height)
                    jumpHero=true;
        }
        else if(bodyA->getTag()==11 && bodyB->getTag()==10)
        {
            if(bodyA->getNode()->getPosition().y >= bodyB->getNode()->getPosition().y+bodyB->getNode()->getBoundingBox().size.height)
                    jumpHero=true;
        }
        if ((shapeA->getCategoryBitmask() & shapeB->getCollisionBitmask()) == 0 
            || (shapeB->getCategoryBitmask() & shapeA->getCollisionBitmask()) == 0)
        {
           return false;
        }
        return true;
}

bool WorldScene::onTouchBegan(Touch* touch, Event* event)
{
    auto bounds = event->getCurrentTarget()->getBoundingBox();
    _circlePoint->getCircle()->setVisible(true);
    _circlePoint->getCircle_Sector()->setVisible(true);
    //this->schedule(schedule_selector(WorldScene::updateSec), 5.0f);



   // _mySprite->returnHero()->setPosition(event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()));
    if (bounds.containsPoint(touch->getLocation())){


        // std::stringstream touchDetails;
        // touchDetails << "Touched at OpenGL coordinates: " << 
        // touch->getLocation().x << "," << touch->getLocation().y << std::endl <<
        // "Touched at UI coordinate: " << 
        // touch->getLocationInView().x << "," << touch->getLocationInView().y << std::endl <<
        // "Touched at local coordinate:" <<
        // event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).x << "," <<  
        // event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).y << std::endl <<
        // "Touch moved by:" << touch->getDelta().x << "," << touch->getDelta().y;

        // MessageBox(touchDetails.str().c_str(), "Touched");
     }

    return true;

}

void WorldScene::onTouchEnded(Touch* touch, Event* event)
{
    _circlePoint->getCircle()->setVisible(false);
    _circlePoint->getCircle_Sector()->setVisible(false);

    //this->schedule(schedule_selector(WorldScene::updateSec), 0.3f);

    if(_circlePoint->getCircleOverload()+45.0<360){
        _circlePoint->setCircleOverload(_circlePoint->getCircleOverload()+45.0);
        _mySprite->returnHero()->setPosition(event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()));
    }
}

// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> WorldScene::keys;





