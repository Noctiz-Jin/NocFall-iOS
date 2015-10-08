#include "Guide.h"
#include "MainMenuScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

Scene* GuideScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GuideScene::create();
    scene->addChild(layer);
    return scene;
}

bool GuideScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    cocos2d::Vec2 center((cocos2d::Director::getInstance()->getVisibleSize().width / 2 + cocos2d::Director::getInstance()->getVisibleOrigin().x), (cocos2d::Director::getInstance()->getVisibleSize().height / 2 + cocos2d::Director::getInstance()->getVisibleOrigin().y));
    
    auto background = Sprite::create("MainMenu.png");
    background->setPosition(center);
    this->addChild(background);

    auto menuItem = MenuItemImage::create("Button_menu.png", "Button_menu_clicked.png", CC_CALLBACK_1(GuideScene::goToMainMenu, this));
    menuItem->setPosition(center.x, center.y - visibleSize.height*0.35);

    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    Guide_move();

    return true;
}

void GuideScene::Guide_move()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto gameTitleLabel= Label::createWithTTF("Tab left half of the screen to move left\nTab right half of the screen to move right\nDodge the falling fireballs\nCollect as many nuggets as possible\n     Have fun!", "Marker Felt.ttf", visibleSize.height * SCORE_FONT * 0.3);
    gameTitleLabel->setColor(Color3B::WHITE);
    gameTitleLabel->setPosition(Point((visibleSize.width / 2) + origin.x, visibleSize.height * 0.45 + origin.y));
    this->addChild(gameTitleLabel,10);
}

void GuideScene::goToMainMenu(cocos2d::Ref *sender)
{
    // create() is static and creates an instance of the class; createScene creates cocos2d::scene*
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("clickButton.mp3");
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionCrossFade::create(TRANSITION_TIME, scene));
}