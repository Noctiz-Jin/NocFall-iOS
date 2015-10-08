#include "MainMenuScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"
#include "GameScene.h"
#include "Guide.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("MainMenuBGM.mp3", true);
    
    auto background = Sprite::create("MainMenu.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);
    
    auto gameTitleLabel= Label::createWithTTF("Trix Noc", "BoldTowne.otf", visibleSize.height * SCORE_FONT * 0.9);
    gameTitleLabel->setColor(Color3B(255, 0, 255));
    gameTitleLabel->setPosition(Point((visibleSize.width / 2)*0.69 + origin.x, visibleSize.height * 0.85 + origin.y));
    this->addChild(gameTitleLabel,10);
    
    auto TitleLabel= Label::createWithTTF("Underground Nuggets", "Garamondo.otf", visibleSize.height * SCORE_FONT * 0.4);
    TitleLabel->setColor(Color3B::YELLOW);
    TitleLabel->setPosition(Point((visibleSize.width / 2)*0.69 + origin.x, visibleSize.height * 0.79 + origin.y));
    this->addChild(TitleLabel,10);
    
    
    auto AchievementLabel= Label::createWithTTF("Trophy Gallery", "Marker Felt.ttf", visibleSize.height * SCORE_FONT * 0.4);
    AchievementLabel->setColor(Color3B(255, 0, 255));
    AchievementLabel->setPosition(Point(visibleSize.width / 2+ origin.x, visibleSize.height * 0.15 + origin.y));
    this->addChild(AchievementLabel,10);
    
    auto playItem = MenuItemImage::create("play_button.png", "play_button_clicked.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    auto guideItem = MenuItemImage::create("guide_button.png", "guide_button_clicked.png", CC_CALLBACK_1(MainMenuScene::GoToGuideScene, this));
    guideItem->setPosition(Point(visibleSize.width / 2 + origin.x, -visibleSize.height*0.1+visibleSize.height / 2 + origin.y));
    auto menu = Menu::create(playItem,guideItem,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    auto trix=Sprite::create("Noc_rightst.png");
    trix->setPosition(Point(visibleSize.width / 2 + origin.x-playItem->getContentSize().width/2+trix->getContentSize().width/2, visibleSize.height / 2 + origin.y+trix->getContentSize().height/2+playItem->getContentSize().height/2));
    this->addChild(trix,100);
    auto move_dis=playItem->getContentSize().width-trix->getContentSize().width;
    auto move_duration=TRIX_SPEED*move_dis;
    auto trix_move=MoveBy::create(move_duration,Point(move_dis,0));
    Vector<SpriteFrame*> trix_ani(2);
    trix_ani.pushBack(SpriteFrame::create("Noc_rightst.png", Rect(0,0,40,72)));
    trix_ani.pushBack(SpriteFrame::create("Noc_right.png", Rect(0,0,40,72)));
    auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
    auto anim_rr=Animate::create(ani);
    auto anim_r=RepeatForever::create(anim_rr);
    trix->runAction(anim_r);
    trix->runAction(Sequence::create(trix_move,RemoveSelf::create(true),nullptr));
    
    
    
    auto highScore = UserDefault::getInstance()->getIntegerForKey("HIGHSCORE", 0);
    auto tempHigh = cocos2d::__String::createWithFormat("Best Score: %d", highScore);
    auto highScoreLabel = Label::createWithTTF(tempHigh->getCString(), "Lucky7.otf", visibleSize.height * SCORE_FONT * 0.5);
    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.3 + origin.y));
    this->addChild(highScoreLabel);
    
    auto ach_1 = Sprite::create("Empty_ach.png");
    auto ach_2 = Sprite::create("Empty_ach.png");
    auto ach_3 = Sprite::create("Empty_ach.png");
    auto ach_4 = Sprite::create("Empty_ach.png");
    ach_1->setPosition(Point(visibleSize.width*0.2+origin.x, visibleSize.height*0.08 + origin.y));
    ach_2->setPosition(Point(visibleSize.width*0.4+origin.x, visibleSize.height*0.08+ origin.y));
    ach_3->setPosition(Point(visibleSize.width*0.6+origin.x, visibleSize.height*0.08 + origin.y));
    ach_4->setPosition(Point(visibleSize.width*0.8+origin.x, visibleSize.height*0.08 + origin.y));
    this->addChild(ach_1);
    this->addChild(ach_2);
    this->addChild(ach_3);
    this->addChild(ach_4);
    
    if (highScore>=TROPHY_1)
    {
        auto ach1=Sprite::create("BrownHat.png");
        ach1->setPosition(Point(visibleSize.width*0.2+origin.x, visibleSize.height*0.08 + origin.y));
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
    }
    
    if (highScore>=TROPHY_2)
    {
        auto ach2=Sprite::create("BrownHat.png");
        ach2->setPosition(Point(visibleSize.width*0.4+origin.x, visibleSize.height*0.08 + origin.y));
        this->addChild(ach2,50);
        Vector<SpriteFrame*> ach_an(4);
        ach_an.pushBack(SpriteFrame::create("WhiteHat.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("WhiteHat_mid.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("WhiteHat_shine.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("WhiteHat_mid.png", Rect(0,0,100,75)));
        auto ann=Animation::createWithSpriteFrames(ach_an,0.2f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=RepeatForever::create(anim_ll);
        ach2->runAction(anim_l);
    }
    
    if (highScore>=TROPHY_3)
    {
        auto ach3=Sprite::create("BlackHat.png");
        ach3->setPosition(Point(visibleSize.width*0.6+origin.x, visibleSize.height*0.08 + origin.y));
        this->addChild(ach3,50);
        Vector<SpriteFrame*> ach_an(4);
        ach_an.pushBack(SpriteFrame::create("BlackHat.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("BlackHat_mid.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("BlackHat_shine.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("BlackHat_mid.png", Rect(0,0,100,75)));
        auto ann=Animation::createWithSpriteFrames(ach_an,0.2f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=RepeatForever::create(anim_ll);
        ach3->runAction(anim_l);
    }
    
    if (highScore>=TROPHY_4)
    {
        auto ach4=Sprite::create("VioletHat.png");
        ach4->setPosition(Point(visibleSize.width*0.8+origin.x, visibleSize.height*0.08 + origin.y));
        this->addChild(ach4,50);
        Vector<SpriteFrame*> ach_an(4);
        ach_an.pushBack(SpriteFrame::create("VioletHat.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("VioletHat_mid.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("VioletHat_shine.png", Rect(0,0,100,75)));
        ach_an.pushBack(SpriteFrame::create("VioletHat_mid.png", Rect(0,0,100,75)));
        auto ann=Animation::createWithSpriteFrames(ach_an,0.2f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=RepeatForever::create(anim_ll);
        ach4->runAction(anim_l);
    }
    
    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref * sender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("clickButton.mp3");
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::GoToGuideScene(cocos2d::Ref * sender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("clickButton.mp3");
    auto scene = GuideScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}