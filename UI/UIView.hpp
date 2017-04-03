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
    UIView( );
    ~UIView();
    
    void setWindowTitle( const std::string &title) noexcept;
    const std::string& getWindowTitle() const noexcept;
    
protected:
    void paint(const GXRect &rect) override;
    
private:
    GXText* _winTitle;
};

#endif /* UIView_hpp */
