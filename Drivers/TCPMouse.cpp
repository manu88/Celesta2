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
        TCPEventHeader header;
        memset(&header, 0, sizeof(TCPEventHeader));
        
        if( _client->read(&header, sizeof(TCPEventHeader)))
        {
            printf("Got TCPEvent %i %i \n" , header.code , header.size);
            
            if( header.code == TypeMouse )
            {
                TCPMouseMsg msg;
                
                if( _client->read(&msg , sizeof(TCPMouseMsg)))
                {
                    if( callback)
                    {
                        callback(msg);
                    }
                }
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
            DEBUG_ASSERT(_client);
            DEBUG_ASSERT(_runLoop);
            if( !_runLoop->addSource(*_client))
            {
                DEBUG_ASSERT(0);
            }

            _client->notification = std::bind(&TCPMouse::onClient, this , std::placeholders::_1);
            
        }
    }
    else
    {
        printf("Listened : other notif %i \n" , notification);
    }
}



