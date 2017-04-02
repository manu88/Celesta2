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
CLElement("TCPMouse")
{
    
    setGBObject(GBTCPSocketCreateListener(port,1, TCPMouse::listenerCallback));
    
    GBRunLoopSourceSetUserContext(getGBRef(), this);
    
}
TCPMouse::~TCPMouse()
{
    
}


bool TCPMouse::addToRunLoop(GB::RunLoop &runLoop)
{
    return runLoop.addSource( getGBObject<GBRunLoopSource*>());
    
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
    else
    {
        printf("Got CLient notification %i\n" , notification);
    }
}
/*static*/ void TCPMouse::listenerCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification)
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
