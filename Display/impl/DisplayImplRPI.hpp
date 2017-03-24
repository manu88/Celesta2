//
//  DisplayImpl.h
//  Broadway_core
//
//  Created by Manuel Deneu on 27/01/15.
//  Copyright (c) 2015 Manuel Deneu. All rights reserved.
//

#ifndef __DisplayImpl__
#define __DisplayImpl__

#include <iostream>
#include <vector>


class DisplayImplRPI
{
public:
    DisplayImplRPI();
    ~DisplayImplRPI();
    

    bool init();
    bool deInit();
    
    void update();
private:  /* attributes */
    


};

#endif /* defined(__DisplayImpl__) */
