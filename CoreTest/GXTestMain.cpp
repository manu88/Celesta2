//
//  GXTestMain.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <GroundBase.hpp>
#include "GXElement.hpp"
#include "GXRenderer.hpp"
#include "GXPath.hpp"
#include "Display.hpp"

int main(int argc, const char * argv[])
{
    Display disp;
    if(disp.init())
    {
        std::cout << "Display init OK " << std::endl;
    }
    else
    {
        std::cout << "Display init Error " << std::endl;
    }
    
    
    GXElement mainElement;
    mainElement.setBackgroundColor(makeColor(255,0,0));

    const GXRect b = makeRect(0, 0, 250, 150);
    mainElement.setBounds( b );
    assert(mainElement.getBounds() == b);
    
    GXElement child1;
    child1.setBounds(  makeRect(100, 50, 200, 100) );
    child1.setZPos(0);
    child1.setBackgroundColor(makeColor(0,255,0));

    GXElement child2;
    child2.setBounds(  makeRect(140, 80, 200, 100) );
    child2.setZPos(1);
    child2.setBackgroundColor(makeColor(0,0,255));

    mainElement.addChild(&child1);
    mainElement.addChild(&child2);
    
    GXRenderer renderer;
    renderer.setDisplayedElement(&mainElement);
    renderer.setBounds(  makeRect(0, 0, 1920, 1080) );
    
    
    disp.setRenderer(&renderer);

    
    if( !disp.update() )
    {
        std::cout << "Error update Display " << std::endl;
    }
    

    
    Introspection(true);

    while (1)
    {

    }
    return 0;
}
