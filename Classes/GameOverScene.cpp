#include "GameOverScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

unsigned long long dispScore = -1;

Scene* GameOverScene::createScene(unsigned long long score)
{
    dispScore = score;
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}


bool GameOverScene::init()
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
    
    auto tempScore = cocos2d::__String::createWithFormat("%llu", dispScore);
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "Lucky7.otf", visibleSize.height * SCORE_FONT * 2);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(center.x, center.y-visibleSize.height*0.04);
    this->addChild(scoreLabel);
    
    ///////////////
    // HIGHSCORE //
    ///////////////
    UserDefault *ref = UserDefault::getInstance();
    auto highScore = ref->getIntegerForKey("HIGHSCORE", 0);
    
    if (dispScore > highScore)
    {
        highScore = dispScore;
        ref->setIntegerForKey("HIGHSCORE", highScore);
    }
    
    ref->flush();
    
    auto tempHigh = cocos2d::__String::createWithFormat("Best Score: %d", highScore);
    highScoreLabel = Label::createWithTTF(tempHigh->getCString(), "Lucky7.otf", visibleSize.height * SCORE_FONT * 0.5);
    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.3 + origin.y));
    this->addChild(highScoreLabel);
    
    // Place the menus
    auto retryItem = MenuItemImage::create("Button_retry.png", "Button_retry_clicked.png", CC_CALLBACK_1(GameOverScene::goToGameScene, this));
    retryItem->setPosition(center.x-visibleSize.width*0.2, center.y - visibleSize.height*0.35);
    
    auto menuItem = MenuItemImage::create("Button_menu.png", "Button_menu_clicked.png", CC_CALLBACK_1(GameOverScene::goToMainMenu, this));
    menuItem->setPosition(center.x+visibleSize.width*0.2, center.y - visibleSize.height*0.35);
    
    auto menu = Menu::create(retryItem, menuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    
    
    if (dispScore<TROPHY_1)
    {
        auto ach = Sprite::create("Empty_ach.png");
        ach->setPosition(Point((visibleSize.width / 2)*0.69 + origin.x, visibleSize.height * 0.85 + origin.y));
        this->addChild(ach);
        auto gameTitleLabel= Label::createWithTTF("No Trophy", "Marker Felt.ttf", visibleSize.height * SCORE_FONT * 0.3);
        gameTitleLabel->setColor(Color3B::GRAY);
        gameTitleLabel->setPosition(Point((visibleSize.width / 2)*0.69 + origin.x, visibleSize.height * 0.75 + origin.y));
        this->addChild(gameTitleLabel,10);
    }
    
    if (dispScore>=TROPHY_1&&dispScore<TROPHY_2)
    {
        auto ach1=Sprite::create("BrownHat.png");
        ach1->setPosition(Point((visibleSize.width / 2)*0.69 + origin.x, visibleSize.height * 0.85 + origin.y));
        this->addChild(ach1,50);
        Vector<SpriteFrame*> ach_an(4);
        ach_an.pushBack(SpriteFrame::create("BrownHat.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("BrownHat_mid.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("BrownHat_shine.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("BrownHat_mid.png", Rect(0,0,100,75)));
        auto ann=Animation::createWithSpriteFrames(ach_an,0.2f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=RepeatForever::create(anim_ll);
        ach1->runAction(anim_l);
        auto gameTitleLabel= Label::createWithTTF("Brown Hat\n       the Gold Collector", "Marker Felt.ttf", visibleSize.height * SCORE_FONT * 0.4);
        gameTitleLabel->setColor(Color3B(152,77,0));
        gameTitleLabel->setPosition(Point((visibleSize.width / 2)*0.9 + origin.x, visibleSize.height * 0.75 + origin.y));
        this->addChild(gameTitleLabel,10);
    }
    
    if (dispScore>=TROPHY_2&&dispScore<TROPHY_3)
    {
        auto ach2=Sprite::create("BrownHat.png");
        ach2->setPosition(Point((visibleSize.width / 2)*0.69 + origin.x, visibleSize.height * 0.85 + origin.y));
        this->addChild(ach2,51);
        Vector<SpriteFrame*> ach_an(4);
        ach_an.pushBack(SpriteFrame::create("WhiteHat.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("WhiteHat_mid.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("WhiteHat_shine.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("WhiteHat_mid.png", Rect(0,0,100,75)));
        auto ann=Animation::createWithSpriteFrames(ach_an,0.2f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=RepeatForever::create(anim_ll);
        ach2->runAction(anim_l);
        auto gameTitleLabel= Label::createWithTTF("White Hat\n       the Millionaire", "Marker Felt.ttf", visibleSize.height * SCORE_FONT * 0.4);
        gameTitleLabel->setColor(Color3B::WHITE);
        gameTitleLabel->setPosition(Point((visibleSize.width / 2)*0.9 + origin.x, visibleSize.height * 0.75 + origin.y));
        this->addChild(gameTitleLabel,10);
    }
    
    if (dispScore>=TROPHY_3&&dispScore<TROPHY_4)
    {
        auto ach3=Sprite::create("BlackHat.png");
        ach3->setPosition(Point((visibleSize.width / 2)*0.69 + origin.x, visibleSize.height * 0.85 + origin.y));
        this->addChild(ach3,52);
        Vector<SpriteFrame*> ach_an(4);
        ach_an.pushBack(SpriteFrame::create("BlackHat.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("BlackHat_mid.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("BlackHat_shine.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("BlackHat_mid.png", Rect(0,0,100,75)));
        auto ann=Animation::createWithSpriteFrames(ach_an,0.2f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=RepeatForever::create(anim_ll);
        ach3->runAction(anim_l);
        auto gameTitleLabel= Label::createWithTTF("Black Hat\n       the Shadow Runner", "Finneon.otf", visibleSize.height * SCORE_FONT * 0.3);
        gameTitleLabel->setColor(Color3B::WHITE);
        gameTitleLabel->setPosition(Point((visibleSize.width / 2)*0.9 + origin.x, visibleSize.height * 0.75 + origin.y));
        this->addChild(gameTitleLabel,10);
    }
    
    if (dispScore>=TROPHY_4)
    {
        auto ach4=Sprite::create("VioletHat.png");
        ach4->setPosition(Point((visibleSize.width / 2)*0.69 + origin.x, visibleSize.height * 0.85 + origin.y));
        this->addChild(ach4,53);
        Vector<SpriteFrame*> ach_an(4);
        ach_an.pushBack(SpriteFrame::create("VioletHat.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("VioletHat_mid.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("VioletHat_shine.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("VioletHat_mid.png", Rect(0,0,100,75)));
        auto ann=Animation::createWithSpriteFrames(ach_an,0.2f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=RepeatForever::create(anim_ll);
        ach4->runAction(anim_l);
        auto gameTitleLabel= Label::createWithTTF("Violet Hat\n       the Trix Noc", "BoldTowne.otf", visibleSize.height * SCORE_FONT * 0.6);
        gameTitleLabel->setColor(Color3B(255,0,255));
        gameTitleLabel->setPosition(Point((visibleSize.width / 2)*0.9 + origin.x, visibleSize.height * 0.75 + origin.y));
        this->addChild(gameTitleLabel,10);
    }
    
    
    
    return true;
}

void GameOverScene::goToMainMenu(cocos2d::Ref *sender)
{
    // create() is static and creates an instance of the class; createScene creates cocos2d::scene*
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("clickButton.mp3");
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionCrossFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::goToGameScene(cocos2d::Ref *sender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("clickButton.mp3");
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFadeBL::create(TRANSITION_TIME, scene));
}
