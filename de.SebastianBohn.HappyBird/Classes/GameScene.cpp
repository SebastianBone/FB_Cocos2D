#include "GameScene.h"
#include "GameOverScene.h"
#include "Bird.h"
#include "Constants.h"

USING_NS_CC;

Scene* GameScene::createScene(){
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
    
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
    
  
    auto groundBody = PhysicsBody::createBox(ground->getContentSize());
    groundBody->setDynamic(false);
    groundBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    groundBody->setContactTestBitmask(true);
    
    ground->setPhysicsBody(groundBody);
    this->addChild(ground, 2);
    
    auto skyBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    skyBody->setCollisionBitmask(SKY_COLLISION_BITMASK);
    skyBody->setContactTestBitmask(true);
    
    auto skyNode = Node::create();
    skyNode->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    skyNode->setPhysicsBody(skyBody);
    this->addChild(skyNode);
    
    this->schedule(schedule_selector(GameScene::spawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);
    
    scoreCount = 0;
    __String *tempScore = __String::createWithFormat("%i", scoreCount);
    
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 16);
    scoreLabel->setColor(Color3B(0, 0, 0));
    scoreLabel->setPosition(Vec2(origin.x + 20, origin.y + visibleSize.height - scoreLabel->getContentSize().height+5));
    this->addChild(scoreLabel, 1);

    bird = new Bird(this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->scheduleUpdate();
    
    return true;
}

void GameScene::spawnPipe(float deltaTime){
    pipe.spawnPipe(this);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact){
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) ||  (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask())) {
        
        auto scene = GameOverScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0,scene));

    }
    
    if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && SCORE_COLLISION_BITMASK == b->getCollisionBitmask()) ||  (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && SCORE_COLLISION_BITMASK == a->getCollisionBitmask())) {
        
        scoreCount++;
        
        __String *tempScore = __String::createWithFormat("%i",scoreCount);
        
        scoreLabel->setString(tempScore->getCString());
        
        return false;
        
    }
    
    if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && SKY_COLLISION_BITMASK == b->getCollisionBitmask()) ||  (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && SKY_COLLISION_BITMASK == a->getCollisionBitmask())) {
        
        bird->skyCollider();

    }
    return true;
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    bird->fly();
    this->scheduleOnce(schedule_selector(GameScene::stopFlying), BIRD_FLY_DURATION);
    
    return true;
}


void GameScene::stopFlying(float deltaTime){
    bird->stopFlying();
}

void GameScene::update(float deltaTime){
    bird->fall();
}