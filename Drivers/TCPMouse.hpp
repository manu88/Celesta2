//
//  TCPMouse.hpp
//  Celesta
//
//  Created by Manuel Deneu on 02/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef TCPMouse_hpp
#define TCPMouse_hpp

#include <GBObjectWrapper.hpp>
#include <GBSocket.h>
#include "CLElement.hpp"


namespace GB
{
    class RunLoop;
}
class TCPMouse : public CLElement , GB::ObjectWrapper
{
public:
    TCPMouse( int port);
    ~TCPMouse();
    
    bool addToRunLoop(GB::RunLoop &);
    
private:
    
    static void listenerCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification);
    static void clientCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification);
    
    const GB::RunLoop* _runLoop;

    
    
};

#endif /* TCPMouse_hpp */
