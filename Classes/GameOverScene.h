#ifndef __NocDownfall__GameOverScene__
#define __NocDownfall__GameOverScene__

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "GameScene.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(unsigned long long score);
    virtual bool init();
    CREATE_FUNC(GameOverScene);
    void setScore(unsigned long long score) {m_score = score;}
    
private:
    void goToMainMenu(cocos2d::Ref *sender);
    void goToGameScene(cocos2d::Ref *sender);
    cocos2d::Label *scoreLabel;
    cocos2d::Label *highScoreLabel;
    unsigned long long m_score;
};





#endif /* defined(__NocDownfall__GameOverScene__) */
