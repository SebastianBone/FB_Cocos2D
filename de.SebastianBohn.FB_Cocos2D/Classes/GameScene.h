#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__


#include "cocos2d.h"
#include "Bird.h"

class GameScene : public cocos2d::Layer{

public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    cocos2d::PhysicsWorld *sceneWorld;
    
    Bird *bird;
    
    
    void setPhysicsWorld(cocos2d::PhysicsWorld *world){
        sceneWorld = world;
    }

};

#endif