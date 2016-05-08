#include "Turel.h"
#include "MyBodyParser.h"



USING_NS_CC;

Turel* Turel::CreateStandTurel(cocos2d::Layer* layer, cocos2d::Vec2 pos_turel, Vec2 orient, int type)
{
	Turel *mainTurel = new (std::nothrow) Turel();

	mainTurel->layer1 = layer;
	mainTurel->vec2_angle=orient;
	if(orient.x<90||orient.x>270)
		mainTurel->orientation = true;
	else if(orient.x==90||orient.x==270)
		mainTurel->orientation = (orient.y>orient.x)?false:true;
	else
		mainTurel->orientation = false;

	 //add turel head
    MyBodyParser::getInstance()->parseJsonFile( "body/Turel.json" ); 	
	
	switch(type)
	{
		case 1:
			mainTurel->rotation=true;
			mainTurel->createTurel_type1(pos_turel);
			break;
		case 2:
			mainTurel->follow=true;
			mainTurel->createTurel_type2(pos_turel);
			break;
		case 3:
			mainTurel->rotation=true;
			mainTurel->createTurel_type3(pos_turel);
			break;
	}


	all_turel.insert(all_turel.end(), mainTurel);
	return mainTurel;
}
 
void Turel::createTurel_type1(Vec2 pos_turel)
{
	turel = Sprite::create("body/turel.png");
	
	
	if(orientation)
		turel->setScale(-visibleSize.width/(turel->getContentSize().width)*0.12,visibleSize.width/(turel->getContentSize().height)*0.03);
	else
		turel->setScale(-visibleSize.width/turel->getContentSize().width*0.12, -visibleSize.width/turel->getContentSize().height*0.03);

	turel->setPosition(pos_turel);
	
	auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(turel, "Turel", PhysicsMaterial( 0, 0, 0 ) ); 


	if ( spriteBody != nullptr )
    {
        spriteBody->setDynamic( false );
        turel->setPhysicsBody( spriteBody );
    }
	turel->setAnchorPoint(Vec2(1,0.5));
    

    //add turel body
    auto turel_body1 = Sprite::create("turel_body1.png");

    if(orientation){
    	turel_body1->setScale(visibleSize.width/(turel->getContentSize().width)*0.07,visibleSize.width/(turel->getContentSize().height)*0.012);
    	turel_body1->setPosition(pos_turel.x-33, pos_turel.y-turel_body1->getBoundingBox().size.height/2+30);
    }
    else{
    	turel_body1->setScale(-visibleSize.width/turel->getContentSize().width*0.07, visibleSize.width/turel->getContentSize().height*0.012);
    	turel_body1->setPosition(pos_turel.x+33, pos_turel.y-turel_body1->getBoundingBox().size.height/2+30);
    }
    

    auto spriteBody1 = MyBodyParser::getInstance()->bodyFormJson(turel_body1, "TurelBody1", PhysicsMaterial( 0, 0, 0 ) );

    if ( spriteBody1 != nullptr )
    {
        spriteBody1->setDynamic( false );
        turel_body1->setPhysicsBody( spriteBody1 );
    }

    layer1->addChild(turel_body1);
    layer1->addChild(turel);
}

