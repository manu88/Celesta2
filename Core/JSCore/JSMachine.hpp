//
//  JSMachine.hpp
//  Celesta
//
//  Created by Manuel Deneu on 22/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef JSMachine_hpp
#define JSMachine_hpp

#include <stdio.h>
#include <list>
#include <vector>
#include "TinyJS/TinyJS.h"

class JSMachine
{
    typedef std::function<void(CScriptVar *v)> JSMachineFunction;
public:
    JSMachine();
    ~JSMachine();
    
    bool executeBuffer( const std::string &buffer );
    CScriptVarLink evaluateComplex(const std::string &code);
    std::string evaluate(const std::string &code);
    bool parseScriptFile( const std::string &filename );
    bool importScriptFile( const std::string &filename );
    
    bool registerFunction( const std::string &identifier , JSMachineFunction callback);
private:
    struct NativeFunctionCall
    {
        JSMachineFunction callBack;
    };
    
    CTinyJS _machine;
    std::vector< std::string > _importedHeaders;
    std::list<NativeFunctionCall*> _nativeCalls;
    
    static void js_print(CScriptVar *v, void *userdata);
    static void js_callback(CScriptVar *v, void *userdata);
    static void js_import(CScriptVar *v, void *userdata);
};

#endif /* JSMachine_hpp */
