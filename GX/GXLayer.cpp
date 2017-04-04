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
CLElement("GXLayout"),
_transparent(true)
{
    
}
GXLayer::~GXLayer()
{
    
}

void GXLayer::setTransparent( bool transparent ) noexcept
{
    _transparent = transparent;
}

void GXLayer::paint(const GXRect &rect)
{
    if( !_transparent)
    {
        GXPath path( rect);
        path.addRect(makeRect(makePointNULL(), rect.size) );
        path.setFillColor( getBackgroundColor() );
        path.fill();
    }
    GXElement::paint(rect);
}
