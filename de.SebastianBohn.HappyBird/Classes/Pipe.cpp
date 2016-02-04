#include "Pipe.h"
#include "Constants.h"

USING_NS_CC;

Pipe::Pipe( )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
}

void Pipe::spawnPipe( cocos2d::Layer *layer )
{
    auto topPipe = Sprite::create( "Pipe.png" );
    auto bottomPipe = Sprite::create( "Pipe.png" );
    
    topPipe->setRotation(180);
    
    topPipe->setScale(1.5f, 1);
    bottomPipe->setScale(1.5f,1);
    
    auto topPipeBody = PhysicsBody::createBox( topPipe->getContentSize( ) );
    auto bottomPipeBody = PhysicsBody::createBox( bottomPipe->getContentSize( ) );
    
    auto random = CCRANDOM_0_1( );
    
    if ( random < LOWER_SCREEN_PIPE_THRESHOLD )
    {
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    }
    else if ( random > UPPER_SCREEN_PIPE_THRESHOLD )
    {
        random = UPPER_SCREEN_PIPE_THRESHOLD;
    }
    
    auto topPipePosition = ( random * visibleSize.height ) + ( topPipe->getContentSize( ).height / 2 );
    
    topPipeBody->setDynamic( false );
    bottomPipeBody->setDynamic( false );
    
    topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topPipeBody->setContactTestBitmask(true);
    
    bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomPipeBody->setContactTestBitmask(true);
    
    topPipe->setPhysicsBody( topPipeBody );
    bottomPipe->setPhysicsBody( bottomPipeBody );
    
    topPipe->setPosition( Point( visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition ) );
    bottomPipe->setPosition( Point( topPipe->getPositionX(), topPipePosition - ( Sprite::create( "Red_Bird_0.png" )->getContentSize( ).height + 7*PIPE_GAP ) - topPipe->getContentSize().height ) );
    
    layer->addChild( topPipe, 0 );
    layer->addChild( bottomPipe, 0 );
    
    auto topPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    auto bottomPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    
    topPipe->runAction( topPipeAction );
    bottomPipe->runAction( bottomPipeAction );
    
    auto pointNode = Node::create( );
    auto pointBody = PhysicsBody::createBox( Size( 0, Sprite::create( "Red_Bird_0.png" )->getContentSize( ).height * PIPE_GAP ));
    pointBody->setDynamic( true );
    pointBody->setCollisionBitmask( SCORE_COLLISION_BITMASK );
    pointBody->setContactTestBitmask( true );
    
    pointNode->setPhysicsBody( pointBody );
    pointNode->setPosition( Point( topPipe->getPositionX( )+ topPipe->getContentSize().width / 2, topPipe->getPositionY( ) - ( topPipe->getContentSize( ).height / 2 ) - ( ( Sprite::create( "Red_Bird_0.png" )->getContentSize( ).height + 7*PIPE_GAP ) / 2 ) ) );
    
    layer->addChild( pointNode );
    
    auto pointNodeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    
    pointNode->runAction( pointNodeAction );
}