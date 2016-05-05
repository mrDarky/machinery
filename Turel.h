#ifndef _TUREL_H_
#define _TUREL_H_

#include "cocos2d.h"


class Turel
{
    public:

        void addEvents();
        void followHero(cocos2d::Vec2 pos_turel);
        cocos2d::Sprite *getTurel();
        void add_Bullet(cocos2d::Vec2 pos_hero);
        static std::vector<Turel *> get_allTurel();

        static Turel* CreateStandTurel(cocos2d::Layer* layer, cocos2d::Vec2 pos_turel, bool orient, int type);
       
    private:

        Turel(cocos2d::Layer *layer, bool orient);
        ~Turel();


        cocos2d::Size visibleSize;
        cocos2d::Vec2 origin; 

        cocos2d::Layer *layer1;
    	cocos2d::Sprite *turel;
       // cocos2d::Vec2 
        cocos2d::Vector<cocos2d::Sprite *> vector_bullets;
        static std::vector<Turel *> all_turel;
        cocos2d::Sprite *turel_body1;

        cocos2d::Vec2 getPos_bullet();

        void createTurel_type1(cocos2d::Vec2 pos_turel);

        bool orientation;
        
        float angle;
        bool shoot;


       //static std::vector<cocos2d::Sprite> all_bullets;
    	
};

#endif // _TUREL_H_
