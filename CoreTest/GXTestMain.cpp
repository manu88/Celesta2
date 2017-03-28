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

#include "CLApplicationDelegate.hpp"
#include "CLApplication.hpp"

#include "StringOperations.hpp"
#include "GXElement.hpp"
#include "GXRenderer.hpp"
#include "GXPath.hpp"
#include "Display.hpp"


class MyAppDelegate  : public CLApplicationDelegate
{
    void willStart()
    {
        std::cout << "App will Start" << std::endl;
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
        
        
    }
    
    void didStart()
    {
        std::cout << "App did Start" << std::endl;
        
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
        
        
        _elements.insert(std::make_pair("app", getApp() ) );
        _elements.insert(std::make_pair("win1", &win1));
        _elements.insert(std::make_pair("child2", &child2));
        _elements.insert(std::make_pair("win3", &win3));
        _elements.insert(std::make_pair("win4", &win4));
        _elements.insert(std::make_pair("disp", &disp));
        
        std::cout << "commands type SEL TARGET ARGS .." << std::endl;
        
        input =  GBFDSourceInitWithFD(STDIN_FILENO, inputCallback);
        GBRunLoopSourceSetUserContext(input, this);
        
        
        getApp()->getRunLoop().addSource(input);
        
        
    }
    static void inputCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification)
    {
        MyAppDelegate* self =  static_cast<MyAppDelegate*>( GBRunLoopSourceGetUserContext(source) );
        assert(self);
        self->termCallback(source, notification);
    }
    void termCallback( GBRunLoopSource* source , GBRunLoopSourceNotification notification)
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
            }
        }

    }
    
    void willStop()
    {
        std::cout << "App will end " << std::endl;
        disp.stop();
    }
    
    void didStop()
    {
        std::cout << "App did end " << std::endl;
        GBRelease(input);
        
        
    }
    
    void parseCommands( const std::string &cmds)
    {
        printf("Command '%s' \n" , cmds.c_str());
        
        std::vector< std::string> args = StringOperations::split(cmds, ' ');
        
        if( args.at(0) == "list")
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
                std::cout << "returned :" << ret << std::endl;
            }
            else
            {
                std::cout << "returned NULL Variant" << std::endl;
            }
        }
    }

    
private:
    
    std::map<const std::string, CLElement*> _elements;
    
    GXElement mainElement;
    GXElement win1;
    GXElement child2;
    Display disp;
    GBFDSource* input;
    /*
    GB::Timer timer;
    GB::RunLoop runLoop;
     */
    
};


int main(int argc, const char * argv[])
{
    {
        CLApplication app("com.myApp");
        MyAppDelegate delegate;
        
        app.setDelegate(&delegate);
        app.start();
        
        std::cout << "App returned " << std::endl;
    }
    GB::ObjectWrapper::introspection(true);
    return 0;
}
