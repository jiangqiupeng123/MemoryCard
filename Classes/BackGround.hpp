//
//  BackGround.hpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#ifndef BackGround_hpp
#define BackGround_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class BackGround:public Node {
protected:
    Sprite *_background;
    
public:
    BackGround();
    virtual ~BackGround();
    
    CREATE_FUNC(BackGround);
    virtual bool init();
    virtual void update(float dt);
};

#endif /* BackGround_hpp */
