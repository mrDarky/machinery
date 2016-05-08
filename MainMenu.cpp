#include "MainMenu.h"
#include "WorldScene.h"

USING_NS_CC;

Scene* mainMenu::createScene()
{
    auto scene = Scene::create();

    auto layer = mainMenu::create();

    scene->addChild(layer);
    return scene;
}

bool mainMenu::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = DrawNode::create();
    background->drawSolidRect(Vec2(visibleSize), Vec2(0,0), Color4F(Color3B(63, 92, 125)));

    this->addChild(background);

    auto startLabel = Label::createWithSystemFont("Start!", "Arial", 24);
    auto closeLabel = Label::createWithSystemFont("Exit", "Arial", 20);

    Vector<MenuItem*> MenuItems;

    auto menuItem_start = MenuItemLabel::create( startLabel,CC_CALLBACK_0(mainMenu::startGame, this) );
    menuItem_start->setPosition(Vec2(0, 50));

    auto menuItem_close = MenuItemLabel::create( closeLabel, CC_CALLBACK_0(mainMenu::closeGame, this) );


    MenuItems.pushBack(menuItem_start);
    MenuItems.pushBack(menuItem_close);

    auto menu = Menu::createWithArray(MenuItems);

    this->addChild(menu);



    return true;
}

void mainMenu::startGame()
{
	auto scene = WorldScene::createScene();
	Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1, scene));
}

void mainMenu::closeGame()
{
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    	exit(0);
	#endif
}