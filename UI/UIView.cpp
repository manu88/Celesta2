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
    setBackgroundColor(makeColor(150 ,150, 150));
    
    
    _winTitle = new GXText();
    _winTitle->setFont(GXFont::loadFont("SourceSansPro-ExtraLight.ttf"));
    
    _winTitle->setText("Hello");
    _winTitle->setTextSize(10);
    
    addChild(_winTitle);

    
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
    
    path.addEllipse(makeRect( makePoint(10, rect.size.height - 15), makeSize(10, 10) ) );
    path.setFillColor( makeColor(255, 93, 90) );
    path.fill();
    
    path.clear();
    path.addEllipse(makeRect( makePoint(30, rect.size.height - 15), makeSize(10, 10) ) );
    path.setFillColor( makeColor(255, 192, 78) );
    path.fill();
    
    path.clear();
    path.addEllipse(makeRect( makePoint(50, rect.size.height - 15), makeSize(10, 10) ) );
    path.setFillColor( makeColor(000, 207, 89) );
    path.fill();
    
    _winTitle->setBounds(makeRect(makePoint(80, rect.size.height - 15), makeSizeNULL()));
    _winTitle->setNeedsDisplay(rect);
    // red rgb(255, 093, 090)
    // yellow rgb(255, 192, 078)
    // green rgb(000, 207, 089)
    //path.clear();
    
    
    
    GXElement::paint(rect);
}
