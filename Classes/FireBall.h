#ifndef __NocDownfall__FireBall__
#define __NocDownfall__FireBall__

#include "cocos2d.h"

class FireBall
{
public:
    FireBall();
    void spawnFireBall(cocos2d::Layer * layer);
    void startFireBall(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};


#endif /* defined(__NocDownfall__FireBall__) */
