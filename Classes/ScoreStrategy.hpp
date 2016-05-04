//
//  ScoreStrategy.hpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#ifndef ScoreStrategy_hpp
#define ScoreStrategy_hpp

#include <stdio.h>
#include "ScoreStrategyBase.h"

class ScoreStrategy:public ScoreStrategyBase {
private:
    int _continuous;
public:
    ScoreStrategy();
    
    virtual void execute(ScoreData *score, CardData *cardA, CardData *cardB);
};

#endif /* ScoreStrategy_hpp */
