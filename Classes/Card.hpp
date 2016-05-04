//
//  Card.hpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ICard.h"

USING_NS_CC;

class Card:public ICard, public Node {
    
    Card();
    virtual ~Card();
    
    
protected:
    
    CardState _state;
    CardData _data;
    CC_PROPERTY(Node*, _backImage, BackImage);
    CC_PROPERTY(Node*, _frontImage, FrontImage);
    
    void flipFromTo(Node *a, Node *b, const std::function<void()> &callback=nullptr);
    
public:
    
    CREATE_FUNC(Card);
    
    virtual void flipToBack(const std::function<void()> &callback=nullptr);
    virtual void flipToFront(const std::function<void()> &callback=nullptr);
    virtual CardState getCardState() const;
    virtual void setCardData(CardData data);
    virtual CardData *getCardData();
    
};

#endif /* Card_hpp */
