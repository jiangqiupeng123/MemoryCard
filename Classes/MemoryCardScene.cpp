//
//  MemoryCardScene.cpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#include "MemoryCardScene.hpp"

MemoryCardScene::MemoryCardScene():
_scoreData({}),
_nowLevelLayer(nullptr)
{
    _scoreData.energy = 1000;
}

MemoryCardScene::~MemoryCardScene() {
    this->unscheduleUpdate();
}

Scene *MemoryCardScene::createScene(std::shared_ptr<ScoreStrategyBase> scoreStrategy) {
    
    auto scene = Scene::create();
    auto layer = MemoryCardScene::create(scoreStrategy);
    scene->addChild(layer);
    
    return scene;
}

MemoryCardScene* MemoryCardScene::create(std::shared_ptr<ScoreStrategyBase> scoreStrategy) {
    MemoryCardScene *scene = new MemoryCardScene();
    if (scene&&scene->initWithScoreStrategy(scoreStrategy)) {
        scene->autorelease();
        return scene;
    }
    
    CC_SAFE_DELETE(scene);
    
    return nullptr;
}

bool MemoryCardScene::initWithScoreStrategy(std::shared_ptr<ScoreStrategyBase> scoreStrategy) {
    
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 设置积分策略
    _scoreStrategy = scoreStrategy;
    
    // 创建背景
    _background = BackGround::create();
    this->addChild(_background);
    
    // 创建能量条
    _energyBar=EnergyBar::create();
    _energyBar->setPosition(visibleSize.width/2, visibleSize.height-100);
    this->addChild(_energyBar);
    
    // 创建分数显示文本
    _scoreText=ScoreText::create();
    _scoreText->setPosition(visibleSize.width-20, visibleSize.height-33);
    this->addChild(_scoreText);
    
    newGame();
    
    this->scheduleUpdate();
    
    return true;
}

void MemoryCardScene::newGame() {
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    LevelData data = {};
    data.rows = 4;
    data.cols = 4;
    data.loss = 20;
    _nowLevelData = data;
    
    auto level = _nowLevelLayer = MemoryCardLevel::create(data);
    addChild(level);
    
    level->setAnchorPoint(Vec2(0.5, 0.5));
    level->ignoreAnchorPointForPosition(false);
    level->setPosition(visibleSize / 2);
    
    level->setScale(visibleSize.width / level->getContentSize().width);
    
    // 注册回调函数
    level->registerCallFunc([this](CardData *cardA, CardData *cardB){
        
        _scoreStrategy->execute(&_scoreData, cardA, cardB);
        
        CCLOG("score:%d, energy:%d,maxContinuous:%d", _scoreData.score, _scoreData.energy, _scoreData.maxContinuous);
        
    }, [](){
        
        CCLOG("complete");
        
    });
}

void MemoryCardScene::update(float dt) {
    Layer::update(dt);
    
    _scoreData.energy-=this->_nowLevelData.loss*dt;
    
    if (_scoreData.energy>1000) {
        _scoreData.energy=1000;
    }
    else if (_scoreData.energy<0) {
        _scoreData.energy=0;
    }
    
    _energyBar->updateView(_scoreData.energy);
    
    _scoreText->updateView(_scoreData.score);
    
}


