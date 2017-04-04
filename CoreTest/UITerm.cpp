//
//  UITerm.cpp
//  Celesta
//
//  Created by Manuel Deneu on 04/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UITerm.hpp"
#include "GXPath.hpp"
#include "GXText.hpp"
#include "GXFont.hpp"
#include "CLApplication.hpp"
#include <GBRunLoopSource.hpp>

UITerm::UITerm(CLApplication *app):
UIView(app),
CLElement("UITerm")
{
    
    _drawCarret = false;
    
    setWindowTitle("Terminal");

    
    setBackgroundColor(makeColor(10, 10, 10 , 230));
    _text = new GXText();
    _text->setFont(GXFont::loadFont("LucidaGrandeRegular.ttf"));
    
    _text->setText("Hello");
    _text->setTextSize(14);
    _text->setTextColor(makeColor(0, 254, 82));
    
    addChild(_text);
    
    _timer.setInterval(1000);
    _timer.setCallback( std::bind(&UITerm::onTime, this , std::placeholders::_1));
    
    getApplication()->getRunLoop().addSource(_timer);
    
    
}
UITerm::~UITerm()
{
    
    delete _text;
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
    
    _text->setBounds(makeRect(makePoint(10, rect.size.height - 20), _text->getBounds().size));
    
    if( _drawCarret)
    {
        //printf("Text W = %i \n" , _text->getBounds().size.width);
        
        pathC.addRect( makeRect( _text->getBounds().size.width + 10 , rect.size.height - 20 , 10 , 15));
        pathC.setFillColor(makeColor(0, 254, 82));
        pathC.fill();
    }
    
    
    
    
}

void UITerm::focusChanged()
{
    printf("Term focus changed to %i\n" , hasFocus());
    
    
    _timer.setActive( hasFocus() );
    
    
}

bool UITerm::keyPressed( const GXKey &key )
{
    
    
    const char c = (char) key.code;
    if( key.code == 13) // enter
    {
        printf("Str : '%s' \n" , _currentCmd.c_str());
        
        
        _currentCmd = "";
        
        
    }
    else if( key.code == 127) // backspace
    {
        _currentCmd.erase(_currentCmd.size() -1);
        _text->setText(_currentCmd);
        _text->setNeedsDisplay();
    }
    else
    {
        _currentCmd.push_back(c);
        
        _text->setText(_currentCmd);
        _text->setNeedsDisplay();
        
    }

    
    return true;
}
