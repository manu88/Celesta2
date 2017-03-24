//
//  JSMachine.cpp
//  Celesta
//
//  Created by Manuel Deneu on 22/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//
#include <iostream>
#include "JSMachine.hpp"
#include "FileSystem.hpp"

JSMachine::JSMachine()
{
    
    _machine.addNative("function print(text)" , &js_print, 0);
    _machine.addNative("function import(script)" , &js_import, this);
    
    
}
JSMachine::~JSMachine()
{
    for( NativeFunctionCall* call : _nativeCalls)
    {
        delete call;
    }
}

bool JSMachine::parseScriptFile( const std::string &filename )
{
    std::cout << "opening file " << filename << std::endl;
    

    if ( !FileSystem::fileExists( filename ) )
    {
        std::cout << "Cannot Open file " << filename << std::endl;
        return false;
    }
    
    const std::string buffer = FileSystem::getFileText( filename );
    
    executeBuffer( buffer );
    
    
    
    return true;
}

bool JSMachine::importScriptFile( const std::string &filename  )
{
    for ( auto i : _importedHeaders )
    {
        if ( i == filename)
            
            return true;
    }
    
    _importedHeaders.push_back( filename );
    
    
    if ( !FileSystem::fileExists( filename ))
    {
        return false;
    }
    
    const std::string buf = FileSystem::getFileText( filename );
    
    executeBuffer( buf );
    
    return true;
}


bool JSMachine::registerFunction( const std::string &identifier , JSMachineFunction callback)
{
    NativeFunctionCall *c = new NativeFunctionCall();
    c->callBack = callback;
    
    _nativeCalls.push_back(c);
    
    _machine.addNative(identifier , &js_callback, c);
    return true;
}

CScriptVarLink JSMachine::evaluateComplex(const std::string &code)
{
    return _machine.evaluateComplex(code);
}
std::string JSMachine::evaluate(const std::string &code)
{
    return _machine.evaluate(code);
}
bool JSMachine::executeBuffer( const std::string &buffer )
{
    try
    {
        _machine.execute(buffer);
        
        return true;
    }
    
    catch ( CScriptException *e )
    {
        std::cout << "JS ERROR " << e->text << std::endl;
        
    }
    
    return false;
}


/*static*/void JSMachine::js_print(CScriptVar *v, void *)
{
    printf("%s", v->getParameter("text")->getString().c_str() );
}

/*static*/ void JSMachine::js_callback(CScriptVar *v, void *userdata)
{
    NativeFunctionCall *c = static_cast<NativeFunctionCall*>(userdata);
    
    if( c == nullptr)
        return;
    
    try
    {
        c->callBack(v);
    }
    catch( const std::bad_function_call &err)
    {
        std::cout << "Bad Call " << err.what() << std::endl;
    }
}

/*static*/ void JSMachine::js_import(CScriptVar *v, void *userdata)
{
    const std::string &file = v->getParameter("script")->getString();
    JSMachine* self = static_cast<JSMachine*>(userdata);
    
    if( self)
    {
        const std::string folder = "/Users/manueldeneu/Documents/projets/dev/CelestaV2/JSLib/";
        
        std::cout << "Import File " << file << std::endl;
        
        self->importScriptFile(folder + file);
    }
}
