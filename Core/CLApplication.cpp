//
//  CLApplication.cpp
//  Celesta
//
//  Created by Manuel Deneu on 22/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//
#ifdef DEBUG
#include <iostream>
#endif

#include "CLApplication.hpp"
#include "CLApplicationDelegate.hpp"


CLApplication::CLApplication( const std::string &identifier ):
CLElement("CLApplication"),

_delegate(nullptr)
{
    setIdentifier(identifier);
    
    registerSelector("stop", [&]( const GB::Variant& )
    {
        stop();
        return GB::Variant::null();
    });

    registerSelector("getValueForKey", [&]( const GB::Variant& key )
    {
        return getValueForKey(key.toString());
    });
    
    registerSelector("setValueForKey", [&]( const GB::Variant& params )
                     {
                         return _datas.addValueForKey(params.getList().at(0), params.getList().at(1).getString());
                         //return getValueForKey(key.toString());
                     });
    
    
}

CLApplication::~CLApplication()
{
    
}

void CLApplication::setDelegate( CLApplicationDelegate *delegate)
{
    _delegate = delegate;
    
    if( _delegate)
    {
        _delegate->_app = this;
    }
}

bool CLApplication::start() noexcept
{
    if( _runLoop.isRunning())
        return false;
    
    if( _delegate)
    {
        _delegate->willStart();
    }
    
    _runLoop.dispatchAsync([&]()
    {
       if( _delegate)
       {
           _delegate->didStart();
       }
    });
    
    if(_runLoop.run())
    {
        return true;
    }
    return false;
}

bool CLApplication::stop() noexcept
{
    if( !_runLoop.isRunning())
        return false;
    
    if( _delegate)
    {
        _delegate->willStop();
    }
    
    if(_runLoop.stop())
    {
        if( _delegate)
        {
            _delegate->didStop();
        }
        
        return true;
    }
    
    return false;
}

GB::Variant CLApplication::getValueForKey( const std::string &key) const noexcept
{
    const GB::Variant ret = _datas.getValueForKey(key);
    
    return ret;
}
