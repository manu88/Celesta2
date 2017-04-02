//
//  GXText.cpp
//  Celesta
//
//  Created by Manuel Deneu on 02/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "GXText.hpp"
#include "GXFont.hpp"
#include "GXPath.hpp"

GXText::GXText():
CLElement("GXText"),
_font(nullptr),
_textPath(nullptr)
{
    _font = GXFont::loadFont("SourceSansPro-Black.ttf");
    
    DEBUG_ASSERT(_font);
    
    registerSelector("setText", [&](const GB::Variant &text)
                     {
                         setText(text.toString());
                         return GB::Variant::null();
                     });
    
    registerSelector("getText", [&](const GB::Variant &text)
                     {
                         return getText();
                     });

}
GXText::~GXText()
{
    
}

void GXText::setText(const std::string &text) noexcept
{
    _text = text;
}

void GXText::paint(const GXRect &rect)
{
    printf("Paint GXText\n");
    if( _textPath)
    {
        _textPath->setFillColor( _textColor );
        _textPath->setStrokeColor( _textColor );
        _textPath->fill();
        _textPath->stroke();
    }
    GXElement::paint(rect);
}

void GXText::prepare()
{
    
}

