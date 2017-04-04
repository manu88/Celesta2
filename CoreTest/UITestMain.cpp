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
#include "UICursor.hpp"
#include "UIMenuBar.hpp"
#include "UITerm.hpp"

#include "UIWinManager.hpp"

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
        getApp()->registerSelector("addView", [&]( const GB::Variant &v)
                                   {
                                       UIView* view = new UIView(getApp());
                                       
                                       view->setWindowTitle(v.toString());
                                       view->setIdentifier(v.toString());
                                       view->setBounds(makeRect(100,100,700,400));
                                       windows.addWindow(view);
                                       getApp()->addElement(view);
                                       
                                       
                                       return GB::Variant::null();
                                   });
        
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
        
        
        term = new UITerm(getApp());
        view2 = new UIView(getApp());
        
        _menuBar.setApplication(getApp());
        
        windows.setMenuBar(&_menuBar);

    }
    
    void didStart()
    {
        assert(disp.start());
        
        std::cout << "App did Start" << std::endl;
        
        mainElement.setTransparent(false);
        mainElement.setBackgroundColor(makeColor(100,127,110));
        
        const GXRect b = makeRect(0, 0, 1920, 1080);
        mainElement.setBounds( b );
        assert(mainElement.getBounds() == b);

        _menuBar.setBounds(makeRect(makePoint(0, mainElement.getBounds().size.height - 25),
                                    makeSize(mainElement.getBounds().size.width, 25)));
        _menuBar.setZPos(39);
        
        _menuBar.setIdentifier("menu");
        cursor.setIdentifier("cursor");
        
        windows.setBounds(makeRect(mainElement.getBounds().origin,
                                   makeSize(
                                            mainElement.getBounds().size.width, mainElement.getBounds().size.height-25)
                                   )
                          );
        
        term->setBounds(makeRect(100, 100, 800, 600));
        view2->setBounds(makeRect(700, 500, 800, 300));
        
        
        view2->setWindowTitle("Application 2");
        mainElement.addChild(&windows);
        
        windows.addWindow( view2 );
        windows.addWindow( term );
        disp.setDisplayedElement(&mainElement);
        

        mainElement.setIdentifier("main");
        disp.setIdentifier("disp");
        term->setIdentifier("term");
        view2->setIdentifier("view2");
        
        
        
        
        cursor.setZPos(40);
        cursor.setBounds(makeRect(0 , 0, 20, 30));
        cursor.moveTo( makePoint(mainElement.getBounds().size.width / 2, mainElement.getBounds().size.height / 2) );
        
        cursor.setBackgroundColor(makeColor(0, 0, 0));
        mainElement.addChild(&cursor);
        mainElement.addChild(&_menuBar);
        
        
        getApp()->addElement( getApp() );
        getApp()->addElement( &mainElement);
        getApp()->addElement( &disp);
        getApp()->addElement( term);
        getApp()->addElement( view2);
        getApp()->addElement( &_menuBar);
        getApp()->addElement( &cursor);
        
        std::cout << "commands type SEL TARGET ARGS .." << std::endl;
        
        input.notification = std::bind(&MyAppDelegate::keyInput, this , std::placeholders::_1);
        _mouse.mouseCallback = std::bind(&MyAppDelegate::mouseInput, this , std::placeholders::_1);
        _mouse.keyCallback = std::bind(&MyAppDelegate::keyboardInput, this , std::placeholders::_1);

        assert(_mouse.addToRunLoop(getApp()->getRunLoop()) );
        getApp()->getRunLoop().addSource(input);

        
    }
    
    void keyboardInput( const TCPKeyMsg &msg)
    {
        /*
        static std::string accum ="";
        
        const char key = (char) msg.keyCode;
        if( msg.keyCode == 13) // enter
        {
            printf("Str : '%s' \n" , accum.c_str());
            
            parseCommands(accum);
            accum = "";
            
            
        }
        else if( msg.keyCode == 127) // backspace
        {
            if( accum.size() > 1)
            {
                accum.erase(accum.size() -1);
            }
        }
        else
        {
            accum.push_back(key);
            
        }
         */
        GXKey k;
        k.code = msg.keyCode;
        k.keyState = KeyReleased;
        
        if( windows.getActiveView())
        {
            windows.getActiveView()->keyPressed(k);
        }
        
        
    }
    void mouseInput( const TCPMouseMsg &msg)
    {
        if( msg.event == Pressed)
        {
            touchBegan(makePoint(msg.x, msg.y));
        }
        else if( msg.event == Moved)
        {
            touchMoved(makePoint(msg.x, msg.y) , msg.button > 0);
        }
        else if( msg.event == Released)
        {
            touchEnded(makePoint(msg.x, msg.y));
        }
        
        return;
    }
    
    void touchBegan( const GXPoint &point)
    {

        for(GXElement* el : mainElement.getChildren())
        {
            if (el == &cursor )
            {
                continue;
            }
            if( rectContainsPoint(el->getBounds(), point))
            {
                UITouchDelegate* view = dynamic_cast<UITouchDelegate*>(el);
                
                if( view)
                {
                    GXTouch t;
                    t.center = point - el->getBounds().origin;
                    t.id = 1;
                    
                    if( view->touchesBegan(t))
                        break;
                    
                }
                
            }
        }
        
        
    }
    void touchMoved( const GXPoint &point , bool pressed)
    {
        cursor.moveTo(makePoint(point.x, point.y-cursor.getBounds().size.height));
        
        cursor.setNeedsDisplay();
        
        for(GXElement* el : mainElement.getChildren())
        {
            if (el == &cursor )
            {
                continue;
            }
            if( rectContainsPoint(el->getBounds(), point))
            {
                UITouchDelegate* view = dynamic_cast<UITouchDelegate*>(el);
                
                if( view)
                {
                    GXTouch t;
                    t.center = point - el->getBounds().origin;
                    t.id = 1;
                    t.touchState  = pressed;
                    
                    if( view->touchesMoved(t))
                        break;
                    
                }
                
            }
        }
    }
    void touchEnded( const GXPoint &point)
    {
        for(GXElement* el : mainElement.getChildren())
        {
            if (el == &cursor )
            {
                continue;
            }
            if( rectContainsPoint(el->getBounds(), point))
            {
                UITouchDelegate* view = dynamic_cast<UITouchDelegate*>(el);
                
                if( view)
                {
                    GXTouch t;
                    t.center = point - el->getBounds().origin;
                    t.id = 1;
                    
                    if( view->touchesEnded(t))
                        break;
                    
                }
                
            }
        }
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
        windows.removeAllWindows();
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
            printf("%zi Elements : \n" , getApp()->getElements().size());
            
            for (auto const el : getApp()->getElements())
            {
                printf("\t'%s' %s \n" ,el->getIdentifier().c_str() , el->getClassName().c_str() );
            }
        }
        else if( args.size() > 1)
        {
            if( args.at(0) == "sels")
            {
                const std::string targetName = args[1];
                CLElement* target = getApp()->getElement(targetName);
                
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
                
                CLElement* target = getApp()->getElement(targetName);
                
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
    

    
    GXLayer mainElement;
    UIMenuBar _menuBar;
    
    
    UIWinManager windows;

    UIView *term;
    UIView *view2;
    
    UICursor cursor;

    


    
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
