//
//  DisplayImpl.h
//  Broadway_core
//
//  Created by Manuel Deneu on 27/01/15.
//  Copyright (c) 2015 Manuel Deneu. All rights reserved.
//

#ifndef __DisplayImpl__
#define __DisplayImpl__

#include "AbstractDisplayImpl.hpp"

class DisplayImplRPI : public AbstractDisplayImpl
{
public:
    DisplayImplRPI();
    ~DisplayImplRPI();
    

    bool init() final override;
    bool deInit() final override;
    
    bool update() final override;
private:
    


};

#endif /* defined(__DisplayImpl__) */
