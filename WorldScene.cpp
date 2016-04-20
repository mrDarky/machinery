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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    jumpHero = false;


    auto edgeBody = PhysicsBody::createEdgeSegment(Vec2(0,0), Vec2(500,0), PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    edgeBody->setTag(10);
    edgeBody->setContactTestBitmask(1);
    auto edgeNode = Node::create();
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    edgeNode->setPhysicsBody(edgeBody);
    
    this->addChild(edgeNode);


    // circlePoint = DrawNode::create();
    // circlePoint->drawCircle(Vec2(100,100), 200, 10, 60,false, Color4F(1,1,1,1));
    // circlePoint->setVisible(false);
    // this->addChild(circlePoint, 3);


    _map_create = new MapGenerator(this);

    _circlePoint = new Circle(this);
    //create main hero
    _mySprite = new MySprite(this);
    _mySprite->addEvents();

   // _turel = new Turel(this, Vec2(190,220), true);
    _turel = Turel::CreateStandTurel(this, Vec2(190,220), true, 1);
    _turel2 = Turel::CreateStandTurel(this, Vec2(1490,220), false,1);



////[start] Keybord event
    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
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


    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        
        
        keys.erase(keyCode);
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);


////[end] keybordEvent



////[start] contacts event
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [=](PhysicsContact& contact){

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
    };
  
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
////[end] contacts event


////[start] click event
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch* touch, Event* event) -> bool {

        auto bounds = event->getCurrentTarget()->getBoundingBox();
        _circlePoint->getCircle()->setVisible(true);
        _circlePoint->getCircle_Sector()->setVisible(true);
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
      };

        touchListener->onTouchEnded = [=](Touch* touch, Event* event)
        {
            _circlePoint->getCircle()->setVisible(false);
            _circlePoint->getCircle_Sector()->setVisible(false);

            if(_circlePoint->getCircleOverload()+45.0<360){
                _circlePoint->setCircleOverload(_circlePoint->getCircleOverload()+45.0);
                _mySprite->returnHero()->setPosition(event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()));
            }
        };

   Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
////[end] click event


    this->schedule(schedule_selector(WorldScene::updateSec), 0.3f);
    this->scheduleUpdate();

    return true;
}


bool WorldScene::isKeyPressed(EventKeyboard::KeyCode code) {
    if(keys.find(code) != keys.end())
        return true;
    return false;
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


   
    _turel->followHero(_mySprite->returnHero()->getPosition());
    _turel2->followHero(_mySprite->returnHero()->getPosition());
    


    //_turel->add_Bullet();
  
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
    _turel->add_Bullet();
    _turel2->add_Bullet();
    //_turel->getPos_bullet();
}


void WorldScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}






// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> WorldScene::keys;





