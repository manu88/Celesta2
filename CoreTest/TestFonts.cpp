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
#include "LayoutManager.hpp"
#include "FontManager.hpp"

void printFaceInfo( const FT_Face face)
{
    printf("Face %s %s \n" , face->family_name , face->style_name);
    printf("yMax %li \n" , face->bbox.yMax);
    
}

int main(int argc, const char * argv[])
{
    FontManager manager;
    
    FT_Face f1 = manager.contains("SourceSansPro-Black.ttf");
    if(!f1)
    {
        std::cout << "Face not found " << std::endl;
    }
    else
    {
        printFaceInfo(f1);
    }
    FT_Face f2 = manager.contains("SourceSansPro-ExtraLight.ttf");
    if(!f2)
    {
        std::cout << "Face not found " << std::endl;
    }
    else
    {
        printFaceInfo(f2);
    }
    return 0;
}
