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
#include <map>
#include "StringOperations.hpp"
#include "GXElement.hpp"
#include "GXRenderer.hpp"
#include "GXPath.hpp"
#include "Display.hpp"



static std::map<const std::string, CLElement*> _elements;
GXElement win1;
GXElement child2;
Display disp;
GB::Timer timer;
GB::RunLoop runLoop;

static void quit()
{
    printf("Stop Display ...\n");
    disp.stop();
    printf("Done\n");
    printf("Stop RunLoop ...\n");
    runLoop.stop();
    printf("Done\n");
}

static void parseCommands( const std::string &cmds)
{
    printf("Command '%s' \n" , cmds.c_str());
    
    std::vector<std::string> args = StringOperations::split(cmds, ' ');

    if( args.at(0) == "quit")
    {
        quit();
        
    }
    else if( args.at(0) == "list")
    {
        printf("%zi Elements : \n" , _elements.size());
        
        for (auto const &el : _elements)
        {
            printf("\t'%s' %s \n" ,el.first.c_str() , el.second->getClassName().c_str());
        }
    }
    else if( args.at(0) == "sels")
    {
        const std::string targetName = args[1];
        CLElement* target =  _elements.find(targetName)->second;
        if( !target)
        {
            printf("Target '%s' not found \n" , targetName.c_str() );
            return;
        }
        printf("%zi Selectors for '%s' class %s \n" , target->getSelectors().size() , targetName.c_str() , target->getClassName().c_str());
        
        for (auto &sel : target->getSelectors())
        {
            printf("\tSEL '%s' \n" , sel.first.c_str() );
        }
    }
    else
    {
        
        printf("Perform '%s' on '%s' with args :" , args[0].c_str() , args[1].c_str() );
        const CLElement::Selector sel = args[0];
        const std::string targetName = args[1];
        CLElement* target =  _elements.find(targetName)->second;
        if( !target)
        {
            printf("Target '%s' not found \n" , targetName.c_str() );
            return;
        }
        args.erase(args.begin());
        args.erase(args.begin());
        
        if( args.size() == 0)
        {
            printf("None");
        }
        const GB::Variant arguments(args);
        
        for ( auto const &v : arguments.getList())
        {
            printf(" '%s' " , v.toString().c_str() );
        }
        printf("\n");
        
        const GB::Variant &ret =  target->perform(sel , arguments.getList().size() == 1? arguments.getList().at(0) : arguments);
        
        if (!ret.isNull())
        {
            std::cout << "returned :" << ret.toString() << std::endl;
        }
        else
        {
            std::cout << "returned NULL Variant" << std::endl;
        }
    }
}

static void inputCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification)
{
    if( notification == GBRunLoopSourceCanRead)
    {
        static char buf[64];
        memset(buf, 0, 64);
        if( GBRunLoopSourceRead(source, buf, 64))
        {
            const std::string cmds = StringOperations::reduce( buf , "" , "\n");
            
            parseCommands(cmds);
            
            return;
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

        
        _elements.insert(std::make_pair("win1", &win1));
        _elements.insert(std::make_pair("child2", &child2));
        _elements.insert(std::make_pair("win3", &win3));
        _elements.insert(std::make_pair("win4", &win4));
        _elements.insert(std::make_pair("disp", &disp));
        
        std::cout << "commands type SEL TARGET ARGS .." << std::endl;
        
        parseCommands("setBackgroundColor win1 1 4 3 4");
        const GXColor &c = win1.getBackgroundColor();
        printf("Background Color %i %i %i %i\n" ,c.r , c.g , c.b , c.a );
        //assert(c == makeColor(1, 2, 3 , 4));
        
        runLoop.run();


        GBRelease(input);
        
        disp.stop();
    }
    
    //GB::BinCoder::introspection(true);

    return 0;
}
