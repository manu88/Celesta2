//
//  GXElement.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "GXElement.hpp"


GXElement::GXElement():
_bounds(makeRectNULL())
{
    
}

GXElement::~GXElement()
{
    
}


void GXElement::setBounds( const GXRect &bounds )
{
    _bounds = bounds;
}
const GXRect& GXElement::getBounds() const
{
    return _bounds;
}

void GXElement::setSize( const GXSize &size)
{
    setBounds( makeRect(_bounds.origin, size ) );
}
