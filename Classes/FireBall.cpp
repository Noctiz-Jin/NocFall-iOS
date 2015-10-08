#include "FireBall.h"
#include "Constants.h"

USING_NS_CC;

FireBall::FireBall()
{
    visibleSize=cocos2d::Director::getInstance()->getVisibleSize();
    origin=cocos2d::Director::getInstance()->getVisibleOrigin();
}


void FireBall::spawnFireBall(cocos2d::Layer * layer)
{
    auto FireBall=cocos2d::Sprite::create("FireBall.png");
    auto ran=CCRANDOM_0_1();
    auto posi_x=ran*visibleSize.width+origin.x;
    auto posi_y=origin.y+visibleSize.height+FireBall->getContentSize().height;
    
    Vector<SpriteFrame*> fireball_an(4);
    fireball_an.pushBack(SpriteFrame::create("FireBall.png", Rect(0,0,58,96)));
    fireball_an.pushBack(SpriteFrame::create("FireBall_2.png", Rect(0,0,58,96)));
    fireball_an.pushBack(SpriteFrame::create("FireBall.png", Rect(0,0,58,96)));
    fireball_an.pushBack(SpriteFrame::create("FireBall_3.png", Rect(0,0,58,96)));
    auto ann=Animation::createWithSpriteFrames(fireball_an,0.1f);
    auto anim_ll=Animate::create(ann);
    auto anim_l=RepeatForever::create(anim_ll);
    FireBall->runAction(anim_l);

    
    auto FireBall_body=cocos2d::PhysicsBody::createBox(FireBall->getContentSize());
    
    FireBall_body->setDynamic(false);
    FireBall_body->setCollisionBitmask(FIREBALL_COLLISION_BITMASK);
    FireBall_body->setContactTestBitmask(FIREBALL_CONTACT_BITMASK);
    FireBall->setPhysicsBody(FireBall_body);
    
    FireBall->setPosition(Point(posi_x,posi_y));
    layer->addChild(FireBall,102);
    auto move_dis=visibleSize.height+FireBall->getContentSize().height+130;
    auto move_duration=FIREBALL_SPEED*move_dis;
    auto FireBall_move=cocos2d::MoveBy::create(move_duration,Point(0,-move_dis));
    FireBall->runAction(Sequence::create(FireBall_move,RemoveSelf::create(true),nullptr));
    
}