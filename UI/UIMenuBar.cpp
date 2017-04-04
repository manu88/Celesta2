//
//  UIMenuBar.cpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UIMenuBar.hpp"
#include "GXPath.hpp"
#include "GXText.hpp"
#include "GXFont.hpp"
#include "GXLayer.hpp"
#include "CLApplication.hpp"

static const GXColor bColor = makeColor(150 ,150, 150);

UIMenuBar::UIMenuBar():CLElement("UIMenuBar") , _app(nullptr)
{
    _menuEnabled = false;
    setBackgroundColor( bColor );
    
    _appTitle = new GXText();
    
    _appTitle->setFont(GXFont::loadFont("LucidaGrandeRegular.ttf"));
    
    _appTitle->setTextSize(20);
    _appTitle->setTextColor(makeColor(0, 0, 0));
    addChild(_appTitle);
    
    
    registerSelector("setAppTitle", _appTitle->getSelectors().at("setText"));
    registerSelector("getAppTitle", _appTitle->getSelectors().at("getText"));
    
    menu = new GXLayer();
    menu->setTransparent(false);
    menu->setBackgroundColor( bColor );
    menu->setBounds(makeRect(40 , -400 , 100 , 400));
    
    
    
    
}

UIMenuBar::~UIMenuBar()
{
    delete menu;
}

void UIMenuBar::paint(const GXRect &rect)
{
    GXPath path( rect);
    path.addRect(makeRect(makePointNULL(), rect.size));
    path.setFillColor( getBackgroundColor() );
    path.fill();
    
    
    const GXRect menuB = makeRect(makePoint(30, rect.size.height - 25), makeSizeNULL());
    
    if( _menuEnabled)
    {
        
        path.clear();
        path.addRect(makeRect(30, 0, _appTitle->getBounds().size.width+10, rect.size.height));
        path.setFillColor(makeColor(51, 57, 246));
        path.fill();
        _appTitle->setTextColor(makeColor(255, 255, 255));
        
        
    }
    else
    {
        _appTitle->setTextColor(makeColor(0, 0, 0));
    }
    
    _appTitle->setBounds(menuB);
    
    
    GXElement::paint(getBounds());
}

bool UIMenuBar::touchesBegan( const GXTouch &touches )
{
    
    if( rectContainsPoint(_appTitle->getBounds(), touches.center))
    {
        if( !_menuEnabled )
        {
            _menuEnabled = true;
            printf("Enable Menu\n");
            
            menu->setVisible(true);
            
            if( menu->getParent() != this)
            {
                addChild(menu);
            }
            
            
        }
    }
    
    return false;
}

bool UIMenuBar::touchesMoved( const GXTouch &touches )
{
    if( rectContainsPoint(_appTitle->getBounds(), touches.center))
    {

    }
    else if( _menuEnabled)
    {
        _menuEnabled = false;
        
        printf("Disable Menu\n");
        removeChild(menu);
        
        
        
    }
    
    return false;
}

bool UIMenuBar::touchesEnded( const GXTouch &touches )
{
    if( rectContainsPoint(_appTitle->getBounds(), touches.center))
    {
        _menuEnabled = false;
        printf("Disable Menu\n");
    }
    return false;
}

void UIMenuBar::setAppTitle( const std::string &title) noexcept
{
    _appTitle->setText(title);
}
const std::string& UIMenuBar::getAppTitle() const noexcept
{
    return _appTitle->getText();
}
