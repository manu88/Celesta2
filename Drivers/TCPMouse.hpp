//
//  TCPMouse.hpp
//  Celesta
//
//  Created by Manuel Deneu on 02/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef TCPMouse_hpp
#define TCPMouse_hpp

#include <functional>
#include <GBObjectWrapper.hpp>
#include <GBSocket.h>
#include "CLElement.hpp"
#include "TCPMouseDefs.h"

namespace GB
{
    class RunLoop;
}
class TCPMouse : public CLElement , GB::ObjectWrapper
{
public:
    
    typedef std::function<void(const TCPMouseMsg& state)> MouseCallBack;
    
    TCPMouse( int port);
    ~TCPMouse();
    
    bool addToRunLoop(GB::RunLoop &);
    
    MouseCallBack callback;
    
private:
    
    static void listenerCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification);
    static void clientCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification);
    
    const GB::RunLoop* _runLoop;

    
    
};

#endif /* TCPMouse_hpp */
