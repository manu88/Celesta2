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
#include "UITouch.hpp"

class GXText;
class UIView : public GXElement , public UITouchDelegate ,public UIKeyDelegate
{
public:
    UIView( );
    ~UIView();
    
    void setWindowTitle( const std::string &title) noexcept;
    const std::string& getWindowTitle() const noexcept;
    
    bool touchesBegan( const GXTouch &touches ) override;
    bool touchesMoved( const GXTouch &touches ) override;
    bool touchesEnded( const GXTouch &touches ) override;
    
    //bool keyPressed( const GXKey &key ) override;
    
    
protected:
    
    virtual void paintContent( const GXRect &rect);
    
private:
    void paint(const GXRect &rect) override final ;
    GXText* _winTitle;
    
    bool _hoveringQuit;
    bool _hoveringMaximize;
};

#endif /* UIView_hpp */
