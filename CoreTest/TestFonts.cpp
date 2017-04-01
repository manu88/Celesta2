//
//  TestFonts.cpp
//  Celesta
//
//  Created by Manuel Deneu on 31/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <assert.h>
#include "Curve.hpp"
#include "GXFont.hpp"
#include "FontParser.hpp"

int main(int argc, const char * argv[])
{
    const GXFont *font = GXFont::loadFont("SourceSansPro-Black.ttf");
    
    
    assert(font);
    
    
    std::cout << "parsed font : " << font->getName()
              << " line space " << font->getLineSpace()
              << " num glyphes " << font->getNumGlyphes()
              <<  std::endl;
    
    return 0;
}
