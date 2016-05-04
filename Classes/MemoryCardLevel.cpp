//
//  MemoryCardLevel.cpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#include "MemoryCardLevel.hpp"
#include "CardFactory.hpp"

MemoryCardLevel::MemoryCardLevel():
_selCardA(nullptr),
_selCardB(nullptr),
_pairCallBack(nullptr),
_completeCallBack(nullptr),
_unfinishedCard(0)
{
    
}

MemoryCardLevel::~MemoryCardLevel() {
    this->removeAllChildren();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

MemoryCardLevel* MemoryCardLevel::create(LevelData levelData) {
    
    auto cl = new MemoryCardLevel();
    if (cl&&cl->initWithLevelData(levelData)) {
        cl->autorelease();
        return cl;
    }
    
    CC_SAFE_DELETE(cl);
    
    return nullptr;
}

bool MemoryCardLevel::initWithLevelData(LevelData levelData) {
    if (!Layer::init()) {
        return false;
    }
    
    if ((levelData.rows*levelData.cols)%2 != 0) {
        return false;
    }
    
    _levelData = levelData;
    
    initCardLayout();
    
    initTouchEvent();
    
    return true;
    
}

void MemoryCardLevel::initCardLayout() {
    
    // 产生颜色的随机数
    int backid = random(0, 7);
    
    // 初始化卡片table
    for (int row = 0; row<_levelData.rows; row++) {
        std::vector<Card*> r(_levelData.cols);
        _cardTable.push_back(r);
    }
    
    // 初始化卡片并填充到卡片数组
    CardFactory factory;
    int number = 0;
    
    Vector<Card*> cardList;
    for (number=0; number<_levelData.rows*_levelData.cols; number++) {
        // 创建卡片
        Card *card = dynamic_cast<Card *>(factory.createCard(backid, number/2));
        cardList.pushBack(card);
    }
    
    this->_unfinishedCard = number;
    
    for (int row = 0; row<_levelData.rows; row++) {
        for (int col=0; col<_levelData.cols; col++) {
            
            int at = random(0, (int)cardList.size()-1);
            
            auto card = cardList.at(at);
            
            cardList.erase(at);
            
            card->getCardData()->row = row;
            card->getCardData()->column = col;
            
            // 设置卡片的坐标
            int space = 20; // 间隔
            auto cardSize = card->getContentSize();
            
            card->setPosition(Vec2(space + (space+cardSize.width)*col + cardSize.width/2, space + (space+cardSize.height)*row + cardSize.height/2));
            
            _cardTable[row][col] = card;
            
            // 添加至显示列表
            this->addChild(card);
            
            // 设置图层大小
            if (col==_levelData.cols-1 && row==_levelData.rows-1) {
                this->setContentSize(Size(space+(space+cardSize.width)*_levelData.cols, space+(space+cardSize.height)*_levelData.rows));
            }
            
        }
    }
    
}

void MemoryCardLevel::registerCallFunc(std::function<void (CardData *, CardData *)> pairCallBack, std::function<void ()> completeCallBack) {
    
    _pairCallBack = pairCallBack;
    _completeCallBack = completeCallBack;
    
}

void MemoryCardLevel::initTouchEvent() {
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [this](Touch *touch, Event *event){
        // 判断当前点击的位置是否在关卡区域内
        
        Point locationInNode = this->convertToNodeSpace(touch->getLocation());
        Size s = this->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode)) {
            return true;
        }
        return false;
    };
    
    listener->onTouchEnded = [this](Touch *touch, Event *event){
        // 找到当前选中的卡片
        
        Point locationInNode = this->convertToNodeSpace(touch->getLocation());
        
        Card *selCard=nullptr;
        for (int row=0; row<_levelData.rows; row++) {
            auto cards = _cardTable[row];
            auto isFind = false;
            for (int col=0; col<_levelData.cols; col++) {
                auto card = cards[col];
                
                if (!card) {
                    continue;
                }
                
                auto size = card->getContentSize();
                auto pos = card->getPosition();
                auto rect = Rect(pos.x - size.width/2, pos.y - size.height/2, size.width, size.height);
//                log("%f, %f, %f, %f", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
                if (rect.containsPoint(locationInNode)) {
                    isFind = true;
                    selCard = card;
                    break;
                }
                
            }
            if (isFind) {
                break;
            }
        }
        
        // 没点到卡片或者点到了第一次点到的卡片
        if (!selCard || _selCardA == selCard) {
            return;
        }
        
        if (_selCardA==nullptr) {
            // 第一次选择
            _selCardA=selCard;
            
            _selCardA->flipToFront();
        } else {
            // 第二次选择
            _selCardB=selCard;
            
            auto dataA=_selCardA->getCardData();
            auto dataB=_selCardB->getCardData();
            
            if (_pairCallBack) {
                _pairCallBack(dataA, dataB);
            }
            
            if (dataA->number == dataB->number) {
                // 配对成功消除
                
                auto cardA = _selCardA;
                auto cardB = _selCardB;
                _selCardB->flipToFront([this, cardA, cardB](){
                    cardA->runAction(Sequence::create(Spawn::create(FadeOut::create(0.25), ScaleTo::create(0.25, 0), NULL), CallFunc::create([cardA](){
                        
                        cardA->removeFromParent();
                        
                    }), NULL));
                    
                    cardB->runAction(Sequence::create(Spawn::create(FadeOut::create(0.25), ScaleTo::create(0.25, 0), NULL), CallFunc::create([cardB](){
                        
                        cardB->removeFromParent();
                        
                    }), NULL));
                    
                });
                
                _cardTable[dataA->row][dataA->column]=nullptr;
                _cardTable[dataB->row][dataB->column]=nullptr;
                
                _unfinishedCard -= 2;
                
                if (_unfinishedCard==0&&_completeCallBack) {
                    _completeCallBack();
                }
            }
            else {
                // 配对失败还原
                
                auto cardA=_selCardA;
                auto cardB=_selCardB;
                _selCardB->flipToFront([this, cardA, cardB](){
                    cardA->flipToBack();
                    cardB->flipToBack();
                });
                
            }
            _selCardA = nullptr;
            _selCardB = nullptr;
        }
        
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
}
