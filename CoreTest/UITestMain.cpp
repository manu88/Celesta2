//
//  GXTestMain.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <map>
#include <GroundBase.hpp>
#include <GBBinCoder.hpp>

#include "CLApplicationDelegate.hpp"
#include "CLApplication.hpp"

#include "StringOperations.hpp"
#include "GXElement.hpp"
#include "GXLayer.hpp"
#include "GXRenderer.hpp"
#include "GXPath.hpp"
#include "Display.hpp"
#include "GXText.hpp"
#include "../Drivers/TCPMouse.hpp"

#include "UIView.hpp"

class MyAppDelegate  : public CLApplicationDelegate
{
public:
    MyAppDelegate():
    _mouse(11000),
    input(STDIN_FILENO)
    {
        
    }
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
        
        //loadUI("file.xml");

        const GB::Variant serializeTest = getApp()->serialize();
        
        
        
        
    }
    
    void didStart()
    {
        assert(disp.start());
        
        std::cout << "App did Start" << std::endl;
        
        mainElement.setBackgroundColor(makeColor(255,0,0));
        
        const GXRect b = makeRect(0, 0, 1920, 1080);
        mainElement.setBounds( b );
        assert(mainElement.getBounds() == b);
        

        disp.setDisplayedElement(&mainElement);
        
        
        view1.setBounds(makeRect(100, 100, 800, 600));
        
        mainElement.addChild(&view1);
        

        mainElement.setIdentifier("main");
        disp.setIdentifier("disp");
        view1.setIdentifier("view1");
        
        
        _elements.push_back( getApp() );
        _elements.push_back( &mainElement);
        _elements.push_back( &disp);
        _elements.push_back( &view1);
        
        std::cout << "commands type SEL TARGET ARGS .." << std::endl;
        
        input.notification = std::bind(&MyAppDelegate::keyInput, this , std::placeholders::_1);
        _mouse.callback = std::bind(&MyAppDelegate::mouseInput, this , std::placeholders::_1);

        assert(_mouse.addToRunLoop(getApp()->getRunLoop()) );
        getApp()->getRunLoop().addSource(input);

        
    }
    
    void mouseInput( const TCPMouseMsg &msg)
    {
        printf("Mouse %i %i Event %i Buttons %i\n" , msg.x , msg.y , msg.event , msg.button);
        return;
    }
    
    void keyInput( GBRunLoopSourceNotification notif)
    {
        if( notif == GBRunLoopSourceCanRead)
        {
            static char buf[64];
            memset(buf, 0, 64);
            if(input.read(buf, 64))//  GBRunLoopSourceRead(source, buf, 64))
            {
                const std::string cmds = StringOperations::reduce( buf , "" , "\n");
                
                parseCommands(cmds);
                return;
            }
        }
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
        
        
        
    }
    
    void parseCommands( const std::string &cmds)
    {
        if( cmds.empty())
            return;
        
        printf("Command '%s' \n" , cmds.c_str());
        
        std::vector< std::string> args = StringOperations::split(cmds, ' ');
        
        if( args.empty())
            return;
        
        if( args.at(0) == "list")
        {
            printf("%zi Elements : \n" , _elements.size());
            
            for (auto const el : _elements)
            {
                printf("\t'%s' %s \n" ,el->getIdentifier().c_str() , el->getClassName().c_str() );
            }
        }
        else if( args.size() > 1)
        {
            if( args.at(0) == "sels")
            {
                const std::string targetName = args[1];
                
                auto iter = std::find_if(_elements.cbegin(),_elements.cend(), [targetName]( const CLElement* el)
                {
                    if( el->getIdentifier() == targetName)
                        return true;
                    
                    return false;
                });
                
                if( iter == _elements.end())
                {
                    printf("Target '%s' not found \n" , targetName.c_str() );
                    return;
                }
                CLElement* target =  *iter;
                
                if( target)
                {
                    printf("%zi Selectors for '%s' class %s \n" , target->getSelectors().size() , targetName.c_str() , target->getClassName().c_str());
                    
                    for (auto &sel : target->getSelectors())
                    {
                        printf("\tSEL '%s' \n" , sel.first.c_str() );
                    }
                }
            }
            else
            {
                
                printf("Perform '%s' on '%s' with args :" , args[0].c_str() , args[1].c_str() );
                const CLElement::Selector sel = args[0];
                const std::string targetName = args[1];
                
                auto iter = std::find_if(_elements.cbegin(),_elements.cend(), [targetName]( const CLElement* el)
                                         {
                                             if( el->getIdentifier() == targetName)
                                                 return true;
                                             
                                             return false;
                                         });
                
                if( iter == _elements.end())
                {
                    printf("Target '%s' not found \n" , targetName.c_str() );
                    return;
                }
                CLElement* target =  *iter;
                if( !target)
                {
                    return;
                }
                args.erase(args.begin());
                args.erase(args.begin());
                
                if( args.size() == 0)
                {
                    printf("None");
                }
                GB::Variant arguments({});
                
                for (const std::string &a : args)
                {
                    arguments.getList().push_back(a);
                }
                
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
    }

private:
    Display disp;
    TCPMouse _mouse;
    GB::FDSource input;
    
    std::list<CLElement*> _elements;
    
    GXLayer mainElement;

    UIView view1;
    

    


    
};


int main(int argc, const char * argv[])
{
    GB::ObjectWrapper::enableInvalidReleaseDebug(true);
    {
        CLApplication app("app");
        MyAppDelegate delegate;
        
        app.setDelegate(&delegate);
        app.start();
        
        std::cout << "App returned " << std::endl;
    }
    GB::ObjectWrapper::introspection(true);
    return 0;
}
