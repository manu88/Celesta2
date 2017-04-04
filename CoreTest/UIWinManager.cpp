//
//  UIWinManager.cpp
//  Celesta
//
//  Created by Manuel Deneu on 04/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UIWinManager.hpp"
#include "UIView.hpp"

UIWinManager::UIWinManager() : CLElement("UIWinManager"), _activeView(nullptr)
{
    
}

UIWinManager::~UIWinManager()
{
    
}

bool UIWinManager::touchesBegan( const GXTouch &touches )
{
    for(GXElement* el : getChildren())
    {
        UIView* view = dynamic_cast<UIView*>(el);
        if(view && rectContainsPoint(el->getBounds(), touches.center))
        {

            changeFocusedView(view);
            break;
        }
        
    }
    
    for (GXElement* el : getChildren())
    {
        UITouchDelegate* view = dynamic_cast<UITouchDelegate*>(el);
        
        
        
        if (view && rectContainsPoint(el->getBounds(), touches.center))
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
        
        if (view && rectContainsPoint(el->getBounds(), touches.center))
        {
            GXTouch t = touches;
            
            t.center = touches.center - el->getBounds().origin;
            if(view->touchesMoved(t))
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
        
        if (view && rectContainsPoint(el->getBounds(), touches.center))
        {
            if(view->touchesEnded(touches))
            {
                return true;
            }
        }
    }
    
    return false;
}


bool UIWinManager::addWindow( UIView* view)
{
    if( !view)
        return false;
    int maxZ = -1;
    for(const GXElement* el : getChildren())
    {
        if( el->getZPos() > maxZ )
        {
            maxZ = el->getZPos();
        }
    }
    
    view->setZPos(maxZ +1);
    return addChild(view);
}
void UIWinManager::changeFocusedView( UIView *view)
{
    printf("Find intersection with %s %s\n" , view->getIdentifier().c_str() , view->getClassName().c_str());
    
    int focus =(int) getChildren().size();
    view->setFocus(true);
    view->setZPos(focus--);
    for(GXElement* el : getChildren())
    {
        UIView* v = dynamic_cast<UIView*>(el);
        if( v != view)
        {
            v->setFocus(false);
            v->setZPos(focus--);
        }
    }
    /*
    for(const GXElement* el : getChildren())
    {
        printf("ZPos %i : %s %s \n" , el->getZPos() , el->getIdentifier().c_str() , el->getClassName().c_str());
    }
    */
    _activeView = view;
}
