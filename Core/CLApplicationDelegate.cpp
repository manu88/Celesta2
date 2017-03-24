//
//  CLApplicationDelegate.cpp
//  Celesta
//
//  Created by Manuel Deneu on 22/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CLApplicationDelegate.hpp"


CLApplicationDelegate::~CLApplicationDelegate()
{
    
}

CLApplicationDelegate::CLApplicationDelegate():
_app(nullptr)
{
    
}

void CLApplicationDelegate::willStart()
{
    
}

void CLApplicationDelegate::didStart()
{
    
}

void CLApplicationDelegate::willStop()
{
    
}

void CLApplicationDelegate::didStop()
{
    
}

CLApplication* CLApplicationDelegate::getApp() const
{
    return _app;
}
