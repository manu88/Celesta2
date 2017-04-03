//
//  TCPMouse.cpp
//  Celesta
//
//  Created by Manuel Deneu on 02/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

//#include <GBRunLoop.h>
#include <GBRunLoop.hpp>
#include "TCPMouse.hpp"


TCPMouse::TCPMouse( int port) :
CLElement("TCPMouse"),
_listener(GBSocketTypeTCP , port , 1/* maxClient*/  ),
_client(nullptr),
_runLoop(nullptr)
{
    
    _listener.notification = std::bind(&TCPMouse::listenerCallback, this , std::placeholders::_1);
}

TCPMouse::~TCPMouse()
{
    if (_client)
    {
        delete _client;
    }
}


bool TCPMouse::addToRunLoop(GB::RunLoop &runLoop)
{
    if( runLoop.addSource(_listener))
    {
        _runLoop = &runLoop;
        return true;
    }
    
    return false;
    
}

void TCPMouse::onClient( GBRunLoopSourceNotification notification)
{
    if( notification == GBRunLoopSourceCanRead)
    {
        static TCPMouseMsg msg;
        if( _client->read(&msg, sizeof(TCPMouseMsg)))
        {
            printf("GOT MOUSE POS \n");
            if( callback)
            {
                callback(msg);
            }
        }
    }
    else
    {
        printf("Client : other notif %i \n" , notification);
    }
}
void TCPMouse::listenerCallback( GBRunLoopSourceNotification notification)
{
    printf("NOTIFICATION %i\n"  , notification);
    DEBUG_ASSERT(_client == nullptr);
    
    if( notification == GBRunLoopSourceCanRead)
    {
        _client = new GB::Socket(GBSocketTypeTCP);
        
        if( !_listener.accept(_client))
        {
            delete _client;
            _client = nullptr;
        }
        else
        {
            printf("Connection accepted \n");
            
            DEBUG_ASSERT(_runLoop);
            DEBUG_ASSERT(_runLoop->addSource(*_client));
            
            _client->notification = std::bind(&TCPMouse::onClient, this , std::placeholders::_1);
            
        }
    }
    else
    {
        printf("Listened : other notif %i \n" , notification);
    }
}

/*static*/ void TCPMouse::clientCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification)
{
    TCPMouse* self = static_cast<TCPMouse*>(  GBRunLoopSourceGetUserContext(source) );
    DEBUG_ASSERT(self);
    if( notification == GBRunLoopSourceCanRead)
    {
        static TCPMouseMsg msg;

        if( GBRunLoopSourceRead(source,&msg, sizeof(msg) ))
        {
            
            if( self->callback)
            {
                self->callback(msg);
            }
            
            //
        }
    }
    else if( notification == GBRunLoopSourceErrorRead)
    {
        printf("GBRunLoopSourceErrorRead \n");
        GBRunLoop* runloop = static_cast<GBRunLoop*>( const_cast<void*>( GBRunLoopSourceGetRunLoop(source)));
        
        GBRunLoopRemoveSource(runloop, source);
    }
    else
    {
        printf("Got CLient notification %i\n" , notification);
    }
}
/*
void TCPMouse::listenerCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification)
{
    TCPMouse* self = static_cast<TCPMouse*>(  GBRunLoopSourceGetUserContext(source) );
    DEBUG_ASSERT(self);
    
    if( notification == GBRunLoopSourceCanRead)
    {
        printf("Connection request \n");
        GBSocket* cSock = static_cast<GBSocket* >(source);
        GBSocket* client = GBSocketCreate(GBSocketGetType(cSock), clientCallback);
        
        GBRunLoopSourceSetUserContext(client, self);
        if(GBSocketAccept(cSock, client))
        {
            GBRunLoop* runloop = static_cast<GBRunLoop*>( const_cast<void*>( GBRunLoopSourceGetRunLoop(source)));
            if(GBRunLoopAddSource(runloop, client) == 0)
            {
                GBRelease(client);
                DEBUG_ASSERT(0);
            }
            
        }
        else
        {
            DEBUG_ASSERT(0);
        }
    }
    else
    {
        printf("Got Listener notification %i\n" , notification);
    }
}
 */
