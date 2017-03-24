//
//  GXTestMain.cpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

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
    
    const GXRect b = makeRect(0, 0, 1920, 1080);
    mainElement.setBounds( b );
    assert(mainElement.getBounds() == b);
    
    GXElement child1;
    child1.setBounds(  makeRect(100, 50, 200, 100) );
    child1.setZPos(1);
    GXElement child2;
    child2.setBounds(  makeRect(140, 80, 200, 100) );
    child2.setZPos(0);
 
    mainElement.addChild(&child1);
    mainElement.addChild(&child2);
    
    GXRenderer renderer;
    renderer.setDisplayedElement(&mainElement);
    renderer.setBounds(  makeRect(0, 0, 1920, 1080) );
    renderer.update();

    GXPath path( makeRect(200, 300, 400, 200));
    path.addRect(path.getBoundingRect());
    path.setFillColor(makeColor(0, 0, 255 ));
    path.fill();

    disp.update();
while(1)
{
}

    return 0;
}
