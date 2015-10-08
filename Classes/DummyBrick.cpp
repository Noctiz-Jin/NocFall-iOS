#include "DummyBrick.h"
#include "Constants.h"

USING_NS_CC;


DBrick::DBrick()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    origin=Director::getInstance()->getVisibleOrigin();
}


void DBrick::spawnDBrick(cocos2d::Layer * layer)
{
    auto brick=Sprite::create("brick_break.png");
    auto ran=CCRANDOM_0_1();
    auto posi_x=ran*visibleSize.width+origin.x;
    auto posi_y=origin.y;
    
    
    auto brick_body=PhysicsBody::createBox(brick->getContentSize());
    brick_body->setDynamic(false);
    brick_body->setCollisionBitmask(BRICK_COLLISION_BITMASK);
    brick_body->setContactTestBitmask(BRICK_DUMMY_CONTACT_BITMASK);
    brick->setPhysicsBody(brick_body);
    
    brick->setPosition(Point(posi_x,posi_y));
    layer->addChild(brick,10);
    auto move_dis=visibleSize.height+brick->getContentSize().height-130;
    auto move_duration=BRICK_SPEED*move_dis;
    auto brick_move=MoveBy::create(move_duration,Point(0,move_dis));
    brick->runAction(Sequence::create(brick_move,RemoveSelf::create(true),nullptr));
    
}