//
//  JSApplication.cpp
//  Celesta
//
//  Created by Manuel Deneu on 22/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>
#include <GBRunLoop.hpp>
#include "JSApplication.hpp"


JSApplication::JSApplication( const std::string &scriptFile ):
CLApplication("com.JSEngine.testApp"),
_appObj(nullptr)
{
    
    setDelegate(this);
    
    auto asyncCall = std::bind(&JSApplication::dispatchAsync, this , std::placeholders::_1);
    _jsEngine.registerFunction("function Dispatch.async(fct)", asyncCall );
    
    auto asyncAfterCall = std::bind(&JSApplication::dispatchAfter, this , std::placeholders::_1);
    _jsEngine.registerFunction("function Dispatch.after(timeMS , fct)", asyncAfterCall );
    
    auto startTimerCall = std::bind(&JSApplication::startTimer, this , std::placeholders::_1);
    _jsEngine.registerFunction("function startTimer(timer)", startTimerCall );
    
    _jsEngine.registerFunction("function startApp(app)", [&](CScriptVar *v)
    {
        v->trace();
        _appObj = v->deepCopy();
    });
    
    _jsEngine.registerFunction("function stopApp()", [&](CScriptVar *v)
    {
        stop();
    });
    
    if(_jsEngine.parseScriptFile( scriptFile ) == false)
    {
        std::cout << "Parse script ERROR" << std::endl;
    }
    
}
void JSApplication::dispatchAsync(CScriptVar *v)
{
    CScriptVar* fct = v->getParameter("fct")->ref();
    
    getRunLoop().dispatchAsync([&]()
   {
       _jsEngine.executeBuffer( fct->getString() );
       fct->unref();
   });
}

void JSApplication::dispatchAfter(CScriptVar *v)
{
    const int timeMS = v->getParameter("timeMS")->getInt();
    
    CScriptVar* fct = v->getParameter("fct")->ref();
    
    getRunLoop().dispatchAfter([&]()
   {
       _jsEngine.executeBuffer( fct->getString() );
       fct->unref();
   } , timeMS );
}

void JSApplication::startTimer(CScriptVar *v)
{
    std::cout << "start timer " << std::endl;
    CScriptVar* jstimer = v->getParameter("timer");
    
    const int timeMs = jstimer->getParameter("period")->getInt();
    CScriptVar* fct = jstimer->getParameter("callback");
    
    jstimer->trace();
    Timer* timer = new Timer();
    timer->setInterval(timeMs);
    timer->setCallback([&](Timer &timer)
    {
        _jsEngine.executeBuffer(fct->getString());
    });
    getRunLoop().addSource(*timer);
}

JSApplication::~JSApplication()
{
    if( _appObj)
    {
        delete _appObj;
    }
}

void JSApplication::willStart()
{
    DEBUG_ASSERT(_appObj);
    const std::string &instanceName = _appObj->firstChild->name;
    
    if( !instanceName.empty())
    {
        _jsEngine.executeBuffer(instanceName+".willStart();");
    }
}

void JSApplication::didStart()
{
    DEBUG_ASSERT(_appObj);
    const std::string &instanceName = _appObj->firstChild->name;
    
    if( !instanceName.empty())
    {
        _jsEngine.executeBuffer(instanceName+".didStart();");
    }
}

void JSApplication::willStop()
{
    DEBUG_ASSERT(_appObj);
    const std::string &instanceName = _appObj->firstChild->name;
    
    if( !instanceName.empty())
    {
        _jsEngine.executeBuffer(instanceName+".willStop();");
    }
}

void JSApplication::didStop()
{
    DEBUG_ASSERT(_appObj);
    const std::string &instanceName = _appObj->firstChild->name;
    
    if( !instanceName.empty())
    {
        _jsEngine.executeBuffer(instanceName+".didStop();");
    }
}
