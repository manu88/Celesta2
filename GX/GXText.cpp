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
_textColor(makeColor(255, 255, 255)),
_font(nullptr),
_textPath(nullptr)
{
    _sizeCoef = 1.0f/3000.f; // ?
    _size  = 10.f;
    _textLengthInPix = -1;
    
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
    
    prepare();
    setNeedsDisplay();
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
    DEBUG_ASSERT(_font);
    
    if ( _textPath == nullptr)
        _textPath = new GXPath( makeRectNULL() );
    
    DEBUG_ASSERT(_textPath);
    
    _textPath->clear();
 
    const float realSize = static_cast<float>( _size* _sizeCoef );
    
    /**/
    const int lineJump =  static_cast<int>(_font->getLineSpace()* FUCKING_SCALE_CONV_ * realSize  );
    
    _textPath->setStrokeColor( _textColor );
    _textPath->setFillColor  ( _textColor );
    
    const GXPoint carret = makePoint(0,/* getBounds().origin.x, getBounds().origin.y*/
                                     100 - lineJump
                                     );
    
    GXPoint pt  = carret;
    GXSize size = makeSizeNULL();
    
    size.height = lineJump;
    
    int tempWidth = 0;
    
    
    
    for (unsigned i=0; i<_text.length(); ++i)
    {
        const char c =_text.at(i);
        
        if ( c == '\n')
        {
            printf("Draw Line jump\n");
            pt.x = carret.x;
            pt.y -= lineJump;
            size.height += lineJump;
            
            if( tempWidth > size.width )
            {
                size.width = tempWidth;
                tempWidth = 0;
            }
        }
        
        else
        {
            printf("Draw %c at %i %i \n" , c , pt.x , pt.y);
            const GXGlyph *glyph =  _font->getCharacter( c );
            
            drawCharAtPositionWithSize( glyph, pt , realSize );
            
            pt.x += (int ) glyph->getAdvanceX() * realSize;
            tempWidth += (int ) glyph->getAdvanceX() * realSize;
            
        }
    }
    
    _textLengthInPix = pt.x - carret.x;
    
    // last line
    if( tempWidth > size.width )
        size.width = tempWidth;
    
    setSize(makeSize( size.width, size.height) );
    printf("GXTExt bounds %i %i %i %i\n" , getBounds().origin.x , getBounds().origin.y , getBounds().size.width ,getBounds().size.height);
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

void GXText::drawCharAtPositionWithSize( const GXGlyph *glyph , const GXPoint &pos , float size )
{
    
    std::function<int(const float&)> ceilAndCast = [] ( const float &val) ->int
    {
        return static_cast<int>( ceilf( val) );
    };

    
    printf("\t Glyph num segs %zi size %f \n", glyph->getNumSegments() , size);
    
    for ( size_t i = 0 ; i < glyph->getNumSegments() ; i++)
    {
        const Curve_float *c = glyph->getCurveAt( i );
        
        if ( c->getCurveType() == CurveMoveTo )
        {
            const GXPoint p =  makePoint( ceilAndCast( c->getPointAt(0).getX() * size ),
                                         ceilAndCast( c->getPointAt(0).getY() * size )
                                         );
            
            _textPath->moveToPoint( pos + p );
        }
        
        else if ( c->getCurveType() == CurveLineTo )
        {
            const GXPoint p =  makePoint( ceilAndCast( c->getPointAt(0).getX() * size ),
                                         ceilAndCast( c->getPointAt(0).getY() * size )
                                         );
            _textPath->addLineToPoint( pos + p );
        }
        else if ( c->getCurveType() == CurveCubicTo )
        {
            const GXPoint p0 =  makePoint( ceilAndCast( c->getPointAt(0).getX() * size ),
                                          ceilAndCast( c->getPointAt(0).getY() * size )
                                          );
            
            const GXPoint c0 =  makePoint( ceilAndCast( c->getPointAt(1).getX() * size ),
                                          ceilAndCast( c->getPointAt(1).getY() * size )
                                          );
            
            const GXPoint p1 =  makePoint( ceilAndCast( c->getPointAt(2).getX() * size ),
                                          ceilAndCast( c->getPointAt(2).getY() * size )
                                          );
            
            _textPath->addCubicCurveToPoint( pos +   p0, pos +   c0, pos +   p1 );
        }
        
        else if ( c->getCurveType() == CurveQuadTo )
        {
            const GXPoint c0 =  makePoint( ceilAndCast( c->getPointAt(0).getX() * size ),
                                          ceilAndCast( c->getPointAt(0).getY() * size )
                                          );
            const GXPoint p0 =  makePoint( ceilAndCast( c->getPointAt(1).getX() * size ),
                                          ceilAndCast( c->getPointAt(1).getY() * size )
                                          );
            
            _textPath->addQuadCurveToPoint( pos + c0 , pos +p0 );
        }
        else
            DEBUG_ASSERT( false );
        
    }
    
}

