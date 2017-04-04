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
#include <GBTimer.hpp>
#include "UIView.hpp"

class GXText;

class UITerm : public UIView 
{
public:
    UITerm(CLApplication *app);
    ~UITerm();
    
private:
    void focusChanged() override;
    void paintContent( const GXRect &rect) override;
    
    bool keyPressed( const GXKey &key ) override;
    
    
    void onTime(GB::Timer &timer);
    GB::Timer _timer;
    GXText* _text;
    
    bool _drawCarret;
    std::string _currentCmd;
    
};

#endif /* UITerm_hpp */
