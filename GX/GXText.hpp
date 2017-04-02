//
//  GXText.hpp
//  Celesta
//
//  Created by Manuel Deneu on 02/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef GXText_hpp
#define GXText_hpp

#include "GXElement.hpp"
#include "GXColors.hpp"

class GXFont;
class GXPath;
class GXGlyph;

class GXText : public GXElement
{
public:
    GXText();
    ~GXText();
    
    void setText(const std::string &) noexcept;
    const std::string& getText() const noexcept
    {
        return _text;
    }
    
    void paint(const GXRect &rect) override ;
    
    
    enum { FUCKING_SCALE_CONV_ = 8};
    
private:
    
    void prepare();
    void drawCharAtPositionWithSize( const GXGlyph *glyph , const GXPoint &pos , float size );
    
    std::string _text;
    GXColor     _textColor;
    const GXFont*     _font;
    GXPath*     _textPath;
    
    float _size;
    float _sizeCoef;
    int _textLengthInPix;
};

#endif /* GXText_hpp */