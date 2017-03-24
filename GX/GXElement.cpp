//
//  GXElement.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "GXElement.hpp"


GXElement::GXElement():
_bounds( makeRectNULL() ),
_zOrder( 0 ),
_parent( nullptr )
{
    
}

GXElement::~GXElement()
{
    
}

/* **** **** **** **** **** **** **** **** **** **** **** **** */
/*
    Geometry
 */

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

void GXElement::setZPos( int z)
{
    _zOrder = z;
}

int GXElement::getZPos() const
{
    return  _zOrder;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** */
/*
    Hierarchy
 */

bool GXElement::addChild( GXElement* element )
{
    _children.push_back(element);
    element->_parent = this;
    
    sortChildren();
    return true;
}

struct layer_comparor
{
    bool operator() (const GXElement* lhs, const GXElement* rhs) const
    {
        return lhs->getZPos() <= rhs->getZPos();
    }
};

void GXElement::sortChildren()
{
    std::sort(_children.begin() , _children.end(), layer_comparor() );
}

/* **** **** **** **** **** **** **** **** **** **** **** **** */
/*
    Render
 */

void GXElement::paint(const GXRect &rect)
{
    printInfos( std::cout );
}

void GXElement::printInfos(std::ostream &stream) const
{
    stream << "Geometry "
           << " x=" << _bounds.origin.x
           << " y=" << _bounds.origin.y
           << " w=" << _bounds.size.width
           << " h=" << _bounds.size.height
           << " z=" << _zOrder;
    
    
    if( !_children.empty())
    {
        stream << " Child " << _children.size() <<   std::endl;
        
        
        for (auto const child : _children)
        {
            stream << "     " ;
            child->paint(child->getBounds());
        }
    }
    stream << std::endl;
}

