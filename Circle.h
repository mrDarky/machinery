#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "cocos2d.h"

class Circle
{

    public:
        Circle(cocos2d::Layer *layer);
        ~Circle();


        cocos2d::DrawNode* getCircle();
        cocos2d::DrawNode* getCircle_Sector();
        cocos2d::DrawNode* getFollowCircle();
        float getCircleOverload();
        void setCircleOverload(float change);
        void reloadSector_new();

        void setFocusVec(cocos2d::Vec2 coord);
        cocos2d::Vec2 getFocusVec();

        void setFocusAngle(float angle);
        float getFocusAngle();

    private:
        cocos2d::Size visibleSize;
        cocos2d::Vec2 origin; 

        cocos2d::DrawNode* circlePoint;
        cocos2d::DrawNode* reloadSector;
        cocos2d::DrawNode* followCircle;

        cocos2d::Vec2 newCoord;

        void drawSector(cocos2d::DrawNode* node, cocos2d::Vec2 origin, float radius, float angle_degree,
                cocos2d::Color4F fillColor, float borderWidth, unsigned int num_of_points);

        float circle_overload;
        float focusAngle;
    	
};

#endif // _CIRCLE_H_
