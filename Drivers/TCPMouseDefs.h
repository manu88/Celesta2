//
//  TCPMouseDefs.h
//  Celesta
//
//  Created by Manuel Deneu on 02/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef TCPMouseDefs_h
#define TCPMouseDefs_h


typedef enum
{
    NoEvent  = 0,
    Pressed  = 1,
    Moved    = 2,
    Released = 3

} MouseEvent;

typedef struct
{
    int32_t x;
    int32_t y;
    int32_t button;
    int32_t event;
    
} TCPMouseMsg;

#endif /* TCPMouseDefs_h */
