//
//  UIView.cpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UIView.hpp"


UIView::UIView():
CLElement("UIView")
{
    setBackgroundColor(makeColor(246 ,246, 246));
    
}

UIView::~UIView()
{
    
}
