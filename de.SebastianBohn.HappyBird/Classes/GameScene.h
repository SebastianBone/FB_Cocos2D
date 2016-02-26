#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "Bird.h"
#include "Pipe.h"

class GameScene : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    
private:
    cocos2d::PhysicsWorld *sceneWorld;
    Bird *bird;
    Pipe pipe;
    unsigned int scoreCount;
    cocos2d::Label *scoreLabel;
    
    void setPhysicsWorld(cocos2d::PhysicsWorld *world){
        sceneWorld = world;
    }
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void stopFlying(float deltaTime);
    void spawnPipe(float deltaTime);
};
#endif