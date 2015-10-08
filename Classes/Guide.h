#ifndef __NocDownfall__Guide__
#define __NocDownfall__Guide__

#include "cocos2d.h"
#include "MainMenuScene.h"

class GuideScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GuideScene);
    
private:
    void goToMainMenu(cocos2d::Ref *sender);
    void Guide_move();
};


#endif /* defined(__NocDownfall__Guide__) */
