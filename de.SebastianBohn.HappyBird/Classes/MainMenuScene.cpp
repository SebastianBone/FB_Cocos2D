#include "MainMenuScene.h"
#include "GameScene.h"
#include "Constants.h"
USING_NS_CC;

Scene* MainMenuScene::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init(){
    
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
    
    auto startButton = MenuItemImage::create("StartButton.png", "StartButton.png", CC_CALLBACK_1(MainMenuScene::startGame, this));
    startButton->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    startButton->setScale(1.5f);
    
    auto ui = Menu::create(startButton, NULL);
    ui->setPosition(Point::ZERO);
    
    this->addChild(ui);
    
    auto label = Label::createWithTTF("Happy Bird", "fonts/Marker Felt.ttf", 36);
    label->setColor(Color3B(0, 0, 0));
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height-20));
    this->addChild(label, 1);
    
    return true;
}

void MainMenuScene::startGame(cocos2d::Ref *sender){
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}