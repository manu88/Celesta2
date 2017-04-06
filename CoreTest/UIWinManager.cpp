//
//  UIWinManager.cpp
//  Celesta
//
//  Created by Manuel Deneu on 04/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "UIWinManager.hpp"
#include "UIView.hpp"
#include "UIMenuBar.hpp"
UIWinManager::UIWinManager() : CLElement("UIWinManager"),_menuBar(nullptr), _activeView(nullptr)
{
    registerSelector("setFocus", [this](const GB::Variant &v)
    {
        const std::string& viewId = v.toString();
        
        for (GXElement* el : getChildren())
        {
            if( el->getIdentifier() == viewId)
            {
                UIView* view = dynamic_cast<UIView*>(el);
                changeFocusedView(view);
                break;
            }
        }
        
        return GB::Variant::null();
    });
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
            GXTouch t = touches;
            t.center = touches.center - el->getBounds().origin;
            if(view->touchesBegan(t))
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
            GXTouch t = touches;
            t.center = touches.center - el->getBounds().origin;
            if(view->touchesEnded(t))
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
    view->viewDidLoad();
    
    view->setZPos(maxZ +1);
    if( addChild(view))
    {
        changeFocusedView(view);
        view->setNeedsDisplay();
        return true;
    }
    return false;
}
void UIWinManager::changeFocusedView( UIView *view)
{
   if( !view)
       return ;
    
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
    
    _menuBar->setAppTitle( view->getWindowTitle() );
    _activeView = view;
}


void UIWinManager::removeWindow(UIView* view)
{
    if( view == nullptr)
        return;
    
    if( contains(view))
    {
        if( removeChild(view))
        {
            view->viewDidUnload();
        }
    }
    else
    {
        printf("Does not contains view \n");
    }
}
void UIWinManager::removeAllWindows()
{
    for(auto el : getChildren())
    {
        UIView* view = dynamic_cast<UIView*>(el);
        if( view)
        {
            removeWindow(view);
        }
    }
}
