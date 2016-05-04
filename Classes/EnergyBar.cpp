//
//  EnergyBar.cpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#include "EnergyBar.hpp"

EnergyBar::EnergyBar():_percentage(0) {
    
}

EnergyBar::~EnergyBar() {
    
}

bool EnergyBar::init() {
    
    if (!Node::init()) {
        return false;
    }
    
    _progress = ProgressTimer::create(Sprite::create("energy_front.png"));
    
    _progress->setType(ProgressTimer::Type::BAR);
    _progress->setMidpoint(Vec2(0, 0));
    _progress->setBarChangeRate(Vec2(1, 0));
    
    _background = Sprite::create("energy_back.png");
    
    this->addChild(_background);
    this->addChild(_progress);
    
    this->setContentSize(_background->getContentSize());
    
    updateView(1000);
    
    return true;
}

void EnergyBar::updateView(int value) {
    
    auto percentage = value / 1000.0f * 100;
    
    if (std::abs(percentage-_percentage)>1.0f) {
        _progress->runAction(EaseBackOut::create(ProgressTo::create(0.25f, percentage)));
        _percentage = percentage;
    }
    
}



