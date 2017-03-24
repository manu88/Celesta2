//
//  Display.hpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef Display_hpp
#define Display_hpp

#include "../Core/CLElement.hpp"
#include "impl/DisplayImpl.hpp"

class Display : public virtual CLElement
{
public:
    Display();
    ~Display();
    
    bool init();
    bool deInit();
};

#endif /* Display_hpp */
