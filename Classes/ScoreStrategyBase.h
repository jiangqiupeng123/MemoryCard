
//
//  ScoreStrategyBase.h
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#ifndef ScoreStrategyBase_h
#define ScoreStrategyBase_h

#include "ScoreData.h"
#include "CardData.h"

class ScoreStrategyBase {
    
public:
    virtual void execute(ScoreData *score, CardData *cardA, CardData *cardB) = 0;
    
};

#endif /* ScoreStrategyBase_h */
