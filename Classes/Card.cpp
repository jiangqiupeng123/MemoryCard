//
//  Card.cpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#include "Card.hpp"

Card::Card() :
_backImage(nullptr),
_frontImage(nullptr),
_state(CardState::BACK)
{
    this->setCascadeOpacityEnabled(true);
}

Card::~Card()
{
    this->removeAllChildren();
}



Node* Card::getBackImage()
{
    return _backImage;
}

Node* Card::getFrontImage()
{
    return _frontImage;
}

void Card::setFrontImage(cocos2d::Node* var)
{
    if (nullptr == var) {
        return;
    }
    
    if (nullptr != _frontImage) {
        _frontImage->removeFromParent();
    }
    
    _frontImage = var;
    _frontImage->setCascadeOpacityEnabled(true);
    _frontImage->setVisible(false);
    addChild(_frontImage);
}

void Card::setBackImage(cocos2d::Node* var)
{
    if (nullptr == var) {
        return;
    }
    
    if (nullptr != _backImage) {
        _backImage->removeFromParent();
    }
    
    _backImage = var;
    _backImage->setCascadeOpacityEnabled(true);
    this->setContentSize(_backImage->getContentSize());
    addChild(_backImage);
}


void Card::flipFromTo(cocos2d::Node *a, cocos2d::Node *b,const std::function<void ()> &callback)
{
    if (nullptr == a || nullptr == b) {
        return;
    }
    
    //初始化属性
    
    a->stopAllActions();
    b->stopAllActions();
    
    a->setVisible(true);
    a->setScaleX(1.0f);
    
    b->setVisible(false);
    b->setScaleX(0);
    
    
    //翻出B
    
    auto flipB = [a, b,callback](){
        a->setVisible(false);
        b->setVisible(true);
        
        CallFunc* func=nullptr;
        if (callback!=nullptr) {
            func=CallFunc::create(callback);
        }
        
        b->runAction(Sequence::create(
                                      ScaleTo::create(0.2f, 1.0f, 1.0f),
                                      func,
                                      NULL));
    };
    
    //翻入A
    
    a->runAction(Sequence::create(
                                  ScaleTo::create(0.2f, 0, 1.0f),
                                  CallFunc::create(flipB)
                                  , NULL));
    
}



void Card::flipToBack(const std::function<void ()> &callback)
{
    if (_state==CardState::BACK) {
        return;
    }
    
    flipFromTo(_frontImage, _backImage,callback);
    _state=CardState::BACK;
}

void Card::flipToFront(const std::function<void ()> &callback)
{
    if (_state==CardState::FRONT) {
        return;
    }
    
    flipFromTo(_backImage, _frontImage,callback);
    _state=CardState::FRONT;
}

CardState Card::getCardState() const
{
    return _state;
}

void Card::setCardData(CardData data)
{
    _data=data;
}

CardData* Card::getCardData()
{
    return &_data;
    
}
