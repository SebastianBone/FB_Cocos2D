#include "Bird.h"
#include "Constants.h"
USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer){
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    bird = Sprite::create("sprite_1.png");
    bird->setPosition(visibleSize.width/2 + origin.x/2 + 20, visibleSize.height/2 + origin.y);
    birdBody = PhysicsBody::createCircle(bird->getContentSize().width/2);
    birdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    birdBody->setContactTestBitmask(true);
    birdBody->setRotationEnable(false);
    bird->setPhysicsBody(birdBody);
    bird->setScale(4);
    layer->addChild(bird,3);
    
    Vector<SpriteFrame*> frames;
    Size birdSize = bird->getContentSize();
    frames.pushBack(SpriteFrame::create("sprite_1.png", Rect(0,0,birdSize.width, birdSize.height)));
    frames.pushBack(SpriteFrame::create("sprite_2.png", Rect(0,0,birdSize.width, birdSize.height)));
    frames.pushBack(SpriteFrame::create("sprite_3.png", Rect(0,0,birdSize.width, birdSize.height)));
    frames.pushBack(SpriteFrame::create("sprite_4.png", Rect(0,0,birdSize.width, birdSize.height)));
    
    auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
    auto animate = Animate::create(animation);
    bird->runAction(RepeatForever::create(animate));
}

void Bird::fly(){
    bird->getPhysicsBody()->setVelocity(Vect(0,0));
    bird->getPhysicsBody()->applyImpulse(Vect(0, 7000));
}