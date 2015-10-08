#include "GameScene.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "Trix.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0,-150));
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    visible_height=visibleSize.height;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("GBGM.mp3", true);
    
    Size edge_box=visibleSize;
    edge_box.height=edge_box.height+200;
    
    Size dead_Line=visibleSize;
    dead_Line.height=1;
    
    auto backgroundSprite = Sprite::create( "BlankBG.png" );
    backgroundSprite->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->addChild(backgroundSprite);
    
    auto up_spike=Sprite::create("up_spike.png");
    up_spike->setPosition(Point( visibleSize.width/2+origin.x, visibleSize.height + origin.y-up_spike->getContentSize().height/2));
    Vector<SpriteFrame*> upspike_an(2);
    upspike_an.pushBack(SpriteFrame::create("up_spike.png", Rect(0,0,1209,117)));
    upspike_an.pushBack(SpriteFrame::create("up_spike_2.png", Rect(0,0,1209,117)));
    auto ani=Animation::createWithSpriteFrames(upspike_an,0.1f);
    auto anim=Animate::create(ani);
    auto anim_s=RepeatForever::create(anim);
    up_spike->runAction(anim_s);
    this->addChild(up_spike,101);

    auto edgeBody = PhysicsBody::createEdgeBox(edge_box, PHYSICSBODY_MATERIAL_EDGE, 1);
    edgeBody->isResting();
    edgeBody->setCollisionBitmask(WALL_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(WALL_CONTACT_BITMASK);
    auto deadLine= PhysicsBody::createEdgeBox(dead_Line);
    deadLine->isResting();
    deadLine->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    deadLine->setContactTestBitmask(OBSTACLE_CONTACT_BITMASK);
    auto deadLine_TOP= PhysicsBody::createEdgeBox(dead_Line);
    deadLine_TOP->isResting();
    deadLine_TOP->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    deadLine_TOP->setContactTestBitmask(OBSTACLE_CONTACT_BITMASK);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point( visibleSize.width / 2 + origin.x,  visibleSize.height / 2+ origin.y ));
    edgeNode->setPhysicsBody(edgeBody);
    auto deadNode= Node::create();
    deadNode->setPosition(Point( visibleSize.width / 2 + origin.x, origin.y-80 ));
    deadNode->setPhysicsBody(deadLine);
    this->addChild(edgeNode);
    this->addChild(deadNode);
    auto deadNode_TOP= Node::create();
    deadNode_TOP->setPosition(Point( visibleSize.width / 2 + origin.x, origin.y+visibleSize.height-110 ));
    deadNode_TOP->setPhysicsBody(deadLine_TOP);
    this->addChild(deadNode_TOP);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::Touch, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::TouchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    

    trix =new Trix(this);
    this->scheduleOnce(schedule_selector(GameScene::startBrick), 0);
    this->schedule(schedule_selector(GameScene::spawnBrick),visibleSize.height*BRICK_SPAWN_FREQ);
    this->schedule(schedule_selector(GameScene::spawnDBrick),visibleSize.height*DBRICK_SPAWN_FREQ);
    
    //this->schedule(schedule_selector(GameScene::spawnFireBall),visible_height*FIREBALL_SPAWN_FREQ);
    //Test fireball speed

    
    this->scheduleOnce(schedule_selector(GameScene::lastwarning1), 7);
    this->schedule(schedule_selector(GameScene::spawnFireBall),visible_height*FIREBALL_SPAWN_FREQ,2,10);
    this->scheduleOnce(schedule_selector(GameScene::lastwarning2), 27);
    this->schedule(schedule_selector(GameScene::spawnFireBall_2),visible_height*(FIREBALL_SPAWN_FREQ-0.0005),5,30);
    this->scheduleOnce(schedule_selector(GameScene::lastwarning3), 57);
    this->schedule(schedule_selector(GameScene::spawnFireBall_3),visible_height*(FIREBALL_SPAWN_FREQ-0.001),8,60);
    this->scheduleOnce(schedule_selector(GameScene::lastwarning4), 87);
    this->schedule(schedule_selector(GameScene::spawnFireBall_4),visible_height*(FIREBALL_SPAWN_FREQ-0.0015),19,90);
    
    
    this->scheduleOnce(schedule_selector(GameScene::lastwarning), 120);
    this->scheduleOnce(schedule_selector(GameScene::lastrush),125);

    this->scheduleUpdate();
    
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
    __String *tempScore = cocos2d::__String::createWithFormat("%llu", m_score);
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "Lucky7.otf", visibleSize.height * SCORE_FONT);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.8 + origin.y);
    this->addChild(scoreLabel, 3);
    return true;
}



void GameScene::lastwarning(float delta)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    warning=Sprite::create("warning.png");
    warning->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(warning,4);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Warning.mp3");
    Vector<SpriteFrame*> warning_ani(2);
    warning_ani.pushBack(SpriteFrame::create("warning.png", Rect(0,0,360,54)));
    warning_ani.pushBack(SpriteFrame::create("warning_2.png", Rect(0,0,360,54)));
    auto ani=Animation::createWithSpriteFrames(warning_ani,0.1f);
    auto anim_rr=Animate::create(ani);
    auto anim_r=RepeatForever::create(anim_rr);
    warning->runAction(anim_r);
    
    warningsign=1;
    
}
void GameScene::lastwarning1(float delta)
{
    lastwarning(delta);
    
}
void GameScene::lastwarning2(float delta)
{
    lastwarning(delta);
    
}
void GameScene::lastwarning3(float delta)
{
    lastwarning(delta);
    
}
void GameScene::lastwarning4(float delta)
{
    lastwarning(delta);
    
}




