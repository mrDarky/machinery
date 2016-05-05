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
	turel = Sprite::create("body/turel.png");
	
	
	if(orientation)
		turel->setScale(-visibleSize.width/(turel->getContentSize().width)*0.12,visibleSize.width/(turel->getContentSize().height)*0.03);
	else
		turel->setScale(visibleSize.width/turel->getContentSize().width*0.12, visibleSize.width/turel->getContentSize().height*0.03);

	turel->setPosition(pos_turel);
	
	auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(turel, "Turel", PhysicsMaterial( 0, 0, 0 ) ); 


	if ( spriteBody != nullptr )
    {
        spriteBody->setDynamic( false );
        turel->setPhysicsBody( spriteBody );
    }
	turel->setAnchorPoint(Vec2(1,0.5));
    


    //add turel body
    turel_body1 = Sprite::create("turel_body1.png");

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

Turel::Turel(cocos2d::Layer* layer, bool orient)
{

	layer1 = layer;
	shoot=true;
	orientation=orient;

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

void Turel::followHero(cocos2d::Vec2 pos_hero)
{
	Vec2 pos_turel = turel->getPosition();
	angle = atanf((pos_hero.y-pos_turel.y)/(pos_hero.x-pos_turel.x));


	if(pos_hero.x > pos_turel.x){
		if(orientation)
		{	
			turel->setRotation(CC_RADIANS_TO_DEGREES(-angle));
			shoot=true;
		}
		else
		{
			turel->setRotation(CC_RADIANS_TO_DEGREES(angle));
			shoot=false;
		}
	}
	else
	{
		if(orientation)
		{
			turel->setRotation(CC_RADIANS_TO_DEGREES(angle));
			shoot=false;
		}
		else
		{
			turel->setRotation(CC_RADIANS_TO_DEGREES(-angle));
			shoot=true;
		}
		
	}
	
}



cocos2d::Vec2 Turel::getPos_bullet()
{

	float coor1_x = turel->getContentSize().width*fabs(turel->getScaleX())+10;
	float formula1_x, formula1_y;

		if(orientation)
		{
			formula1_x = cosf(angle)*coor1_x+turel->getPosition().x;
			formula1_y = sinf(angle)*coor1_x + turel->getPosition().y;
		}
		else
		{
			formula1_x = -cosf(angle)*coor1_x+turel->getPosition().x;
			formula1_y = -sinf(angle)*coor1_x+turel->getPosition().y;
		}

	return cocos2d::Vec2(formula1_x, formula1_y);
}

void Turel::add_Bullet(cocos2d::Vec2 pos_hero)
{

	float length1 = sqrtf((pos_hero.x-turel->getPosition().x)*(pos_hero.x-turel->getPosition().x)+(pos_hero.y-turel->getPosition().y)*(pos_hero.y-turel->getPosition().y));
	
	if(shoot && length1<1000)
	{
		auto bullet = Sprite::create("bullet1.png");
		if(orientation)
			bullet->setScale(-visibleSize.width/bullet->getContentSize().width*0.015, visibleSize.height/bullet->getContentSize().height*0.015);
		else
			bullet->setScale(visibleSize.width/bullet->getContentSize().width*0.015, visibleSize.height/bullet->getContentSize().height*0.015);
		
		bullet->setPosition(getPos_bullet());

		auto spriteBody_bullet = MyBodyParser::getInstance()->bodyFormJson(bullet, "bullet1", PhysicsMaterial( 0, 0, 0 ) ); 
	
		if ( spriteBody_bullet != nullptr )
	    {
	        spriteBody_bullet->setDynamic( true );
	        if(orientation)
	        	spriteBody_bullet->setVelocity( Vec2(200*cosf(angle), 200*sinf(angle) ));
	        else	
	        	spriteBody_bullet->setVelocity(Vec2(-200*cosf(angle), -200*sinf(angle)));

	        spriteBody_bullet->setGravityEnable(false);
	        spriteBody_bullet->setTag(5);
	        spriteBody_bullet->setContactTestBitmask(1);

   			bullet->setRotation(CC_RADIANS_TO_DEGREES(-angle));
	        bullet->setPhysicsBody( spriteBody_bullet );
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