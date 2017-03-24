//
//  GXTestMain.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <GroundBase.hpp>
#include "GXElement.hpp"
#include "GXRenderer.hpp"
#include "GXPath.hpp"
#include "Display.hpp"


GXElement win1;
GXElement child2;
Display disp;

static void inputCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification)
{
    if( notification == GBRunLoopSourceCanRead)
    {
        char buf[10];
        if( GBRunLoopSourceRead(source, buf, 10))
        {

            
            bool update = false;
            if( buf[0] == 'a')
            {
                printf("move <- \n");
                child2.moveOf(-10 , 0);
                update = true;
            }
            else  if( buf[0] == 'z')
	    {
                printf("move -> \n");
                child2.moveOf(10 , 0);
                update = true;
            }
            else  if( buf[0] == 'q')
            {
                printf("Send quit \n");
                GBRunLoopStop( GBRunLoopSourceGetRunLoop(source));
            }
            
            if( update)
            {
                if( !disp.update() )
                {
                    std::cout << "Error update Display " << std::endl;
                }
            }
            
        }
        
    }
}

int main(int argc, const char * argv[])
{
    
    if(disp.init())
    {
        std::cout << "Display init OK " << std::endl;
    }
    else
    {
        std::cout << "Display init Error " << std::endl;
    }
    
    
    GXElement mainElement;
    mainElement.setBackgroundColor(makeColor(255,0,0));

    const GXRect b = makeRect(0, 0, 1920, 1080);
    mainElement.setBounds( b );
    assert(mainElement.getBounds() == b);
    
    
    win1.setBounds(  makeRect(100, 50, 200, 150) );
    win1.setZPos(0);
    win1.setBackgroundColor(makeColor(0,255,0));

    
    child2.setBounds(  makeRect(140, 80, 170, 100) );
    child2.setZPos(1);
    child2.setBackgroundColor(makeColor(0,0,255));

    mainElement.addChild(&win1);
    win1.addChild(&child2);
    
    GXRenderer renderer;
    renderer.setDisplayedElement(&mainElement);
    renderer.setBounds(  makeRect(0, 0, 1920, 1080) );
    
    
    disp.setRenderer(&renderer);

    
    if( !disp.update() )
    {
        std::cout << "Error update Display " << std::endl;
    }
    

    GBRunLoop* runLoop = GBRunLoopInit();
    
    GBFDSource* input =  GBFDSourceInitWithFD(STDIN_FILENO, inputCallback);
    GBRunLoopAddSource(runLoop, input);
    GBRunLoopRun(runLoop);
    
    GBRelease(runLoop);
    GBRelease(input);
    
    Introspection(true);

    
    return 0;
}
