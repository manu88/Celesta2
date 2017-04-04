//
//  UITerm.cpp
//  Celesta
//
//  Created by Manuel Deneu on 04/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UITerm.hpp"
#include "GXPath.hpp"

UITerm::UITerm():CLElement("UITerm")
{
    
    setWindowTitle("Terminal");
}
UITerm::~UITerm()
{
    
}


void UITerm::paintContent( const GXRect &rect)
{
    GXPath pathC( rect);
    pathC.addRoundedRect(makeRect(makePointNULL(), rect.size), 5.f, 5.f);
    pathC.setFillColor( makeColor(10, 10, 10) );
    pathC.fill();
    
}
