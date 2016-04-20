#include "Turel.h"
#include "MyBodyParser.h"



USING_NS_CC;

Turel* Turel::CreateStandTurel(cocos2d::Layer* layer, cocos2d::Vec2 pos_turel, bool orient, int type)
{
	Turel *mainTurel = new (std::nothrow) Turel(layer, pos_turel, orient, type);

	// if(mainTurel)
	// {
	 	return mainTurel;
//	}

	// delete mainTurel;
	// return nullptr;
}
 
void Turel::createTurel_type1(cocos2d::Vec2 pos_turel, bool orient)
{
	turel = Sprite::create("turel.png");
	
	if(orient)
		turel->setScale(-visibleSize.width/(turel->getContentSize().width)*0.15,visibleSize.width/(turel->getContentSize().height)*0.05);
	else
		turel->setScale(visibleSize.width/turel->getContentSize().width*0.15, visibleSize.width/turel->getContentSize().height*0.05);

	turel->setPosition(pos_turel);
	//turel->setScaleX

	auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(turel, "Turel", PhysicsMaterial( 0, 0, 0 ) ); 


	if ( spriteBody != nullptr )
    {
        spriteBody->setDynamic( false );
        turel->setPhysicsBody( spriteBody );
    }
	turel->setAnchorPoint(Vec2(1,0));
    layer1->addChild(turel);


    //add turel body
    turel_body1 = Sprite::create("turel_body1.png");

    if(orient)
    	turel_body1->setScale(visibleSize.width/(turel->getContentSize().width)*0.06,visibleSize.width/(turel->getContentSize().height)*0.02);
    else
    	turel_body1->setScale(-visibleSize.width/turel->getContentSize().width*0.06, visibleSize.width/turel->getContentSize().height*0.02);
    turel_body1->setPosition(pos_turel.x, pos_turel.y-turel_body1->getBoundingBox().size.height/4);

    MyBodyParser::getInstance()->parseJsonFile( "body/TurelBody1.json" );

    auto spriteBody1 = MyBodyParser::getInstance()->bodyFormJson(turel_body1, "TurelBody1", PhysicsMaterial( 0, 0, 0 ) );

    if ( spriteBody1 != nullptr )
    {
        spriteBody1->setDynamic( false );
        turel_body1->setPhysicsBody( spriteBody1 );
    }

    layer1->addChild(turel_body1);
}

Turel::Turel(cocos2d::Layer* layer, cocos2d::Vec2 pos_turel, bool orient, int type)
{

	layer1 = layer;
	shoot=true;

	visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    //add turel head

	MyBodyParser::getInstance()->parseJsonFile( "body/Turel.json" );
	
	switch(type)
	{
		case 1:
			createTurel_type1(pos_turel, orient);
			break;
	}
	
	
    MyBodyParser::getInstance()->parseJsonFile( "body/Turel.json" );


}

Turel::~Turel(){}

void Turel::addEvents()
{}

cocos2d::Sprite *Turel::getTurel()
{
	return turel;
}

void Turel::followHero(cocos2d::Vec2 pos_hero)
{
	Vec2 pos_turel = turel->getPosition();
	angle = atan((pos_hero.y-pos_turel.y)/(pos_hero.x-pos_turel.x))*57;

	if(pos_hero.x>pos_turel.x){
		angle = -angle;
		turel->setRotation(angle);
		shoot=true;
	}
	else
	{

		turel->setRotation(angle);
		shoot=false;
	}
}



cocos2d::Vec2 Turel::getPos_bullet()
{
	Vec2 pos_turel_start = turel->getPosition();
	Vec2 pos_turel_end = Vec2(turel->getPosition().x+turel->getContentSize().width*fabs(turel->getScaleX()), turel->getPosition().y);

	float coor1_x = pos_turel_end.x - pos_turel_start.x;
	float coor1_y = pos_turel_end.y - pos_turel_start.y;
	//CCLOG("%f", cos(angle));
	// if(angle<0)
	// {
	// 	angle=-angle;
	// }
	float formula1_x, formula1_y;
	formula1_x = cosf(angle/57)*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.x+50;
	if(angle<0){
		
		formula1_y = cosf((90-(-angle))/57)*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.y+turel->getContentSize().width/4*fabs(turel->getScaleY());
	}
	else
	{
		//formula1_x = cos(angle/57)*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.x;
		formula1_y = -cosf((90-angle)/57)*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.y+turel->getContentSize().width*0.01*fabs(turel->getScaleY());
	}

	return cocos2d::Vec2(formula1_x, formula1_y);
}

void Turel::add_Bullet()
{
	if(shoot)
	{
		auto bullet = Sprite::create("bullet1.png");
		bullet->setScale(-visibleSize.width/bullet->getContentSize().width*0.03, visibleSize.height/bullet->getContentSize().height*0.03);
		
		

		auto spriteBody_bullet = MyBodyParser::getInstance()->bodyFormJson(bullet, "bullet1", PhysicsMaterial( 0, 0, 0 ) ); 
	
		if ( spriteBody_bullet != nullptr )
	    {
	        spriteBody_bullet->setDynamic( true );
	        spriteBody_bullet->setVelocity(Vec2(1000*cosf(angle/57), -1000*sinf(angle/57)));
	        spriteBody_bullet->setGravityEnable(false);
	        spriteBody_bullet->setTag(5);
	        spriteBody_bullet->setContactTestBitmask(1);

	        bullet->setPhysicsBody( spriteBody_bullet );
	    }
	    bullet->setRotation(angle+7);
	    //bullet->setPosition(turel->getPosition().x+turel->getBoundingBox().size.width,
	    //						turel->getPosition().y+turel->getBoundingBox().size.height);
	    bullet->setPosition(getPos_bullet());
	
		vector_bullets.pushBack(bullet);
	
		layer1->addChild(bullet);
	}
}
