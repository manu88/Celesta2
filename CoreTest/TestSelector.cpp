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

#include "GXLayer.hpp"
#include "GXRenderer.hpp"
#include "Display.hpp"
#include "CLApplication.hpp"

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
    assert(el.respondsTo("setZPos"));
    assert(el.respondsTo("getZPos"));
    assert(el.respondsTo("getBounds"));
    assert(el.respondsTo("setBounds"));
    assert(el.respondsTo("getBackgroundColor"));
    assert(el.respondsTo("setBackgroundColor"));

    assert(el.respondsTo("yoloLol") == false);
    
    const int zPos = 10;
    el.perform("setZPos", GB::Variant(zPos));
    assert(el.getZPos() == zPos);
    const GB::Variant &zPos2 = el.perform("getZPos" );
    assert(zPos2.isInt() && zPos2.getInt() == zPos);
    
    const GXRect bounds = makeRect(12, 34, 56, 78);
    
    el.perform("setBounds" , GB::Variant({ GB::Variant(12), GB::Variant(34), GB::Variant(56), GB::Variant(78) }) );
    
    const GB::Variant b = el.perform("getBounds");
    assert(b.isList());
    assert(b.getList().size() == 4 );
    assert(b.getList().at(0).getInt() == bounds.origin.x);
    assert(b.getList().at(1).getInt() == bounds.origin.y);
    assert(b.getList().at(2).getInt() == bounds.size.width);
    assert(b.getList().at(3).getInt() == bounds.size.height);
    
    
    el.perform("setBackgroundColor" , GXColorGetVariant(makeColor(10, 20, 30 , 40)));
    
    const GXColor &color = el.getBackgroundColor();
    const GB::Variant &colorVar = el.perform("getBackgroundColor");
    assert( VariantGetGXColor(colorVar) == color);
    
}

GXRect setValue( const GB::Variant &value)
{
    return VariantGetRect(value);
}
int testSet( int val)
{
    return val;
}

const GB::Variant testRet(const GXRect &r)
{
    return GXRectGetVariant(r);
}
int main(int argc, const char * argv[])
{
    GB::ObjectWrapper::enableInvalidReleaseDebug(true);
 
    {
        const GXRect rect = makeRect(100, 120, 130, 140);
        //
        const GB::Variant &v = testRet(rect);
        
        
        const GXRect &r = setValue(v);
        assert(r == rect);
        
        int inputV = 100;
        const GB::Variant implicitConv =  testSet( inputV );
        assert(implicitConv.isInt());
        assert(implicitConv.getInt() == inputV);

        assert(v.isList());
        assert(v.getList().size() == 4);
        assert(v.getList().at(0).getInt() == rect.origin.x);
        assert(v.getList().at(1).getInt() == rect.origin.y);
        assert(v.getList().at(2).getInt() == rect.size.width);
        assert(v.getList().at(3).getInt() == rect.size.height);
        GXRenderer rend;
        testClassName( rend );
        GXLayer el;
        testClassName(el);
        
        Display disp;
        testClassName(disp);
        testGXElement(disp);
         
        testGXElement(el);
    }
    {
        const std::string appID = "com.myCompanyName.myApplicationName";
        CLApplication app( appID);
        
        const GB::Variant vAppID = app.perform("getValueForKey" , std::string("identifier") );
        assert(vAppID.isString());
        assert(vAppID.getString() == appID);
    }
    
    GB::ObjectWrapper::introspection( true );
    //const GB::Variant &className
    return 0;
}
