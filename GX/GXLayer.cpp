//
//  GXLayout.cpp
//  Celesta
//
//  Created by Manuel Deneu on 29/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "GXPath.hpp"
#include "GXLayer.hpp"


GXLayer::GXLayer():
CLElement("GXLayout")
{
    
}
GXLayer::~GXLayer()
{
    
}

void GXLayer::paint(const GXRect &rect)
{
    GXPath path( rect);
    path.addRoundedRect(makeRect(makePointNULL(), rect.size), 25.f, 25.f);
    path.setFillColor( getBackgroundColor() );
    path.fill();
    path.clear();
    
    GXElement::paint(rect);
}
