//
//  UIMenuBar.cpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UIMenuBar.hpp"
#include "GXPath.hpp"
#include "GXText.hpp"
#include "GXFont.hpp"

UIMenuBar::UIMenuBar():CLElement("UIMenuBar")
{
    setBackgroundColor(makeColor(150 ,150, 150));
    
    _appTitle = new GXText();
    
    _appTitle->setFont(GXFont::loadFont("LucidaGrandeRegular.ttf"));
    _appTitle->setText("Hello");
    _appTitle->setTextSize(20);
    _appTitle->setTextColor(makeColor(0, 0, 0));
    addChild(_appTitle);
    
    
    registerSelector("setAppTitle", _appTitle->getSelectors().at("setText"));
    registerSelector("getAppTitle", _appTitle->getSelectors().at("getText"));
    
}

UIMenuBar::~UIMenuBar()
{
    
}

void UIMenuBar::paint(const GXRect &rect)
{
    GXPath path( rect);
    path.addRect(makeRect(makePointNULL(), rect.size));
    path.setFillColor( getBackgroundColor() );
    path.fill();
    
    _appTitle->setBounds(makeRect(makePoint(30, rect.size.height - 10), makeSizeNULL()));
    
    GXElement::paint(getBounds());
}

bool UIMenuBar::touchesBegan( const GXTouch &touches )
{
    return false;
}

bool UIMenuBar::touchesMoved( const GXTouch &touches )
{
    return false;
}

bool UIMenuBar::touchesEnded( const GXTouch &touches )
{
    return false;
}
