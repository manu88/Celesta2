//
//  UITouch.hpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef UITouch_hpp
#define UITouch_hpp


#include "GXGeometry.hpp"

typedef struct
{
    GXPoint center;
    int     id;
    int     touchState;
} GXTouch;

class UITouchDelegate
{
public:
    virtual ~UITouchDelegate()
    {}
    
    virtual bool touchesBegan( const GXTouch &touches );
    virtual bool touchesMoved( const GXTouch &touches );
    virtual bool touchesEnded( const GXTouch &touches );
};

#endif /* UITouch_hpp */
