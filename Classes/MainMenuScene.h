#ifndef NocDownfall_MainMenuScene_h
#define NocDownfall_MainMenuScene_h

#include "cocos2d.h"


class MainMenuScene : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MainMenuScene);
    
private:
    void GoToGameScene (cocos2d::Ref * sender);
    void GoToGuideScene (cocos2d::Ref * sender);

};



#endif
