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
    
    //birdBody->setVelocity(Vect(0,-100));
    
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
    //bird->getPhysicsBody()->setLinearDamping(1);
    bird->getPhysicsBody()->setVelocity(Vect(0,0));
    bird->getPhysicsBody()->applyImpulse(Vect(0, 7000));

}

void Bird::fall(){
    bird->getPhysicsBody()->setVelocity(Vect(0,-100));
}
//
//    Vector<SpriteFrame*> animFrames(4);
//    
//    
//    char str[100] = {0};
//    
//    for(int i = 0; i < 4; i++){
//        
//        sprintf(str, "sprite_%d.png",i);
//        //auto frame = SpriteFrame::create(str,Rect(0,0,7.7,5.8));
//        auto frame = SpriteFrame::create(str,Rect(0,0,34,26));
//        animFrames.pushBack(frame);
//    }
//    
//    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
//    auto animate = Animate::create(animation);
//    auto action = RepeatForever::create(animate);
//    
//    bird = Sprite::createWithSpriteFrameName("sprite_1.png");
//    
//    bird->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    bird->setScale(4);
//    bird->runAction(action);
//    
//    //birdBody = PhysicsBody::createCircle(bird->getContentSize().width/1.5f);
//    //birdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
//    //birdBody->setContactTestBitmask(true);
//    //birdBody->setGravityEnable(false);
//    
//    //bird->setPhysicsBody(birdBody);
//    layer->addChild(bird,3);
//    
//    isFalling = true;
//    
//}
//
//void Bird::fall(){
//    if(isFalling){
//       // bird->setPositionX(visibleSize.width/2 + origin.x/2);
//       // bird->setPositionY(bird->getPositionY() - (visibleSize.height * BIRD_GRAVITY));
//    }
//    else{
//        //bird->setPositionX(visibleSize.width/2 + origin.x/2);
//        //bird->setPositionY(bird->getPositionY() + (visibleSize.height * BIRD_FLY_FORCE));
//    
//        //bird->runAction(JumpTo::create(1, Point(bird->getPositionX(),bird->getPositionY()), 10, 1));
//    }
//}
//
//void Bird::skyCollider(){
//    //bird->setPositionX(visibleSize.width/2 + origin.x/2);
//    //bird->setPositionY(visibleSize.height - 2 * bird->getContentSize().height);
//}
