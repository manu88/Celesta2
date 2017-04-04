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
class CLApplication;



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
    
    void setApplication( CLApplication *app)
    {
        _application = app;
    }
    
protected:
    
    CLApplication* getApplication() const
    {
        return _application;
    }
    
    virtual void paintContent( const GXRect &rect);
    
private:
    
    CLApplication *_application;
    
    void paint(const GXRect &rect) override final ;
    GXText* _winTitle;
    
    bool _hoveringQuit;
    bool _hoveringMaximize;
};

#endif /* UIView_hpp */
