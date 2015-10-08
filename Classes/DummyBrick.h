#ifndef __NocDownfall__DummyBrick__
#define __NocDownfall__DummyBrick__

#include "cocos2d.h"

class DBrick
{
public:
    DBrick();
    void spawnDBrick(cocos2d::Layer * layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};


#endif /* defined(__NocDownfall__DummyBrick__) */
