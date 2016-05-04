//
//  ScoreText.hpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#ifndef ScoreText_hpp
#define ScoreText_hpp

#include <stdio.h>
#include "cocos2d.h"
#include <CocosGUI.h>

USING_NS_CC;

class ScoreText:public Node {

protected:
    ui::TextAtlas *_text;
    
    int _score;
    
public:
    ScoreText();
    
    CREATE_FUNC(ScoreText);
    
    virtual bool init();
    
    virtual void updateView(int value);
};

#endif /* ScoreText_hpp */
