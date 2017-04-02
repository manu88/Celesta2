//
//  CLApplicationDelegate.hpp
//  Celesta
//
//  Created by Manuel Deneu on 22/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CLApplicationDelegate_hpp
#define CLApplicationDelegate_hpp

class CLApplication;

class CLApplicationDelegate
{
    friend class CLApplication;
public:
    virtual ~CLApplicationDelegate();
    
protected:
    CLApplicationDelegate();
    
    virtual void willStart();
    virtual void didStart();
    
    virtual void willStop();
    virtual void didStop();
    
    CLApplication* getApp() const ;
    
private:
    CLApplication* _app;
};

#endif /* CLApplicationDelegate_hpp */
