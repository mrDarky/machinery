#ifndef __WORLD_SCENE_H__
#define __WORLD_SCENE_H__

#include "cocos2d.h"
#include "MySprite.h"
#include "Turel.h"
#include "MapGenerator.h"
#include "Circle.h"
#include <map>

class WorldScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(WorldScene);

    virtual void update(float delta) override;

private:
	cocos2d::PhysicsWorld *sceneWorld;

    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    static std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;

    MySprite* _mySprite;

    MapGenerator* _map_create;
    Circle* _circlePoint;

    void onEnter();
    void updateSec(float delta);
    void update_delSec(float delta);

    void onMouseMove(cocos2d::Event *event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

    bool onContactBegin(cocos2d::PhysicsContact& contact);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


    bool jumpHero;
    bool stopPhysicsWorld;
    float coef;
    
};

#endif // __WORLD_SCENE_H__
