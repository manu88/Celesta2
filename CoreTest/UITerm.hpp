//
//  UITerm.hpp
//  Celesta
//
//  Created by Manuel Deneu on 04/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef UITerm_hpp
#define UITerm_hpp

#include <string>
#include "UIView.hpp"

class GXText;

class UITerm : public UIView 
{
public:
    UITerm();
    ~UITerm();
    
private:
    void paintContent( const GXRect &rect) override;
    
    bool keyPressed( const GXKey &key ) override;
    
    GXText* _text;
    
    std::string _currentCmd;
    
};

#endif /* UITerm_hpp */
