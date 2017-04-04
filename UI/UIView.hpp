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

namespace GB { class RunLoop; }

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
    
    void setRunLoop( GB::RunLoop* runloop)
    {
        _runLoop = runloop;
    }
    
protected:
    
    GB::RunLoop* getRunLoop() const
    {
        return _runLoop;
    }
    
    virtual void paintContent( const GXRect &rect);
    
private:
    
    GB::RunLoop *_runLoop;
    
    void paint(const GXRect &rect) override final ;
    GXText* _winTitle;
    
    bool _hoveringQuit;
    bool _hoveringMaximize;
};

#endif /* UIView_hpp */
