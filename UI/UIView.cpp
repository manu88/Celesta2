//
//  UIView.cpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UIView.hpp"
#include "GXPath.hpp"
#include "GXText.hpp"
#include "GXFont.hpp"
UIView::UIView():
CLElement("UIView")
{
    _hoveringQuit = false;
    setBackgroundColor(makeColor(150 ,150, 150));

    _winTitle = new GXText();
    _winTitle->setFont(GXFont::loadFont("SourceSansPro-ExtraLight.ttf"));
    
    _winTitle->setText("Hello");
    _winTitle->setTextSize(14);
    _winTitle->setTextColor(makeColor(0, 0, 0));
    addChild(_winTitle);
    

    registerSelector("setWindowTitle", _winTitle->getSelectors().at("setText"));
    registerSelector("getWindowTitle", _winTitle->getSelectors().at("getText"));
    
}

void UIView::setWindowTitle( const std::string &title) noexcept
{
    _winTitle->setText(title);
}

const std::string& UIView::getWindowTitle() const noexcept
{
    return _winTitle->getText();
}

UIView::~UIView()
{
    delete _winTitle;
}

void UIView::paint(const GXRect &rect)
{
    GXPath path( rect);
    path.addRoundedRect(makeRect(makePointNULL(), rect.size), 10.f, 10.f);
    path.setFillColor( getBackgroundColor() );
    path.fill();
    //path.clear();
    
    path.addRoundedRect(makeRect(makePoint(2, 2), makeSize(rect.size.width-4, rect.size.height - 20)), 5.f, 5.f);
    path.setFillColor( makeColor(190, 190, 190) );
    path.fill();
    
    path.clear();
    
    // close icon
    path.addEllipse(makeRect( makePoint(10, rect.size.height - 15), makeSize(10, 10) ) );
    if(_hoveringQuit)
    {
        path.setFillColor( makeColor(244, 187, 61) );
    }
    else
    {
        path.setFillColor( makeColor(255, 93, 90) );
    }
    path.fill();
    
    // reduce icon
    path.clear();
    path.addEllipse(makeRect( makePoint(30, rect.size.height - 15), makeSize(10, 10) ) );
    path.setFillColor( makeColor(255, 192, 78) );
    path.fill();
    
    // fullscreen icon
    path.clear();
    path.addEllipse(makeRect( makePoint(50, rect.size.height - 15), makeSize(10, 10) ) );
    path.setFillColor( makeColor(000, 207, 89) );
    path.fill();
    
    _winTitle->setBounds(makeRect(makePoint(rect.size.width/2, rect.size.height - 15), makeSizeNULL()));
    
    _winTitle->setNeedsDisplay(rect);
    // red rgb(255, 093, 090)
    // yellow rgb(255, 192, 078)
    // green rgb(000, 207, 089)
    //path.clear();
    
    
    
    GXElement::paint(getBounds());
}

bool UIView::touchesBegan( const GXTouch &touches )
{
    return false;
}

bool UIView::touchesMoved( const GXTouch &touches )
{
    
    if( touches.center.y > getBounds().size.height - 20)
    {
        if(rectContainsPoint(makeRect( makePoint(10, getBounds().size.height - 15), makeSize(10, 10)), touches.center) )
        {
            printf("Hovering Close Icon in UIView %s\n" , getIdentifier().c_str() );
            _hoveringQuit = true;
        }
        else
        {
            printf("Touching touch bar in UIView %s\n" , getIdentifier().c_str() );
        }
        //printf("TouchesMoved in UIView %s\n" , getIdentifier().c_str() );
    }
    else
    {
        _hoveringQuit = false;
    }
    return false;
}

bool UIView::touchesEnded( const GXTouch &touches )
{
    return false;
}

