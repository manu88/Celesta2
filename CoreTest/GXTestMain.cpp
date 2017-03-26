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
GB::Timer timer;
GB::RunLoop runLoop;


static void inputCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification)
{
    if( notification == GBRunLoopSourceCanRead)
    {
        char buf[10];
        if( GBRunLoopSourceRead(source, buf, 10))
        {

            
            bool update = false;
            if( buf[0] == 'q')
            {
                printf("move <- \n");
                win1.moveOf(-10 , 0);
                update = true;
            }
            else  if( buf[0] == 'd')
	    {
                printf("move -> \n");
                win1.moveOf(10 , 0);
                update = true;
            }
	    else  if( buf[0] == 'z')
            {
                printf("move -> \n");
                win1.moveOf(0 , 10);
                update = true;
            }
            else  if( buf[0] == 's')
            {
                printf("move -> \n");
                win1.moveOf(0 , -10);
                update = true;
            }
            else if( buf[0] == 't')
            {
                if(win1.removeChild( &child2))
                    update = true;
	 	else 
		    std::cout << "Error remove child" << std::endl;

            }
            else if( buf[0] == 'g')
            {
                if(win1.addChild( &child2))
                    update = true;
            	else 
		    std::cout << "Error add child" << std::endl;
	    }

            else  if( buf[0] == 'p')
            {
                printf("Send quit \n");
                GBRunLoopStop( GBRunLoopSourceGetRunLoop(source));
            }
	    else if( buf[0] == 'o')
	    {
		runLoop.removeSource(timer);
	    }
	    else if( buf[0] == 'l')
            {
                runLoop.addSource( timer);
            }
            
            if( update)
            {
                win1.setNeedsDisplay();
                /*
                if( !disp.update() )
                {
                    std::cout << "Error update Display " << std::endl;
                }
                 */
            }
            
        }
        
    }
}

int main(int argc, const char * argv[])
{
    {
        if(disp.init())
        {
            std::cout << "Display init OK " << std::endl;
        }
        else
        {
            std::cout << "Display init Error " << std::endl;
        }
        
        
        disp.setBounds(  makeRect(0, 0, 1920, 1080) );
        assert(disp.start());
        
        
        GXElement mainElement;
        mainElement.setBackgroundColor(makeColor(255,0,0));

        const GXRect b = makeRect(0, 0, 1920, 1080);
        mainElement.setBounds( b );
        assert(mainElement.getBounds() == b);
        
        
        win1.setBounds(  makeRect(100, 50, 200, 150) );
        win1.setZPos(0);
        win1.setBackgroundColor(makeColor(0,255,0));

        GXElement win3;
        win3.setBounds(  makeRect(100, 50, 200, 150) );
        win3.setZPos(3);
        win3.setBackgroundColor(makeColor(127,0,127 , 127));
        mainElement.addChild(&win3);

	GXElement win4;
        win4.setBounds(  makeRect(600, 60, 600, 500) );
        win4.setZPos(4);
        win4.setBackgroundColor(makeColor(0,100,127 ));
        mainElement.addChild(&win4);

        
        child2.setBounds(  makeRect(0, 0, 170, 100) );
        child2.setZPos(1);
        child2.setBackgroundColor(makeColor(0,0,255));

        mainElement.addChild(&win1);
        win1.addChild(&child2);

        disp.setDisplayedElement(&mainElement);
        
        
        GBFDSource* input =  GBFDSourceInitWithFD(STDIN_FILENO, inputCallback);
        runLoop.addSource(input);
        
        timer.setInterval(10);
        timer.setCallback([&](GB::Timer &timer)
        {
	    GXColor col = win1.getBackgroundColor();
            col.a++;
            if( col.a>255)
                col.a = 0;
            
            win1.setBackgroundColor(col);

            win1.moveOf(5, 5);
 
            if( win1.getBounds().origin.y > 1080)
            {
                win1.moveTo(0,0);
            }
            
            win1.setNeedsDisplay();

        });
        
        //runLoop.addSource(timer);

        runLoop.run();


        GBRelease(input);
        
        disp.stop();
    }
    Introspection(true);

    
    return 0;
}
