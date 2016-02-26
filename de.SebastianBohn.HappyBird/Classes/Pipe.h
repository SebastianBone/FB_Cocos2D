#ifndef __PIPE_H__
#define __PIPE_H__

#include "cocos2d.h"

class Pipe {
public:
    Pipe();
    
    void spawnPipe(cocos2d::Layer *layer);
    void removePipe(cocos2d::Layer *layer);
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
//    cocos2d::Sprite *topPipe;
//    cocos2d::Sprite *bottomPipe;
//    
//    cocos2d::PhysicsBody *topPipeBody;
//    cocos2d::PhysicsBody *bottomPipeBody;
    
    
};

#endif
