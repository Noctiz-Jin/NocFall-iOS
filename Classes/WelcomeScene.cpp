#include "WelcomeScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WelcomeScene::create();
    scene->addChild(layer);
    return scene;
}

bool WelcomeScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto welcomePic=Sprite::create("Starter_welcome_pic.png");
    welcomePic->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    this->addChild(welcomePic);
    
    auto noc=Sprite::create("Noc_stand.png");
    noc->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    this->addChild(noc,10);
    
    this->scheduleOnce(schedule_selector(WelcomeScene::GoToMainMenuScene), WELCOME_SCREEN_DISP_TIME);
    
    return true;
}

void WelcomeScene::GoToMainMenuScene(float delta)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}