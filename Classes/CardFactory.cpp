//
//  CardFactory.cpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#include "CardFactory.hpp"
#include "cocos2d.h"
#include <ui/CocosGUI.h>
#include "Card.hpp"

USING_NS_CC;

ICard* CardFactory::createCard(int backId, int number) {
    
    const int cardSize = 189;
    
    // 创建背景
    if (backId<0 || backId > 7) {
        backId = 0;
    }
    int x = (backId%2)*cardSize;
    int y = (backId/2)*cardSize;
    
    auto backImage = Sprite::create("card_back.png", Rect(x, y, cardSize, cardSize));
    
    // 创建正面
    auto frontImage = Node::create();
    frontImage->setContentSize(Size(cardSize, cardSize));
    frontImage->addChild(Sprite::create("card_front.png"));
    
    auto numberText = ui::TextAtlas::create(StringUtils::format("%d", number), "card_number.png", 140, 140, "0");
    
    frontImage->addChild(numberText);
    
    // 创建卡片数据
    CardData data={};
    data.number = number;
    
    // 创建卡片
    auto card = Card::create();
    card->setBackImage(backImage);
    card->setFrontImage(frontImage);
    card->setCardData(data);
    card->setContentSize(backImage->getContentSize());
    
    return card;
}