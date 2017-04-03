//
//  UIMenuBar.cpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UIMenuBar.hpp"
#include "GXPath.hpp"

UIMenuBar::UIMenuBar():CLElement("UIMenuBar")
{
    setBackgroundColor(makeColor(150 ,150, 150));
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
    
    GXElement::paint(getBounds());
}
