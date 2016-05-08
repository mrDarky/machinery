#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__


#include "cocos2d.h"

class mainMenu : public cocos2d::Layer
{
public:


	static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    CREATE_FUNC(mainMenu);



    

    void startGame();

    void closeGame();
};

#endif // __MAIN_MENU_H__