#include "Brick.h"
#include "Constants.h"

USING_NS_CC;


Brick::Brick()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    origin=Director::getInstance()->getVisibleOrigin();
}


void Brick::spawnBrick(cocos2d::Layer * layer)
{
    auto brick=Sprite::create("brick_long_normal.png");
    auto ran=CCRANDOM_0_1();
    auto posi_x=ran*visibleSize.width+origin.x;
    auto posi_y=origin.y;
    
    Vector<SpriteFrame*> brick_an(2);
    brick_an.pushBack(SpriteFrame::create("brick_shine_1.png", Rect(0,0,168,36)));
    brick_an.pushBack(SpriteFrame::create("brick_shine_2.png", Rect(0,0,168,36)));
    auto ann=Animation::createWithSpriteFrames(brick_an,0.15f);
    auto anim_ll=Animate::create(ann);
    auto anim_l=RepeatForever::create(anim_ll);
    anim_l->setTag(1);
    brick->runAction(anim_l);
    auto brick_body=PhysicsBody::createBox(brick->getContentSize());

    brick_body->setDynamic(false);
    brick_body->setCollisionBitmask(BRICK_COLLISION_BITMASK);
    brick_body->setContactTestBitmask(BRICK_CONTACT_BITMASK);
    brick->setPhysicsBody(brick_body);
    
    brick->setPosition(Point(posi_x,posi_y));
    layer->addChild(brick,5);
    auto move_dis=visibleSize.height+brick->getContentSize().height-130;
    auto move_duration=BRICK_SPEED*move_dis;
    auto brick_move=MoveBy::create(move_duration,Point(0,move_dis));
    brick->runAction(Sequence::create(brick_move,RemoveSelf::create(true),nullptr));
        
}

void Brick::startBrick(cocos2d::Layer * layer)
{
    auto brick=Sprite::create("brick_start.png");
    auto brick_body=PhysicsBody::createBox(brick->getContentSize());
    brick_body->setDynamic(false);
    brick_body->setCollisionBitmask(BRICK_COLLISION_BITMASK);
    brick_body->setContactTestBitmask(BRICK_CONTACT_BITMASK);
    brick->setPhysicsBody(brick_body);
    brick->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2-100));
    layer->addChild(brick,5);
    auto move_dis=visibleSize.height+brick->getContentSize().height-100;
    auto move_duration=BRICK_SPEED*move_dis;
    auto brick_move=MoveBy::create(move_duration,Point(0,move_dis));
    brick->runAction(Sequence::create(brick_move,RemoveSelf::create(true),nullptr));
}