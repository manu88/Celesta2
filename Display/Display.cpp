//
//  Display.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//


#include <GroundBase.hpp>
#include "Display.hpp"

#ifdef TARGET_RASPBERRY_PI
#include "impl/DisplayImplRPI.hpp"
#else
#include "../Dummies/DisplayImplDum.hpp"
#endif

#include "impl/AbstractDisplayImpl.hpp"
#include "GXRenderer.hpp"


Display::Display():
_impl(nullptr)
{
#ifdef TARGET_RASPBERRY_PI
    _impl = new DisplayImplRPI();
#else
    _impl = new DisplayImplDummy();
#endif

    DEBUG_ASSERT(_impl);
    
    _guiThread.setName("Celesta.GUI");
    _guiThread.setMain(std::bind(&Display::startGUI, this));
}

Display::~Display()
{
    DEBUG_ASSERT(_impl);
    
    if( _impl)
    {
        delete _impl;
    }
    
}

bool Display::init()
{
    DEBUG_ASSERT(_impl);
        
    return _impl->init();
}
bool Display::deInit()
{
    DEBUG_ASSERT(_impl);
    
    return _impl->deInit();
}

bool Display::update()
{
    DEBUG_ASSERT(_impl);

    
    if( updateContent() )
    {
        return _impl->update();
    }
    
    return false;
}

bool Display::start()
{
    return _guiThread.start();
}
bool Display::stop()
{
    return _guiThread.sendStop();
}


void Display::needsDisplay()
{
    std::cout << "DISP needsDisplay " << std::endl;
    _guiThread.wake();
}


void Display::startGUI()
{
    std::cout << "Start GUI Thread" << std::endl;
    
    update();
    while ( !_guiThread.shouldReturn() )
    {
        if(_guiThread.waitForever())
        {
            std::cout << "DISP Update " << std::endl;
        }
    }
    
}
