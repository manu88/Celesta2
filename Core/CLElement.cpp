//
//  Element.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <GBVariant.hpp>
#include <iostream> // DEBUG
#include <GBRunLoop.hpp>
#include <GBSequenceType.hpp>

#include "CLElement.hpp"

CLElement::CLElement( const std::string &className ):
_className(className)
{
    
    registerSelector("getClassName", std::bind( &CLElement::getClassName, this ));
    
    registerSelector("getIdentifier", std::bind( &CLElement::getIdentifier, this ));
    
    registerSelector("setIdentifier", [&](const GB::Variant &l)
                     {
                         setIdentifier(l.toString());
                         return GB::Variant::null();
                         
                     });

    
}

CLElement::~CLElement()
{
    
}

bool CLElement::registerSelector( const Selector &name , CallableFunction func)
{
 
    std::pair<Selector, CallableFunction> p = std::make_pair(name,
                                                     func);
    return _selectors.insert(p).second;
}

const std::string &CLElement::getClassName() const noexcept
{
    return _className;// std::string( typeid(this).name());
}

/*static*/ const GB::Variant CLElement::performAsync(const GB::RunLoop& runLoop,
                                                     CLElement* el ,
                                                     const Selector &sel ,
                                                     const GB::Variant &args
                                                     )
{
    runLoop.dispatchAsync([&]()
    {
        el->perform(sel , args);
    });
    return GB::Variant::null();
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

const std::map<const CLElement::Selector , CLElement::CallableFunction>& CLElement::getSelectors() const
{
    return _selectors;
}

void CLElement::setIdentifier( const std::string &id) noexcept
{
    _identifier = id;
}


GB::Variant CLElement::serialize() const
{
    std::cout << "CLElement serialization" << std::endl;
    
    const GB::Variant prop({
                            { "Class" , getClassName()},
                            { "Identifier" , getIdentifier()}
                           });

    return prop;
}


