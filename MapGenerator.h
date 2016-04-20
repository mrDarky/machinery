#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include "cocos2d.h"

class MapGenerator 
{
    public:
        MapGenerator(cocos2d::Layer *layer);
        ~MapGenerator();
    private:
        cocos2d::Size visibleSize;
        cocos2d::Vec2 origin; 

        cocos2d::Layer *layer1;
        void createBoxBlock1(int n, cocos2d::Vec2 start_value, bool xORy, bool jumpHero);

        cocos2d::Vec2 end_point;
    	
};

#endif // _MAP_GENERATOR_H_
