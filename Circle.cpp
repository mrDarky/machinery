#include "Circle.h"
#include "Definitions.h"

USING_NS_CC;


Circle::Circle(cocos2d::Layer* layer)
{
  circle_overload = 0;
  circlePoint = DrawNode::create();
  circlePoint->drawCircle(Vec2(100,100), 200, 10, 60,false, Color4F::BLUE);
  circlePoint->setVisible(false);

  layer->addChild(circlePoint, 3);

  reloadSector = DrawNode::create();
  reloadSector->setVisible(false);
  drawSector(reloadSector, Vec2(100,100), 200, circle_overload, Color4F::RED, 3, 100);
  layer->addChild(reloadSector,4);

  followCircle = DrawNode::create();
  followCircle->drawCircle(Vec2(0,0), 10, 10, 60, false, Color4F::WHITE);
  followCircle->setVisible(false);

  layer->runAction(Follow::create(followCircle));
  layer->addChild(followCircle);

  eye_circle1 = DrawNode::create();
  eye_circle1->drawSolidCircle(Vec2(0,0), 7, 10, 60, 0.4f, 1.0f, Color4F::WHITE);
  //eye_circle1->setScaleX(eye_circle1->getContentSize().width*0.9);
  

  eye_circle2 = DrawNode::create();
  eye_circle2->drawSolidCircle(Vec2(0,0), 7, 10, 60, 0.4f, 1.0f, Color4F::WHITE);
  layer->addChild(eye_circle2);
  layer->addChild(eye_circle1);

}

Circle::~Circle(){}



void Circle::drawSector(cocos2d::DrawNode* node, cocos2d::Vec2 origin, float radius, float angle_degree,
                cocos2d::Color4F fillColor, float borderWidth, unsigned int num_of_points)
{
  if (!node)
  {
    return;
  }

  const cocos2d::Vec2 start = origin + cocos2d::Vec2{radius, 0};
  const auto angle_step = 2 * M_PI * angle_degree / 360.f / num_of_points;
  std::vector<cocos2d::Point> circle;

  //circle.emplace_back(origin);
  for (unsigned int i = 0; i <= num_of_points; i++)
  {
    auto rads = angle_step * i;
    auto x = origin.x + radius * cosf(rads);
    auto y = origin.y + radius * sinf(rads);
    circle.emplace_back(x, y);
  }

  //node->drawPolygon(circle.data(), circle.size(), fillColor, borderWidth, bordercolor);
  node->drawPoints(circle.data(), circle.size(), borderWidth, fillColor);
}


cocos2d::DrawNode* Circle::getCircle()
{
  return circlePoint;
}

cocos2d::DrawNode* Circle::getCircle_Sector()
{
  return reloadSector;
}

cocos2d::DrawNode* Circle::getFollowCircle()
{
  return followCircle;
}

cocos2d::DrawNode* Circle::getEye1Circle()
{
  return eye_circle1;
}

cocos2d::DrawNode* Circle::getEye2Circle()
{
  return eye_circle2;
}

float Circle::getCircleOverload()
{
  return circle_overload;
}
void Circle::setCircleOverload(float change)
{
  circle_overload=change;
}


void Circle::reloadSector_new()
{
  reloadSector->clear();
  drawSector(reloadSector, Vec2(100,100), 200, circle_overload, Color4F::RED, 4, 10*circle_overload);
}


void Circle::setFocusVec(cocos2d::Vec2 coord)
{
  newCoord = coord;
}

cocos2d::Vec2 Circle::getFocusVec()
{
  return newCoord;
}

void Circle::setFocusAngle(float angle)
{
  focusAngle = angle;
}

float Circle::getFocusAngle()
{
  return focusAngle;
}
