#include "Bird.h"
#include "Constants.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer){
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    Vector<SpriteFrame*> animFrames(4);
    char str[100] = {0};
    
    for(int i = 1; i < 5; i++){
        
        sprintf(str, "sprite_%d.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,7.7,5.8));
        animFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    auto animate = Animate::create(animation);
    auto action = RepeatForever::create(animate);
    
    
    bird = Sprite::createWithSpriteFrameName("sprite_1.png");
    
    bird->setPosition(Point(visibleSize.width/2 + origin.x/2, visibleSize.height/2 + origin.y));
    bird->setScale(4);
    bird->runAction(action);
    
    birdBody = PhysicsBody::createCircle(bird->getContentSize().width/2);
    birdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    birdBody->setContactTestBitmask(true);
    
    bird->setPhysicsBody(birdBody);
    layer->addChild(bird,3);
    
    isFalling = true;
    
}

void Bird::fall(){
    if(isFalling){
        bird->setPositionX(visibleSize.width/2 + origin.x/2);
        bird->setPositionY(bird->getPositionY() - (visibleSize.height * BIRD_GRAVITY));
    }
    else{
        bird->setPositionX(visibleSize.width/2 + origin.x/2);
        bird->setPositionY(bird->getPositionY() + (visibleSize.height * BIRD_FLY_FORCE));
    }
}

void Bird::skyCollider(){
    bird->setPositionX(visibleSize.width/2 + origin.x/2);
    bird->setPositionY(visibleSize.height - 2 * bird->getContentSize().height);
}
