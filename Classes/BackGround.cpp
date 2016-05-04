//
//  BackGround.cpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#include "BackGround.hpp"

BackGround::BackGround() {
    
}

BackGround::~BackGround() {
    this->unscheduleUpdate();
}

bool BackGround::init() {
    
    if (!Node::init()) {
        return false;
    }
    
    _background = Sprite::create("background.png");
    _background->setAnchorPoint(Vec2(0, 0));
    
    Texture2D::TexParams tp={GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    
    _background->getTexture()->setTexParameters(tp);
    
    auto viewSize = Director::getInstance()->getVisibleSize();
    auto rect = Rect(0, 0, viewSize.width, viewSize.height);
    
    _background->setTextureRect(rect);
    
    this->addChild(_background);
    
    this->scheduleUpdate();
    
    return true;
    
}

void BackGround::update(float dt) {
    Node::update(dt);
    
    auto rect = _background->getTextureRect();
    rect.origin.x+=100.0f*dt;
    rect.origin.y+=100.0f*dt;
    _background->setTextureRect(rect);
    
}
