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

UITerm::UITerm(CLApplication *app):
UIView(app),
CLElement("UITerm")
{
    
    setWindowTitle("Terminal");
    
    _text = new GXText();
    _text->setFont(GXFont::loadFont("LucidaGrandeRegular.ttf"));
    
    _text->setText("Hello");
    _text->setTextSize(14);
    _text->setTextColor(makeColor(0, 254, 82));
    
    
    addChild(_text);
}
UITerm::~UITerm()
{
    delete _text;
}


void UITerm::paintContent( const GXRect &rect)
{
    GXPath pathC( rect);
    pathC.addRoundedRect(makeRect(makePointNULL(), rect.size), 5.f, 5.f);
    pathC.setFillColor( makeColor(10, 10, 10) );
    pathC.fill();
    
    _text->setBounds(makeRect(makePoint(10, rect.size.height - 20), makeSizeNULL()));
    
    
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
