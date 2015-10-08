#ifndef __NocDownfall__Brick__
#define __NocDownfall__Brick__

#include "cocos2d.h"

class Brick
{
public:
    Brick();
    void spawnBrick(cocos2d::Layer * layer);
    void startBrick(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};




#endif /* defined(__NocDownfall__Brick__) */
