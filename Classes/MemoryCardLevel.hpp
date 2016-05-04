//
//  MemoryCardLevel.hpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#ifndef MemoryCardLevel_hpp
#define MemoryCardLevel_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "LevelData.h"
#include "Card.hpp"

USING_NS_CC;

class MemoryCardLevel:public Layer {
    
    // 关卡数据
    LevelData _levelData;
    // 放置当前卡片的二维数组
    std::vector<std::vector<Card*>> _cardTable;
    // 剩余卡片数量
    int _unfinishedCard;
    // 当前选择的卡片
    Card *_selCardA;
    Card *_selCardB;
    
    // 配对时回调
    std::function<void(CardData *cardA, CardData *cardB)> _pairCallBack;
    
    // 全部匹配时回调
    std::function<void()> _completeCallBack;
    
public:
    MemoryCardLevel();
    virtual ~MemoryCardLevel();
    
    static MemoryCardLevel* create(LevelData levelData);
    
    virtual bool initWithLevelData(LevelData levelData);
    
    void registerCallFunc(std::function<void(CardData *cardA, CardData *cardB)> pairCallBack, std::function<void()> completeCallBack);
    
protected:
    void initCardLayout();
    void initTouchEvent();
    
};


#endif /* MemoryCardLevel_hpp */
