//
//  Element.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <GBVariant.hpp>

#include "CLElement.hpp"

CLElement::CLElement( const std::string &className ):
_className(className)
{
    /*
    registerSelector("t",
                     std::bind(&CLElement::test,this  , std::placeholders::_1 ));
    */
    registerSelector("getClassName", std::bind( &CLElement::getClassName, this ));

    
}

CLElement::~CLElement()
{
    
}

bool CLElement::registerSelector( const Selector &name , Callable func)
{
 
    std::pair<Selector, Callable> p = std::make_pair(name,
                                                     func);
    return _selectors.insert(p).second;
}

const std::string &CLElement::getClassName() const noexcept
{
    return _className;// std::string( typeid(this).name());
}

const GB::Variant CLElement::perform( const Selector &sel, const GB::Variant &args)
{
    if( _selectors.find(sel) != _selectors.end())
    {
        const auto call = _selectors.at(sel);
        return call(args);
    }
    
    return GB::Variant::null();
}

bool CLElement::respondsTo( const Selector &sel ) const
{
    return _selectors.find(sel) != _selectors.end();
}

