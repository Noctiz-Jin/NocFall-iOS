#ifndef __NocDownfall__Trix__
#define __NocDownfall__Trix__

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"


class Trix
{
public:
    Trix(cocos2d::Layer * layer);
    ~Trix();
    void leftm(){trix_move=1;}
    void rightm(){trix_move=2;}
    void stop(){trix_move=0;}
    void move();
    void dead();
    void dead_fire();
    void stop_ani(){M_trix->stopAllActions();}
    cocos2d::Sprite *M_trix;

    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    int trix_move=0;//1 is left, 2 is right
    int trix_atside=0;
};

#endif /* defined(__NocDownfall__Trix__) */
