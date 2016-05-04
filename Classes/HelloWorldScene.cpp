#include "HelloWorldScene.h"

#include "Card.hpp"
#include "CardFactory.hpp"

#include "MemoryCardLevel.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    LevelData data = {};
    data.rows = 4;
    data.cols = 4;
    
    auto level = MemoryCardLevel::create(data);
    addChild(level);
    
    level->setAnchorPoint(Vec2(0.5, 0.5));
    level->ignoreAnchorPointForPosition(false);
    level->setPosition(visibleSize / 2);
    
    level->setScale(visibleSize.width / level->getContentSize().width);
    
    // 注册回调函数
    level->registerCallFunc([](CardData *cardA, CardData *cardB){
        CCLOG("cardA number:%d cardB number:%d", cardA->number, cardB->number);
    }, [](){
        CCLOG("complete");
    });
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
