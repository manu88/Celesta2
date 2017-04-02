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

class MyAppDelegate  : public CLApplicationDelegate
{
public:
    MyAppDelegate():
    _mouse(11000)
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
        
        
        getApp()->registerSelector("move", [&]( const GB::Variant &vars )
        {
            win1.moveOf(50, 50);
            win1.setNeedsDisplay();
            return GB::Variant::null();
        });
        
        getApp()->registerSelector("save", [&]( const GB::Variant &vars )
                                   {
                                       
                                       return saveUI(vars.toString());
                                   });
        
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
        
        
        win1.setBounds(  makeRect(100, 50, 200, 150) );
        win1.setZPos(0);
        win1.setBackgroundColor(makeColor(0,255,0));
        
        
        win3.setBounds(  makeRect(100, 50, 200, 150) );
        win3.setZPos(3);
        win3.setBackgroundColor(makeColor(127,0,127 , 127));
        mainElement.addChild(&win3);
        
        
        win4.setBounds(  makeRect(600, 60, 600, 500) );
        win4.setZPos(4);
        win4.setBackgroundColor(makeColor(0,100,127 ));
        mainElement.addChild(&win4);
        
        
        child2.setBounds(  makeRect(0, 0, 170, 100) );
        child2.setZPos(1);
        child2.setBackgroundColor(makeColor(0,0,255));
        
        mainElement.addChild(&win1);
        win1.addChild(&child2);
        
        cursor.setZPos(40);
        cursor.setBackgroundColor(makeColor(0, 0, 0));
        mainElement.addChild(&cursor);
        
        disp.setDisplayedElement(&mainElement);
        
        win4.setText("Hello");
        
        mainElement.setIdentifier("main");
        win1.setIdentifier("win1");
        child2.setIdentifier("child2");
        win3.setIdentifier("win3");
        win4.setIdentifier("win4");
        disp.setIdentifier("disp");
        
        
        _elements.insert(std::make_pair("app", getApp() ) );
        _elements.insert(std::make_pair(mainElement.getIdentifier(), &mainElement));
        _elements.insert(std::make_pair(win1.getIdentifier(), &win1));
        _elements.insert(std::make_pair(child2.getIdentifier(), &child2));
        _elements.insert(std::make_pair(win3.getIdentifier(), &win3));
        _elements.insert(std::make_pair(win4.getIdentifier(), &win4));
        _elements.insert(std::make_pair(disp.getIdentifier(), &disp));
        
        std::cout << "commands type SEL TARGET ARGS .." << std::endl;
        
        input =  GBFDSourceInitWithFD(STDIN_FILENO, inputCallback);
        GBRunLoopSourceSetUserContext(input, this);
        
        _mouse.callback = [&](const TCPMouseMsg &msg)
        {
            //printf("Did read %i %i Button %i\n" , msg.x , msg.y , msg.button);
            cursor.moveTo(msg.x, msg.y);
            cursor.setNeedsDisplay();
        };
        
        _mouse.addToRunLoop(getApp()->getRunLoop());
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
        if( cmds.empty())
            return;
        
        printf("Command '%s' \n" , cmds.c_str());
        
        std::vector< std::string> args = StringOperations::split(cmds, ' ');
        
        if( args.empty())
            return;
        
        if( args.at(0) == "list")
        {
            printf("%zi Elements : \n" , _elements.size());
            
            for (auto const &el : _elements)
            {
                printf("\t'%s' %s \n" ,el.first.c_str() , el.second->getClassName().c_str());
            }
        }
        else if( args.size() > 1)
        {
            if( args.at(0) == "sels")
            {
                const std::string targetName = args[1];
                if( _elements.count(targetName) == 0)
                {
                    printf("Target '%s' not found \n" , targetName.c_str() );
                    return;
                }
                CLElement* target =  _elements.find(targetName)->second;
                
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
                
                if( _elements.count(targetName) == 0)
                {
                    printf("Target '%s' not found \n" , targetName.c_str() );
                    return;
                }
                CLElement* target =  _elements.find(targetName)->second;
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

    bool saveUI( const std::string &file)
    {
        GB::Variant children((GB::VariantList()));
        
        for(const GXElement* el : mainElement.getChildren())
        {
            const GB::Variant prop = el->serialize();
            
            children.getList().push_back(prop);
            
            
        }
        _doc.addValueForKey( children, "Children");
        
        return _doc.save(file);
    }
    
    bool loadUI( const std::string &file)
    {
        GB::XMLDocument doc(file);
        
        if( !doc.isValid())
            return false;
        
        std::cout << "parse file " << file << std::endl;
        
        const GB::Variant &children = doc.getValueForKey("Children");
        
        assert(children.isList());
        
        std::cout << "Got " << children.getList().size() << " children" << std::endl;
        
        for (const GB::Variant &child  : children.getList())
        {
            assert(child.isMap());
            const GB::Variant id = child.getMap().at("Identifier");
            assert(id.isString());
            std::cout << "\t id : " << id  << std::endl;
            
        }
        
        return false;
    }
private:
    
    
    GB::XMLDocument _doc;
    std::map<const std::string, CLElement*> _elements;
    
    TCPMouse _mouse;
    GBFDSource* input;
    
    GXLayer mainElement;
    GXLayer win1;
    GXLayer child2;
    Display disp;
    
    GXLayer win3;
    GXText win4;
    
    GXLayer cursor;
    /*
    GB::Timer timer;
    GB::RunLoop runLoop;
     */
    
};


int main(int argc, const char * argv[])
{
    GB::ObjectWrapper::enableInvalidReleaseDebug(true);
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
