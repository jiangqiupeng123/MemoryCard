//
//  MemoryCardScene.hpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#ifndef MemoryCardScene_hpp
#define MemoryCardScene_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "MemoryCardLevel.hpp"
#include "ScoreStrategyBase.h"
#include <memory>
#include "BackGround.hpp"

#include "EnergyBar.hpp"
#include "ScoreText.hpp"

USING_NS_CC;

class MemoryCardScene:public Layer {
    
protected:
    
    LevelData _nowLevelData;
    
    MemoryCardLevel *_nowLevelLayer;
    
    std::shared_ptr<ScoreStrategyBase> _scoreStrategy;
    
    ScoreData _scoreData;
    
    BackGround *_background;
    
    EnergyBar *_energyBar;
    
    ScoreText *_scoreText;
    
public:
    MemoryCardScene();
    virtual ~MemoryCardScene();
    
    static Scene *createScene(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
    
    static MemoryCardScene *create(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
    
    virtual bool initWithScoreStrategy(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
    
    virtual void update(float dt);
    
    virtual void newGame();
};

#endif /* MemoryCardScene_hpp */
