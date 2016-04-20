#ifndef _MYSPRITE_H_
#define _MYSPRITE_H_

#include "cocos2d.h"

class MySprite : public cocos2d::Sprite
{
    public:
        MySprite(cocos2d::Layer *layer);
        ~MySprite();

        void addEvents();

        cocos2d::Sprite *returnHero();
        float returnRadius();

    private:
    	cocos2d::Sprite *hero;
    	cocos2d::Size visibleSize;
    	cocos2d::Vec2 origin;

    	float radius1;
    
};

#endif // _MYSPRITE_H_
