//
//  EnergyBar.hpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#ifndef EnergyBar_hpp
#define EnergyBar_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class EnergyBar:public Node {
    
protected:
    ProgressTimer *_progress;
    Sprite *_background;
    
    float _percentage;
    
public:
    
    EnergyBar();
    virtual ~EnergyBar();
    
    CREATE_FUNC(EnergyBar);
    
    virtual bool init();
    
    void updateView(int value);
};

#endif /* EnergyBar_hpp */