void Turel::createTurel_type2(Vec2 pos_turel)
{
	turel = Sprite::create("body/flight_turel1.png");
	turel->setPosition(pos_turel);
	turel->setScale(50/turel->getContentSize().width, 100/turel->getContentSize().height);

	auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(turel, "Flight_Turel1", PhysicsMaterial(0,0,0));

	if ( spriteBody != nullptr )
    {
    	spriteBody->setRotationEnable(false);
        spriteBody->setDynamic(true);
        spriteBody->setGravityEnable(false);
        turel->setPhysicsBody( spriteBody );
    }

    layer1->addChild(turel);
}
void Turel::createTurel_type3(Vec2 pos_turel)
{
	turel = Sprite::create("body/turel3.png");
	turel->setPosition(pos_turel);
	turel->setScale(-150/turel->getContentSize().width, 37.5/turel->getContentSize().height);

	auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(turel, "Turel3", PhysicsMaterial(0,0,0));

	if ( spriteBody != nullptr )
    {
        spriteBody->setDynamic(false);
        turel->setPhysicsBody( spriteBody );
    }
    turel->setAnchorPoint(Vec2(1,0.5));

    

    auto turel_body1 = DrawNode::create();
    turel_body1->drawSolidRect(Vec2(5,30), Vec2(0,0), Color4F::BLACK);
    turel_body1->drawSolidCircle(Vec2(2.5,0), 10, 10, 60, Color4F::BLACK);

    turel_body1->setPosition(pos_turel.x-2.5, pos_turel.y);




    //add turel body
 //    auto turel_body1 = Sprite::create("body/turel_body2.png");

	// turel_body1->setScale(100/turel->getContentSize().width,50/turel->getContentSize().height);
	// turel_body1->setPosition(pos_turel.x, pos_turel.y);

 //    auto spriteBody1 = MyBodyParser::getInstance()->bodyFormJson(turel_body1, "TurelBody2", PhysicsMaterial( 0, 0, 0 ) );

 //    if ( spriteBody1 != nullptr )
 //    {
 //        spriteBody1->setDynamic( false );
 //        turel_body1->setPhysicsBody( spriteBody1 );
 //    }

	 layer1->addChild(turel_body1);    
	 layer1->addChild(turel);
}
Turel::Turel()
{
	shoot=false;
	rotation=false;
	follow=false;
	angle=0;
	length_max=1000;
	visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

Turel::~Turel(){
	// for(unsigned i=0; i< all_turel.size(); ++i)
	// {
	// 	delete[] all_turel[i];
	// }
	
}

void Turel::addEvents()
{}

cocos2d::Sprite *Turel::getTurel()
{
	return turel;
}


bool Turel::checkShoot(cocos2d::Vec2 pos)
{
	float length1 = sqrtf((pos.x-turel->getPosition().x)*(pos.x-turel->getPosition().x)+(pos.y-turel->getPosition().y)*(pos.y-turel->getPosition().y));
	// check angle for shootiong
	if(length1<length_max)
	{
		
		if(vec2_angle.y<vec2_angle.x)
		{
			if((CC_RADIANS_TO_DEGREES(angle)>=vec2_angle.x && cosf(angle)>=cosf(CC_DEGREES_TO_RADIANS(vec2_angle.x))) 
				|| (CC_RADIANS_TO_DEGREES(angle)<=vec2_angle.y && cosf(angle)>=cosf(CC_DEGREES_TO_RADIANS(vec2_angle.y))) ){
				return true;
			}else{
				return false;
			}
		}
		else
		{
			if(CC_RADIANS_TO_DEGREES(angle)>=vec2_angle.x && CC_RADIANS_TO_DEGREES(angle)<=vec2_angle.y)
				return true;
			else
				return false;
		}
	}

	return  false;
}

float Turel::getAngle(cocos2d::Vec2 pos)
{
	Vec2 pos_turel = turel->getPosition();

	float angle1;

	if(pos.x > pos_turel.x){
		if(pos.y>pos_turel.y)
			angle1 = atanf((pos.y-pos_turel.y)/(pos.x-pos_turel.x));  
		else
			angle1 = CC_DEGREES_TO_RADIANS(360)+atanf((pos.y-pos_turel.y)/(pos.x-pos_turel.x)); 
	}
	else
	{
		if(pos.y>pos_turel.y)
			angle1 = CC_DEGREES_TO_RADIANS(180)+atanf((pos.y-pos_turel.y)/(pos.x-pos_turel.x)); 
		else
			angle1 = CC_DEGREES_TO_RADIANS(180)+atanf((pos.y-pos_turel.y)/(pos.x-pos_turel.x)); 
	}

	return angle1;
}

void Turel::followHero(cocos2d::Vec2 pos_hero)
{

	angle = getAngle(pos_hero);

	if(shoot && rotation && checkShoot(pos_hero)){
		
		turel->setRotation(CC_RADIANS_TO_DEGREES(-angle));	
	}

	if(follow){
		float angle1 = getAngle(Vec2(pos_hero.x, pos_hero.y+200));
		
		float length = sqrtf((pos_hero.x-turel->getPosition().x)*(pos_hero.x-turel->getPosition().x)+(pos_hero.y+200-turel->getPosition().y)*(pos_hero.y+200-turel->getPosition().y));
		if(length >= 2.0)
			turel->getPhysicsBody()->setVelocity( Vec2(200*cos(angle1), 200*sin(angle1)) );
		else
			turel->getPhysicsBody()->setVelocity( Vec2(0, 0) );
		//turel->setPosition( turel->getPosition().x+cosf(angle1), turel->getPosition().y+sinf(angle1) );
	}
}



cocos2d::Vec2 Turel::getPos_bullet()
{
	float coor1_x = turel->getContentSize().width*fabs(turel->getScaleX())+10;
	float formula1_x = cosf(angle)*coor1_x+turel->getPosition().x;
	float formula1_y = sinf(angle)*coor1_x + turel->getPosition().y;

	return cocos2d::Vec2(formula1_x, formula1_y);
}

void Turel::add_Bullet(cocos2d::Vec2 pos_hero)
{

	shoot = checkShoot(pos_hero);
	
	if(shoot)
	{

		auto bullet = Sprite::create("bullet1.png");

		bullet->setScale(-visibleSize.width/bullet->getContentSize().width*0.015, visibleSize.height/bullet->getContentSize().height*0.015);
		
		auto spriteBody_bullet = MyBodyParser::getInstance()->bodyFormJson(bullet, "bullet1", PhysicsMaterial( 0, 0, 0 ) );
		if ( spriteBody_bullet != nullptr )
	    {
	        spriteBody_bullet->setDynamic( true );
			spriteBody_bullet->setVelocity( Vec2(500*cosf(angle), 500*sinf(angle) ));
	        spriteBody_bullet->setGravityEnable(false);
	        spriteBody_bullet->setTag(5);
	        spriteBody_bullet->setContactTestBitmask(1);

   			
	        bullet->setPhysicsBody( spriteBody_bullet );
	    }

	    if(rotation)
		{
			bullet->setPosition(getPos_bullet());
			bullet->setRotation(CC_RADIANS_TO_DEGREES(-angle));
		}
		else
		{
			bullet->setPosition(turel->getPosition().x, turel->getPosition().y-turel->getBoundingBox().size.height/2-10);
			bullet->setRotation(90);
		}


		vector_bullets.pushBack(bullet);
	
		layer1->addChild(bullet);
	}
}

std::vector<Turel *> Turel::get_allTurel()
{
	return all_turel;
}


std::vector<Turel *> Turel::all_turel;