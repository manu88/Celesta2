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
CLElement("GXElement"),
_visible (true),
_bounds( makeRectNULL() ),
_zOrder( 0 ),
_backgroundColor( makeColor(0,0,0)),
_parent( nullptr ),
_needsUpdate(false),
_updateRect( makeRectNULL() )
{
    initSelectors();
}

void GXElement::initSelectors()
{
    
    registerSelector("setNeedsDisplay", [&](const GB::Variant &l)
    {
        setNeedsDisplay();
        return GB::Variant::null();
    });
    registerSelector("getZPos", std::bind( &GXElement::getZPos, this ));
    registerSelector("setZPos", [&](const GB::Variant &l)
    {
        setZPos(l.toInt());
        return GB::Variant::null();
     
    });
    
    registerSelector("getBounds", [&](const GB::Variant &l)
    {
        const GB::Variant &ret =  GXRectGetVariant(getBounds());
        return ret;
    });
    
    registerSelector("setBounds", [&](const GB::Variant &l)
    {
        setBounds( VariantGetRect(l));
        return GB::Variant::null();
    });
    
    registerSelector("setPos", [&](const GB::Variant &l)
    {
        setBounds( makeRect(VariantGetPoint(l)  , getBounds().size) );
        return GB::Variant::null();
    });
    
    registerSelector("getPos", [&](const GB::Variant &l)
    {
        return GXPointGetVariant(getBounds().origin);
    });
    
    registerSelector("getBackgroundColor", [&]( const GB::Variant &l)
    {
        const GXColor &c = getBackgroundColor();
        printf("will return color %i %i %i %i \n" , c.r , c.g , c.b , c.a);
        return GXColorGetVariant(c);
    });
    
    registerSelector("setBackgroundColor", [&]( const GB::Variant &l)
    {
        
        setBackgroundColor( VariantGetGXColor(l));
        return GB::Variant::null();
    });
    
    registerSelector("setVisible", [&]( const GB::Variant &l)
                     {
                         if( l.isNull())
                             return GB::Variant::null();
                         
                         setVisible( (bool) l.toInt());
                         return GB::Variant::null();
                     });
    
    registerSelector("isVisible", [&]( const GB::Variant &l)
                     {
                         return isVisible();
                     });
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

bool GXElement::setZPos( int z)
{
    _zOrder = z;
    return true;
}

int GXElement::getZPos() const
{
    return  _zOrder;
}


void GXElement::setBackgroundColor(const GXColor & color)
{
    _backgroundColor = color;
}

void GXElement::setVisible( bool vis)
{
    _visible = vis;
    
}

/* **** **** **** **** **** **** **** **** **** **** **** **** */
/*
    Hierarchy
 */

bool GXElement::addChild( GXElement* element )
{
    if( !element)
        return false;
    
    if( element == this)
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
    if(_parent)
    {
        _parent->setNeedsDisplay( rect );
    }
    
    needsDisplay();
    
    
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
    
    
    
    if( !_children.empty())
    {
        for (auto const child : _children)
        {
            DEBUG_ASSERT(child);
            
            if( child && child->isVisible())
            {
                const GXRect b = makeRect(getBounds().origin + child->getBounds().origin, child->getBounds().size );
                //printf("Paint at %i %i %i %i \n" , b.origin.x , b.origin.y , b.size.width , b.size.height);
                child->paint( b );
            }
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

GB::Variant GXElement::serialize() const
{
    GB::Variant r = CLElement::serialize();
    
    r.getMap().insert({ "ZPos" , getZPos() });
    r.getMap().insert({ "Bounds" , GXRectGetVariant( getBounds()) });
    r.getMap().insert({ "BackGroundColor" , GXColorGetVariant(getBackgroundColor())});
    
    return r;
}

