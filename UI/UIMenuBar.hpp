//
//  UIMenuBar.hpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef UIMenuBar_hpp
#define UIMenuBar_hpp

#include "GXElement.hpp"
#include "UITouch.hpp"

class GXText;
class UIMenuBar : public GXElement , public UITouchDelegate
{
public:
    UIMenuBar();
    ~UIMenuBar();
    
    void setAppTitle( const std::string &title) noexcept;
    const std::string& getAppTitle() const noexcept;
    
    bool touchesBegan( const GXTouch &touches ) override;
    bool touchesMoved( const GXTouch &touches ) override;
    bool touchesEnded( const GXTouch &touches ) override;
    
private:
    void paint(const GXRect &rect) override;
    
    GXText* _appTitle;
    
    bool _menuEnabled;
};

#endif /* UIMenuBar_hpp */
