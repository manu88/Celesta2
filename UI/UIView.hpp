//
//  UIView.hpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef UIView_hpp
#define UIView_hpp

#include "GXElement.hpp"

class GXText;
class UIView : public GXElement
{
public:
    UIView();
    ~UIView();
    
protected:
    void paint(const GXRect &rect);
    
private:
    GXText* _winTitle;
};

#endif /* UIView_hpp */
