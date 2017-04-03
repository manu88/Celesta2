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
    
    const GXFont* getFont() const noexcept
    {
        return _font;
    }
    void setFont(const GXFont *) noexcept;
    
    void setTextSize( float size) noexcept;
    float getTextSize() const noexcept
    {
        return _size;
    }
    
    void setTextColor(const GXColor &) noexcept;
    
    const GXColor &getTextColor() const noexcept
    {
        return _textColor;
    }
    void paint(const GXRect &rect) override ;
    
    
    
    
private:
    
    void prepare();
    void drawCharAtPositionWithSize( const GXGlyph *glyph , const GXPoint &pos , float size );
    
    std::string _text;
    GXColor     _textColor;
    const GXFont*     _font;
    GXPath*     _textPath;
    
    float _size;
    int _textLengthInPix;
};

#endif /* GXText_hpp */
