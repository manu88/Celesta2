//
//  Display.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "Display.hpp"


Display::Display()
{
    
}

Display::~Display()
{
    
}

bool Display::init()
{
    return _impl.init();
}
bool Display::deInit()
{
    return _impl.deInit();
}
