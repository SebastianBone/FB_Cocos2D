#include "GameOverScene.h"
#include "GameScene.h"
#include "Constants.h"
USING_NS_CC;

Scene* GameOverScene::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init(){
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ){
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
    this->addChild(ground, 2);
    
    auto startButton = MenuItemImage::create("StartButton.png", "StartButton.png", CC_CALLBACK_1(GameOverScene::startGame, this));
    startButton->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    startButton->setScale(1.5f);
    
    auto ui = Menu::create(startButton, NULL);
    ui->setPosition(Point::ZERO);
    
    this->addChild(ui);
    
    auto gameOverLabel = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 36);
    gameOverLabel->setColor(Color3B(0, 0, 0));
    gameOverLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - gameOverLabel->getContentSize().height-20));
    this->addChild(gameOverLabel, 1);
    
    auto tryAgainLabel = Label::createWithTTF("Try Again?", "fonts/Marker Felt.ttf", 20);
    tryAgainLabel->setColor(Color3B(0, 0, 0));
    tryAgainLabel->setPosition(Vec2(origin.x + visibleSize.width/2, gameOverLabel->getPositionY()- tryAgainLabel->getContentSize().height-30));
    this->addChild(tryAgainLabel, 1);

    
    return true;
}

void GameOverScene::startGame(cocos2d::Ref *sender){
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}