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
    const std::string &className1 = el.getClassName();
    const GB::Variant& className2 = el.perform("getClassName", GB::VariantList() );
    assert( !className2.isNull() && className2.isString());
    assert(className2.getString() == className1);
    
    std::cout << "Class name " << className1 << std::endl;
    std::cout << "Class name " << className2.getString() << std::endl;
    
}


int main(int argc, const char * argv[])
{
    
    GXRenderer rend;
    testClassName( rend );
    GXElement el;
    testClassName(el);
    
    Display disp;
    testClassName(disp);
    
    
    //const GB::Variant &className
    return 0;
}
