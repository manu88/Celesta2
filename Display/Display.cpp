//
//  Display.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "Display.hpp"

#ifdef TARGET_RASPBERRY_PI
#include "impl/DisplayImplRPI.hpp"
#endif

Display::Display():
_impl(nullptr)
{
#ifdef TARGET_RASPBERRY_PI
    _impl = new DisplayImplRPI();
#endif
}

Display::~Display()
{
    if( _impl)
    {
        delete _impl;
    }
    
}

bool Display::init()
{
    return _impl->init();
}
bool Display::deInit()
{
    return _impl->deInit();
}

void Display::update()
{
    _impl->update();
}
