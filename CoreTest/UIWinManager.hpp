//
//  UIWinManager.hpp
//  Celesta
//
//  Created by Manuel Deneu on 04/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef UIWinManager_hpp
#define UIWinManager_hpp

#include "GXElement.hpp"
#include "UITouch.hpp"
class UIView;
class UIMenuBar;

class UIWinManager : public GXElement, public UITouchDelegate ,public UIKeyDelegate
{
public:
    UIWinManager();
    ~UIWinManager();
    
    void changeFocusedView( UIView *view);
    
    bool addWindow( UIView* view);
    
    UIView* getActiveView() const
    {
        return _activeView;
    }
    
    void setMenuBar( UIMenuBar* bar)
    {
        _menuBar = bar;
    }
private:
    
    bool touchesBegan( const GXTouch &touches ) override;
    bool touchesMoved( const GXTouch &touches ) override;
    bool touchesEnded( const GXTouch &touches ) override;
    
    UIMenuBar* _menuBar;
    UIView* _activeView;
};

#endif /* UIWinManager_hpp */
