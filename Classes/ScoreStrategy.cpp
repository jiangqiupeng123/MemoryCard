//
//  ScoreStrategy.cpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#include "ScoreStrategy.hpp"

ScoreStrategy::ScoreStrategy():_continuous(0) {
    
}

void ScoreStrategy::execute(ScoreData *score, CardData *cardA, CardData *cardB) {
    if (cardA->number==cardB->number) {
        //配对成功，增长能量和积分，累计连击数
        _continuous++;
        if (_continuous>score->maxContinuous) {
            score->maxContinuous = _continuous;
        }
        
        score->energy+=100;
        
        score->score+=100*_continuous;
        
    }
    else {
        //失败，扣除能量
        
        if (cardA->flipCount==0&&cardB->flipCount==0) {
            //第一次翻开 不扣能量和积分
            
        }
        else {
            score->energy-=100;
            _continuous=0;
        }
    }
    
    cardA->flipCount++;
    cardB->flipCount++;
}