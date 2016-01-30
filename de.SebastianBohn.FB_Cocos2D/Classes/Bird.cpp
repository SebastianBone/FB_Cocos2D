#include "Bird.h"
#include "Constants.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer){
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    bird = Sprite::create("Red_Bird_0.png");
    bird->setScale(2);
    bird->setPosition(Point(visibleSize.width/2 + origin.x/2, visibleSize.height/2 + origin.y));
    
    birdBody = PhysicsBody::createCircle(bird->getContentSize().width/2);
    birdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    
    bird->setPhysicsBody(birdBody);
    layer->addChild(bird,3);
    
}

void Bird::fall(){
    if(isFalling){
        bird->setPositionX(visibleSize.width/2 + origin.x/2);
        bird->setPositionY(bird->getPositionY()+(visibleSize.height * BIRD_GRAVITY));
    }
    else{
        bird->setPositionX(visibleSize.width/2 + origin.x/2);
        bird->setPositionY(bird->getPositionY() + (visibleSize.height * BIRD_FLY_FORCE));
    }
}
