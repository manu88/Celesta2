//
//  GXRenderer.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>
#include "GXRenderer.hpp"


GXRenderer::GXRenderer():
CLElement("GXRenderer"),
_rootElement(nullptr)
{
    
}

GXRenderer::~GXRenderer()
{
    
}

bool GXRenderer::setDisplayedElement(GXElement* element)
{
    _rootElement = element;
    element->_parent = this;
    
    return true;
}

bool GXRenderer::updateContent()
{
    if( !_rootElement)
        return false;
    
    if( _rootElement->_needsUpdate)
    {
        _rootElement->paint(getBounds() );
    }
    
    

    return true;
}
