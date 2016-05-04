#include "Turel.h"
#include "MyBodyParser.h"



USING_NS_CC;

Turel* Turel::CreateStandTurel(cocos2d::Layer* layer, cocos2d::Vec2 pos_turel, bool orient, int type)
{
	Turel *mainTurel = new (std::nothrow) Turel(layer, orient);


	 //add turel head

	MyBodyParser::getInstance()->parseJsonFile( "body/Turel.json" );
	
	switch(type)
	{
		case 1:
			mainTurel->createTurel_type1(pos_turel);
			break;
	}


	all_turel.insert(all_turel.end(), mainTurel);
	return mainTurel;
}
 
void Turel::createTurel_type1(cocos2d::Vec2 pos_turel)
{
	turel = Sprite::create("turel.png");
	
	
	if(orientation)
		turel->setScale(-visibleSize.width/(turel->getContentSize().width)*0.15,visibleSize.width/(turel->getContentSize().height)*0.05);
	else
		turel->setScale(visibleSize.width/turel->getContentSize().width*0.15, visibleSize.width/turel->getContentSize().height*0.05);

	turel->setPosition(pos_turel);
	
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

    if(orientation)
    	turel_body1->setScale(visibleSize.width/(turel->getContentSize().width)*0.06,visibleSize.width/(turel->getContentSize().height)*0.02);
    else
    	turel_body1->setScale(-visibleSize.width/turel->getContentSize().width*0.06, visibleSize.width/turel->getContentSize().height*0.02);
    turel_body1->setPosition(pos_turel.x, pos_turel.y-turel_body1->getBoundingBox().size.height/4);

    //MyBodyParser::getInstance()->parseJsonFile( "body/TurelBody1.json" );

    auto spriteBody1 = MyBodyParser::getInstance()->bodyFormJson(turel_body1, "TurelBody1", PhysicsMaterial( 0, 0, 0 ) );

    if ( spriteBody1 != nullptr )
    {
        spriteBody1->setDynamic( false );
        turel_body1->setPhysicsBody( spriteBody1 );
    }

    layer1->addChild(turel_body1);
}

Turel::Turel(cocos2d::Layer* layer, bool orient)
{

	layer1 = layer;
	shoot=true;
	orientation=orient;

	visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

   

}

Turel::~Turel(){
	for(unsigned i=0; i< all_turel.size(); ++i)
	{
		delete[] all_turel[i];
	}
	
}

void Turel::addEvents()
{}

cocos2d::Sprite *Turel::getTurel()
{
	return turel;
}

void Turel::followHero(cocos2d::Vec2 pos_hero)
{
	Vec2 pos_turel = turel->getPosition();

	angle = CC_RADIANS_TO_DEGREES(atan((pos_hero.y-pos_turel.y)/(pos_hero.x-pos_turel.x)));


	if(pos_hero.x > pos_turel.x){
		if(orientation)
		{	
			angle = -(angle-5);
			turel->setRotation(angle);
			shoot=true;
		}
		else
		{
			turel->setRotation(angle);
			shoot=false;
		}
	}
	else
	{
		if(orientation)
		{
			turel->setRotation(angle);
			shoot=false;
		}
		else
		{
			angle = -(angle+5);
			turel->setRotation(angle);
			shoot=true;
		}
		
	}
	
}



cocos2d::Vec2 Turel::getPos_bullet()
{
	Vec2 pos_turel_start = turel->getPosition();
	Vec2 pos_turel_end = Vec2(turel->getPosition().x+turel->getContentSize().width*fabs(turel->getScaleX()), turel->getPosition().y);

	float coor1_x = pos_turel_end.x - pos_turel_start.x;
	float coor1_y = pos_turel_end.y - pos_turel_start.y+turel->getBoundingBox().size.height;
	//CCLOG("%f", cos(angle));
	// if(angle<0)
	// {
	// 	angle=-angle;
	// }
	float formula1_x, formula1_y;
	if(orientation)
		formula1_x = cosf(CC_DEGREES_TO_RADIANS(angle))*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.x;
	else
		formula1_x = -cosf(CC_DEGREES_TO_RADIANS(angle))*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.x;
	
	if(angle<0){
		//CCLOG("%f", angle);
		if(orientation)
		{
			formula1_y = cosf(CC_DEGREES_TO_RADIANS(90+angle))*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.y+turel->getBoundingBox().size.height/4+10;
		}
		else
		{
			formula1_y = -30-cosf(CC_DEGREES_TO_RADIANS(90+angle))*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.y+turel->getContentSize().width/4*fabs(turel->getScaleY());
		}
	}
	else
	{
		if(orientation)
			formula1_y = -cosf((90-angle)/57)*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.y+turel->getContentSize().width*0.01*fabs(turel->getScaleY())+30;
		else 
			formula1_y = cosf((90-angle)/57)*sqrtf(coor1_x*coor1_x+coor1_y*coor1_y)+pos_turel_start.y+turel->getContentSize().width*0.01*fabs(turel->getScaleY())+40;
	}

	return cocos2d::Vec2(formula1_x, formula1_y);
}

void Turel::add_Bullet()
{
	if(shoot)
	{
		auto bullet = Sprite::create("bullet1.png");
		if(orientation)
			bullet->setScale(-visibleSize.width/bullet->getContentSize().width*0.015, visibleSize.height/bullet->getContentSize().height*0.015);
		else
			bullet->setScale(visibleSize.width/bullet->getContentSize().width*0.015, visibleSize.height/bullet->getContentSize().height*0.015);
		
		

		auto spriteBody_bullet = MyBodyParser::getInstance()->bodyFormJson(bullet, "bullet1", PhysicsMaterial( 0, 0, 0 ) ); 
	
		if ( spriteBody_bullet != nullptr )
	    {
	        spriteBody_bullet->setDynamic( true );
	        if(orientation)
	        	spriteBody_bullet->setVelocity(Vec2(1000*cosf(angle/57), -1000*sinf(angle/57)));
	        else
	        	spriteBody_bullet->setVelocity(Vec2(-1000*cosf(angle/57), 1000*sinf(angle/57)));

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

std::vector<Turel *> Turel::get_allTurel()
{
	return all_turel;
}


std::vector<Turel *> Turel::all_turel;