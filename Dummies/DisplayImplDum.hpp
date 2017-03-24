//
//  DisplayImplDum.hpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef DisplayImplDum_hpp
#define DisplayImplDum_hpp

#include "AbstractDisplayImpl.hpp"

class DisplayImplDummy : public AbstractDisplayImpl
{
public:
    DisplayImplDummy();
    ~DisplayImplDummy();
    
    
    bool init() final override;
    bool deInit() final override;
    
    bool update() final override;
private: 
    
    
    
};

#endif /* DisplayImplDum_hpp */
