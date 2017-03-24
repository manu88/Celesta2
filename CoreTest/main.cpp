//
//  main.cpp
//  Celesta
//
//  Created by Manuel Deneu on 22/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>

#include "CLApplication.hpp"
#include "CLApplicationDelegate.hpp"
#include <GBTimer.hpp>

class MyAppDelegate  : public CLApplicationDelegate
{
    void willStart()
    {
        std::cout << "App will Start" << std::endl;
    }
    
    void didStart()
    {
        std::cout << "App did Start" << std::endl;
        
        getApp()->getRunLoop().dispatchAsync([&]
        {
            getApp()->getRunLoop().dispatchAsync([&]
            {
                _timer.setInterval(1000);
                _timer.setCallback([&](Timer &timer)
                {
                    static int count = 0;
                    std::cout << "on time" << std::endl;
                    
                    if( count++ > 15)
                    {
                        getApp()->stop();
                    }
                    
                });
                
                getApp()->getRunLoop().addSource( _timer );
                
            });
        });
        
    }
    
    void willStop()
    {
        std::cout << "App will end " << std::endl;
    }
    
    void didStop()
    {
        std::cout << "App did end " << std::endl;
    }
    
private:
    Timer _timer;
    
};
int main(int argc, const char * argv[])
{

    CLApplication app("com.myApp");
    MyAppDelegate delegate;
    
    app.setDelegate(&delegate);
    
    
    
    app.start();
     
    std::cout << "App returned " << std::endl;
    return 0;
}
