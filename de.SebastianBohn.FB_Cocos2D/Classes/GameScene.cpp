#include "GameScene.h"
#include "Bird.h"
#include "Constants.h"

USING_NS_CC;

Scene* GameScene::createScene(){
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    
    scene->addChild(layer);
    return scene;
}

bool GameScene::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create("Sky.png");
    background->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    background->setScale(1, 3.5f);
    this->addChild(background, 0);
    
    auto ground = Sprite::create("Ground.png");
    ground->setPosition(Point(visibleSize.width/2 + origin.x, 15));
    ground->setScale(1, 1.5f);
    
    /*
    auto groundBody = PhysicsBody::createBox(ground->getContentSize());
    groundBody->setDynamic(false);
    groundBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    groundBody->setContactTestBitmask(true);
   
     
    ground->setPhysicsBody(groundBody);
     */
    this->addChild(ground, 2);
    
    auto label = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 16);
    label->setColor(Color3B(0, 0, 0));
    label->setPosition(Vec2(origin.x + 20, origin.y + visibleSize.height - label->getContentSize().height+5));
    this->addChild(label, 1);

    bird = new Bird(this);

    
    return true;
}