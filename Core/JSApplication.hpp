//
//  JSApplication.hpp
//  Celesta
//
//  Created by Manuel Deneu on 22/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef JSApplication_hpp
#define JSApplication_hpp

#include "CLApplicationDelegate.hpp"
#include "CLApplication.hpp"
#include "JSCore/JSMachine.hpp"

class JSApplication : public CLApplicationDelegate , public CLApplication
{
public:
    JSApplication( const std::string &scriptFile);
    ~JSApplication();
private:
    void willStart();
    void didStart();
    void willStop();
    void didStop();
    
    void dispatchAsync(CScriptVar *v);
    void dispatchAfter(CScriptVar *v);
    void startTimer(CScriptVar *v);
    
    JSMachine _jsEngine;
    CScriptVar* _appObj;
};

#endif /* JSApplication_hpp */
