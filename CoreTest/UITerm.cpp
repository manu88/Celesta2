//
//  UITerm.cpp
//  Celesta
//
//  Created by Manuel Deneu on 04/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UITerm.hpp"
#include <GBRunLoopSource.hpp>

#include "GXPath.hpp"
#include "GXText.hpp"
#include "GXFont.hpp"
#include "CLApplication.hpp"
#include "StringOperations.hpp"


UITerm::UITerm(CLApplication *app):
UIView(app),
CLElement("UITerm")
{
    
    _drawCarret = false;
    
    setWindowTitle("Terminal");

    
    setBackgroundColor(makeColor(10, 10, 10 , 230));
    

    currentLine = addLine();
    
    _timer.setInterval(1000);
    _timer.setCallback( std::bind(&UITerm::onTime, this , std::placeholders::_1));
    
    getApplication()->getRunLoop().addSource(_timer);
    
    
}

void UITerm::viewDidUnload()
{
    printf("UITerm::viewDidUnload() \n");
    
    if(!getApplication()->getRunLoop().removeSource(_timer))
    {
        DEBUG_ASSERT(0);
    }
    
    
}

UITerm::~UITerm()
{
    clear();
    
}

void UITerm::clear()
{
    for( GXText *text : _lines)
    {
        removeChild(text);
        delete text;
    }
    
    _lines.clear();
}


void UITerm::onTime(GB::Timer &timer)
{
    
    _drawCarret = ! _drawCarret;
    setNeedsDisplay();
    
    
}
void UITerm::paintContent( const GXRect &rect)
{
    GXPath pathC( rect);
    pathC.addRoundedRect(makeRect(makePointNULL(), rect.size), 5.f, 5.f);
    pathC.setFillColor( getBackgroundColor() );
    pathC.fill();
    
    pathC.clear();
    
    
    int yPos = 0;
    for( GXText* t : _lines)
    {
        yPos += 20;
        t->setBounds(makeRect(makePoint(10, rect.size.height - yPos), t->getBounds().size));
        
        
    }
    
    
    if( !hasFocus())
        _drawCarret = false;
    
    if( _drawCarret)
    {
        //printf("Text W = %i \n" , _text->getBounds().size.width);
        
        pathC.addRect( makeRect( currentLine->getBounds().size.width + 12 , rect.size.height - yPos , 10 , 15));
        pathC.setFillColor(makeColor(0, 254, 82));
        pathC.fill();
    }
    
    
    
    
}

GXText* UITerm::addLine()
{
    GXText* line = new GXText();
    line->setFont(GXFont::loadFont("LucidaGrandeRegular.ttf"));
    line->setText(":>");
    line->setTextSize(16);
    line->setTextColor(makeColor(0, 254, 82));
    
    _lines.push_back(line);
    
    addChild(line);
    
    currentLine = line;
    return line;
}

void UITerm::focusChanged()
{
    printf("Term focus changed to %i\n" , hasFocus());
    
    
    _timer.setActive( hasFocus() );
    
    
}

bool UITerm::keyPressed( const GXKey &key )
{
    
    
    const char c = (char) key.code;
    std::string currentCmd = currentLine->getText();
    if( key.code == 13) // enter
    {
        
        parseCommands( currentCmd.substr(2) );
        addLine();
        currentLine->setText(":>");
        
        
        
    }
    else if( key.code == 127) // backspace
    {

        if( currentCmd.size() > 2)
        {
            currentCmd.erase(currentCmd.size() -1);
            currentLine->setText( currentCmd );
            currentLine->setNeedsDisplay();
        }
    }
    else
    {
        currentCmd.push_back(c);
        
        currentLine->setText( currentCmd );
        currentLine->setNeedsDisplay();
        
    }

    
    return true;
}

void UITerm::parseCommands( const std::string &cmds)
{
    if( cmds.empty())
        return;
    
    printf("Command '%s' \n" , cmds.c_str());
    
    std::vector< std::string> args = StringOperations::split(cmds, ' ');
    
    if( args.empty())
        return;
    
    if( args.size() == 1)
    {
        if( args.at(0) == "clear")
        {
            printf("Clearing term \n");
            clear();
        }
    }
    if( args.size() > 1)
    {
        if( args.at(0) == "sels")
        {
            const std::string targetName = args[1];
            
            CLElement* target =  getApplication()->getElement(targetName);
            
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
            
            CLElement* target =  getApplication()->getElement(targetName);
            
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
