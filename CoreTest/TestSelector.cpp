//
//  TestSelector.cpp
//  Celesta
//
//  Created by Manuel Deneu on 26/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//


#include <iostream>
#include <assert.h>

#include <GroundBase.hpp>

#include "GXElement.hpp"
#include "GXRenderer.hpp"
#include "Display.hpp"

static void testClassName( CLElement &el)
{
    assert(el.respondsTo("getClassName"));
    
    const std::string &className1 = el.getClassName();
    const GB::Variant& className2 = el.perform("getClassName");
    assert( !className2.isNull() && className2.isString());
    assert(className2.getString() == className1);
    
    std::cout << "Class name " << className1 << std::endl;
    std::cout << "Class name " << className2.getString() << std::endl;
    
}

static void testGXElement( GXElement &el)
{
    const int zPos = 10;
    el.perform("setZPos", GB::Variant(zPos));
    assert(el.getZPos() == zPos);
    const GB::Variant &zPos2 = el.perform("getZPos" );
    assert(zPos2.isInt() && zPos2.getInt() == zPos);
    
    const GXRect bounds = makeRect(12, 34, 56, 78);
    
    el.perform("setBounds" , GB::VariantList({ 12, 34, 56, 78 }) );
    
    //el.setBounds( bounds );
    
    const GB::Variant b = el.perform("getBounds");
    assert(b.isList());
    assert(b.getList().size() == 4 );
    assert(b.getList().at(0).getInt() == bounds.origin.x);
    assert(b.getList().at(1).getInt() == bounds.origin.y);
    assert(b.getList().at(2).getInt() == bounds.size.width);
    assert(b.getList().at(3).getInt() == bounds.size.height);
}

int main(int argc, const char * argv[])
{
    GB::ObjectWrapper::enableInvalidReleaseDebug(true);
 
    {
        GXRenderer rend;
        testClassName( rend );
        GXElement el;
        testClassName(el);
        
        Display disp;
        testClassName(disp);
        testGXElement(disp);
         
        testGXElement(el);
    }
    
    GB::ObjectWrapper::introspection( true );
    //const GB::Variant &className
    return 0;
}
