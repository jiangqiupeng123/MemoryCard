//
//  CardFactory.hpp
//  MemoryCard
//
//  Created by 江秋朋 on 16/1/9.
//
//

#ifndef CardFactory_hpp
#define CardFactory_hpp

#include <stdio.h>
#include "ICard.h"

class CardFactory {
    
public:
    virtual ICard* createCard(int backId, int number);
    
};

#endif /* CardFactory_hpp */
