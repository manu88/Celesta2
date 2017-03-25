//
//  GXElement.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <algorithm>
#include <GroundBase.hpp>

#include "GXElement.hpp"
#include "GXColors.hpp"
#include "GXPath.hpp"

GXElement::GXElement():
_bounds( makeRectNULL() ),
_zOrder( 0 ),
_backgroundColor( makeColor(0,0,0)),
_parent( nullptr ),
_needsUpdate(false),
_updateRect( makeRectNULL() )
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

/* **** **** **** **** **** **** **** **** **** **** */

void GXElement::moveTo( const GXPoint &point )
{
    setBounds( makeRect(point, getBounds().size));
}

void GXElement::moveOf( int dX , int dY)
{
    moveTo( makePoint( _bounds.origin.x + dX, _bounds.origin.y + dY)); // call ElementChanged!
}

void GXElement::moveTo( int x , int y)
{
    moveTo( makePoint(x, y)); // call ElementChanged!
}

/* **** **** **** **** **** **** **** **** **** **** */

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


void GXElement::setBackgroundColor(const GXColor & color)
{
    _backgroundColor = color;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** */
/*
    Hierarchy
 */

bool GXElement::addChild( GXElement* element )
{
    if( !element)
        return false;
    
//    if( element->_parent == this)
//        return true;
    
    DEBUG_ASSERT( std::find(_children.begin(), _children.end(), element) == _children.end());
    
    _children.push_back(element);
    element->_parent = this;
    
    sortChildren();
    
    element->setNeedsDisplay(element->getBounds());
    return true;
}

bool GXElement::removeChild(GXElement *element)
{
    if( !element)
        return false;

    DEBUG_ASSERT(element->_parent == this);
    
//    if(element->_parent != this)
//        return false;
    
    _children.erase(std::remove( _children.begin(), _children.end(), element), _children.end());

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
    Updates
 */

void GXElement::setNeedsDisplay()
{
    setNeedsDisplay(getBounds());
}
void GXElement::setNeedsDisplay( const GXRect &rect )
{
    _updateRect = rect;
    _needsUpdate = true;
    needsDisplay();
    if(_parent)
    {
        _parent->setNeedsDisplay( rect );
    }
}
/* **** **** **** **** **** **** **** **** **** **** **** **** */
/*
    Render
 */

void GXElement::needsDisplay()
{    
}

void GXElement::paint(const GXRect &rect)
{
    //printInfos( std::cout );
    
    GXPath path( rect);
    path.addRect(makeRect(makePointNULL(), rect.size));
    path.setFillColor( _backgroundColor );
    path.fill();
    path.clear();
    
    if( !_children.empty())
    {
        
        
        for (auto const child : _children)
        {
            const GXRect b = makeRect(getBounds().origin + child->getBounds().origin, child->getBounds().size );
            //printf("Paint at %i %i %i %i \n" , b.origin.x , b.origin.y , b.size.width , b.size.height);
            child->paint( b );
        }
    }
    
    _needsUpdate = false;
}

void GXElement::printInfos(std::ostream &stream) const
{
    stream << "Geometry "
           << " x=" << _bounds.origin.x
           << " y=" << _bounds.origin.y
           << " w=" << _bounds.size.width
           << " h=" << _bounds.size.height
           << " z=" << _zOrder
           << " Color = " << (int) _backgroundColor.r
                   << "/" << (int) _backgroundColor.g
                   << "/" << (int) _backgroundColor.b
                   << "/" << (int) _backgroundColor.a;
    
    
    if( !_children.empty())
    {
        stream << " Child " << _children.size() <<   std::endl;
    }
    stream << std::endl;
}