bool GameScene::Touch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if (touch->getLocation().x<origin.x+visibleSize.width/2 && Trix_dead==0)
    {
        trix->leftm();
        Vector<SpriteFrame*> trix_ani(2);
        trix_ani.pushBack(SpriteFrame::create("Noc_leftst.png", Rect(0,0,40,72)));
        trix_ani.pushBack(SpriteFrame::create("Noc_left.png", Rect(0,0,40,72)));
        auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
        auto anim_rr=Animate::create(ani);
        auto anim_r=RepeatForever::create(anim_rr);
        trix->M_trix->runAction(anim_r);
    }

    if (touch->getLocation().x>origin.x+visibleSize.width/2 && Trix_dead==0)
    {
        trix->rightm();
        Vector<SpriteFrame*> trix_ani(2);
        trix_ani.pushBack(SpriteFrame::create("Noc_rightst.png", Rect(0,0,40,72)));
        trix_ani.pushBack(SpriteFrame::create("Noc_right.png", Rect(0,0,40,72)));
        auto ani=Animation::createWithSpriteFrames(trix_ani,0.1f);
        auto anim_rr=Animate::create(ani);
        auto anim_r=RepeatForever::create(anim_rr);
        trix->M_trix->runAction(anim_r);


    }
    if (Trix_dead==1)
    {
        trix->dead();
    }
    if (Trix_dead==2)
    {
        trix->dead_fire();
    }

    return true;
}

void GameScene::TouchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    trix->stop();
    trix->stop_ani();
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    auto *a = contact.getShapeA()->getBody();
    auto *b = contact.getShapeB()->getBody();
    
    
    if (( TRIX_CONTACT_BITMASK == a->getContactTestBitmask()&& OBSTACLE_CONTACT_BITMASK == b->getContactTestBitmask() ) || ( TRIX_CONTACT_BITMASK == b->getContactTestBitmask()&& OBSTACLE_CONTACT_BITMASK == a->getContactTestBitmask()))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameOver.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        this->unscheduleAllSelectors();
        Trix_dead=1;
        trix->dead();
        auto scene = GameOverScene::createScene(m_score);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    
    
    
    if (( TRIX_CONTACT_BITMASK == a->getContactTestBitmask()&& FIREBALL_CONTACT_BITMASK == b->getContactTestBitmask() ) || ( TRIX_CONTACT_BITMASK == b->getContactTestBitmask()&& FIREBALL_CONTACT_BITMASK == a->getContactTestBitmask()))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameOver.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        this->unscheduleAllSelectors();
        Trix_dead=2;
        trix->dead_fire();
        
        Vector<SpriteFrame*> fireball_an;
        fireball_an.pushBack(SpriteFrame::create("Explosion.png", Rect(0,0,136,144)));
        auto ann=Animation::createWithSpriteFrames(fireball_an,0.15f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=RepeatForever::create(anim_ll);
        if (b->getContactTestBitmask() == FIREBALL_CONTACT_BITMASK)
        {
            b->getNode()->stopAllActions();
            b->getNode()->runAction(anim_l);
        }
        if (a->getContactTestBitmask() == FIREBALL_CONTACT_BITMASK)
        {
            a->getNode()->stopAllActions();
            a->getNode()->runAction(anim_l);
        }

        auto scene = GameOverScene::createScene(m_score);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    
    
    if ((a->getContactTestBitmask() == TRIX_CONTACT_BITMASK && b->getContactTestBitmask() == BRICK_DUMMY_CONTACT_BITMASK)
        ||
        (b->getContactTestBitmask() == TRIX_CONTACT_BITMASK && a->getContactTestBitmask() == BRICK_DUMMY_CONTACT_BITMASK))
    {
        if (b->getContactTestBitmask() == BRICK_DUMMY_CONTACT_BITMASK)
        {
            b->getNode()->removeFromParentAndCleanup(true);

        }
        if (a->getContactTestBitmask() == BRICK_DUMMY_CONTACT_BITMASK)
        {
            a->getNode()->removeFromParentAndCleanup(true);
        }
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Coin.mp3");
        m_score++;
        
        auto tempScore = __String::createWithFormat("%llu", m_score);
        scoreLabel->setString(tempScore->getCString());
    }
    
    if ((a->getContactTestBitmask() == TRIX_CONTACT_BITMASK && b->getContactTestBitmask() == BRICK_CONTACT_BITMASK)
        ||
        (b->getContactTestBitmask() == TRIX_CONTACT_BITMASK && a->getContactTestBitmask() == BRICK_CONTACT_BITMASK))
    {
        Vector<SpriteFrame*> brick_an;
        brick_an.pushBack(SpriteFrame::create("brick_long_normal.png", Rect(0,0,168,36)));
        auto ann=Animation::createWithSpriteFrames(brick_an,0.15f);
        auto anim_ll=Animate::create(ann);
        auto anim_l=RepeatForever::create(anim_ll);
        if (b->getContactTestBitmask() == BRICK_CONTACT_BITMASK)
        {
            b->getNode()->stopActionByTag(1);
            b->getNode()->runAction(anim_l);
            b->setContactTestBitmask(BRICK_EMPTY_CONTACT_BITMASK);
        }
        if (a->getContactTestBitmask() == BRICK_CONTACT_BITMASK)
        {
            a->getNode()->stopActionByTag(1);
            a->getNode()->runAction(anim_l);
            a->setContactTestBitmask(BRICK_EMPTY_CONTACT_BITMASK);
        }

        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Coin.mp3");
        m_score++;
        
        auto tempScore = __String::createWithFormat("%llu", m_score);
        scoreLabel->setString(tempScore->getCString());
    }
    
    return true;
}


void GameScene::update(float delta)
{
    trix->move();
}
