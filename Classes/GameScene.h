#ifndef __NocDownfall__GameScene__
#define __NocDownfall__GameScene__

#include "cocos2d.h"
#include "Trix.h"
#include "physics/CCPhysicsShape.h"
#include "Brick.h"
#include "DummyBrick.h"
#include "FireBall.h"
#include "Constants.h"

const cocos2d::PhysicsMaterial PHYSICSBODY_MATERIAL_EDGE(0.1f, 0.5f, 0.5f);

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    void setPhysicsWorld(cocos2d::PhysicsWorld *world) {sceneWorld = world;}
    unsigned long long getScore() const {return m_score;}
    
    
    
private:
    cocos2d::PhysicsWorld *sceneWorld;
    Trix *trix;
    cocos2d::Sprite* warning;
    
    
    bool Touch(cocos2d::Touch *touch, cocos2d::Event *event);
    void TouchEnd(cocos2d::Touch *touch, cocos2d::Event *event);
    void update (float delta);
    void spawnBrick(float delta){Brick.spawnBrick(this);}
    void spawnDBrick(float delta){DBrick.spawnDBrick(this);}
    void startBrick(float delta){Brick.startBrick(this);}
    
    void lastwarning1(float delta);
    void lastwarning2(float delta);
    void lastwarning3(float delta);
    void lastwarning4(float delta);
    void lastwarning(float delta);
    void lastrush(float delta){warning->removeFromParentAndCleanup(true); warningsign=0; this->schedule(schedule_selector(GameScene::spawnFireBall_5),visible_height*FIREBALL_SPAWN_FREQ_HARD);}
    
    void spawnFireBall(float delta){if(warningsign==1){warning->removeFromParentAndCleanup(true);warningsign=0;}FireBall.spawnFireBall(this);CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FireBall_Coming.mp3");}
    void spawnFireBall_2(float delta){if(warningsign==1){warning->removeFromParentAndCleanup(true);warningsign=0;}
        FireBall.spawnFireBall(this);CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FireBall_Coming.mp3");}
    void spawnFireBall_3(float delta){if(warningsign==1){warning->removeFromParentAndCleanup(true);warningsign=0;}
        FireBall.spawnFireBall(this);CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FireBall_Coming.mp3");}
    void spawnFireBall_4(float delta){if(warningsign==1){warning->removeFromParentAndCleanup(true);warningsign=0;}
        FireBall.spawnFireBall(this);CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FireBall_Coming.mp3");}
    void spawnFireBall_5(float delta){if(warningsign==1){warning->removeFromParentAndCleanup(true);warningsign=0;}
        FireBall.spawnFireBall(this);CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("FireBall_Coming.mp3");}
    void TrixInvTime(float delta){Trix_inv=0;trix->M_trix->getPhysicsBody()->setContactTestBitmask(TRIX_CONTACT_BITMASK);}
    
    Brick Brick;
    DBrick DBrick;
    FireBall FireBall;
    int Trix_dead=0;//0->alive  1->spike dead 2->fireball dead
    int Trix_inv=0;
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    unsigned long long m_score=0;
    float visible_height;
    cocos2d::Label *scoreLabel;
    float FireRound=0;
    int warningsign=0;
};


#endif /* defined(__NocDownfall__GameScene__) */
