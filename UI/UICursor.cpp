//
//  UICursor.cpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UICursor.hpp"
#include "GXPath.hpp"

UICursor::UICursor(): CLElement("UICursor")
{
    
}
UICursor::~UICursor()
{
    
}

void UICursor::paint(const GXRect &rect)
{
    GXPath path( rect);
    path.moveToPoint(makePoint(0, rect.size.height));
    path.addLineToPoint(makePoint(rect.size.width/2, rect.size.height*2/3));
    path.addLineToPoint(makePoint(0, rect.size.height*2/3));
    path.closePath();
    
    
    
    
    //path.addRoundedRect(makeRect(makePointNULL(), rect.size), 25.f, 25.f);
    path.setFillColor( getBackgroundColor() );
    path.fill();
    path.clear();
    
    GXElement::paint(rect);
}
