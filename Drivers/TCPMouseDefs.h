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
    TypeError = 0,
    TypeMouse = 1,
    TypeKey   = 2
} TCPEventType;

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

typedef struct
{
    int32_t keyCode;
} TCPKeyMsg;



typedef struct
{
    uint16_t code;
    uint16_t size;
    
}TCPEventHeader;

typedef struct
{
    TCPEventHeader header;
    uint8_t  data[64];
    
}TCPEventMsg;

#endif /* TCPMouseDefs_h */
