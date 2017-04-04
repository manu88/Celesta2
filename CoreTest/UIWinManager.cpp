//
//  UIWinManager.cpp
//  Celesta
//
//  Created by Manuel Deneu on 04/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UIWinManager.hpp"


UIWinManager::UIWinManager() : CLElement("UIWinManager")
{
    
}

UIWinManager::~UIWinManager()
{
    
}

bool UIWinManager::touchesBegan( const GXTouch &touches )
{
    for (GXElement* el : getChildren())
    {
        UITouchDelegate* view = dynamic_cast<UITouchDelegate*>(el);
        
        if (view)
        {
            if(view->touchesBegan(touches))
            {
                return true;
            }
        }
    }
    
    return false;
}

bool UIWinManager::touchesMoved( const GXTouch &touches )
{
    for (GXElement* el : getChildren())
    {
        UITouchDelegate* view = dynamic_cast<UITouchDelegate*>(el);
        
        if (view)
        {
            if(view->touchesMoved(touches))
            {
                return true;
            }
        }
    }
    
    return false;
}

bool UIWinManager::touchesEnded( const GXTouch &touches )
{
    for (GXElement* el : getChildren())
    {
        UITouchDelegate* view = dynamic_cast<UITouchDelegate*>(el);
        
        if (view)
        {
            if(view->touchesEnded(touches))
            {
                return true;
            }
        }
    }
    
    return false;
}
