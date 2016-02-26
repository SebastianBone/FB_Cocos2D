#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__
#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameOverScene);
    
private:
    void startGame(cocos2d::Ref *sender);
};
#endif