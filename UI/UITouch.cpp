//
//  UITouch.cpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UITouch.hpp"


bool UITouchDelegate::touchesBegan( const GXTouch &touches )
{
    return false;
}
bool UITouchDelegate::touchesMoved( const GXTouch &touches )
{
    return false;
}

bool UITouchDelegate::touchesEnded( const GXTouch &touches )
{
    return false;
}


bool UIKeyDelegate::keyPressed( const GXKey &key )
{
    return false;
}
