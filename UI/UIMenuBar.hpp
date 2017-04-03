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
    
private:
    void paint(const GXRect &rect) override;
};

#endif /* UIMenuBar_hpp */
