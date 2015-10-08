#include "Trix.h"
#include "Constants.h"
#include "GameScene.h"

USING_NS_CC;

Trix::~Trix()
{
    dead();
}

Trix::Trix(cocos2d::Layer *layer)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    M_trix=Sprite::create("Noc_rightst.png");
    M_trix->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    auto trix_b = PhysicsBody::createBox(M_trix->getContentSize());
    trix_b->setRotationEnable(false);
    M_trix->setPhysicsBody(trix_b);
    trix_b->setCollisionBitmask(TRIX_COLLISION_BITMASK);
    trix_b->setContactTestBitmask(TRIX_CONTACT_BITMASK);
    

    layer->addChild(M_trix, 100);
    
    
}

void Trix::dead()
{
    stop_ani();
    Vector<SpriteFrame*> trix_ani_dead;
    trix_ani_dead.pushBack(SpriteFrame::create("Trix_dead.png", Rect(0,0,40,72)));
    auto ani_dead=Animation::createWithSpriteFrames(trix_ani_dead,0.1f);
    auto anim_dead=Animate::create(ani_dead);
    auto anim_d=RepeatForever::create(anim_dead);
    M_trix->runAction(anim_d);
}

void Trix::dead_fire()
{
    stop_ani();
    Vector<SpriteFrame*> trix_ani_dead;
    trix_ani_dead.pushBack(SpriteFrame::create("Trix_Fire.png", Rect(0,0,40,72)));
    auto ani_dead=Animation::createWithSpriteFrames(trix_ani_dead,0.1f);
    auto anim_dead=Animate::create(ani_dead);
    auto anim_d=RepeatForever::create(anim_dead);
    M_trix->runAction(anim_d);
    
}
void Trix::move()
{
    if ((M_trix->getPositionX()-(M_trix->getContentSize().width)/2)<origin.x)
    {
        trix_atside=1;
    }
    else if ((M_trix->getPositionX()+(M_trix->getContentSize().width)/2)>(origin.x+visibleSize.width))
    {
        trix_atside=2;
    }
    else
    {
        trix_atside=0;
    }
    
    
    if (trix_move==1&&trix_atside!=1)
    {
        M_trix->setPositionX(M_trix->getPositionX()-TRIX_SPEED *visibleSize.width);

    }
    else if (trix_move==2&&trix_atside!=2)
    {
        M_trix->setPositionX(M_trix->getPositionX()+TRIX_SPEED *visibleSize.width);

    }
    else
    {
        M_trix->stopAllActions();

    }
}
