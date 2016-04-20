#ifndef _TUREL_H_
#define _TUREL_H_

#include "cocos2d.h"


class Turel
{
    public:

        void addEvents();
        void followHero(cocos2d::Vec2 pos_turel);
        cocos2d::Sprite *getTurel();
        void add_Bullet();

        static Turel* CreateStandTurel(cocos2d::Layer* layer, cocos2d::Vec2 pos_turel, bool orient, int type);
       
    private:

        Turel(cocos2d::Layer *layer, cocos2d::Vec2 pos_turel, bool orient, int type);
        ~Turel();


        cocos2d::Size visibleSize;
        cocos2d::Vec2 origin; 

        cocos2d::Layer *layer1;
    	cocos2d::Sprite *turel;
       // cocos2d::Vec2 
        cocos2d::Vector<cocos2d::Sprite *> vector_bullets;
        cocos2d::Sprite *turel_body1;

        cocos2d::Vec2 getPos_bullet();

        void createTurel_type1(cocos2d::Vec2 pos_turel, bool orient);

        


        float angle;
        bool shoot;
    	
};

#endif // _TUREL_H_
