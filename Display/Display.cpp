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
    if( !_impl.initPlatform() )
    {
        std::cout << "Error init Platform Display Impl" << std::endl;
        return false;
    }

    if( !_impl.initDisplay() )
    {
        std::cout << "Error init Display Impl" << std::endl;
        return false;
    }
    
    
    return true;
}
bool Display::deInit()
{
    return _impl.deInitDisplay();
}
