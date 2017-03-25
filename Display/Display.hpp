//
//  Display.hpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef Display_hpp
#define Display_hpp

#include <GBThread.hpp>
#include "../Core/CLElement.hpp"
#include "../GX/GXRenderer.hpp"

class AbstractDisplayImpl;


class Display : public GXRenderer
{
public:
    Display();
    ~Display();
    
    bool init();
    bool deInit();
    bool update();
    
    bool start();
    bool stop();
    
private:
    
    void needsDisplay() override final ;
    
    void startGUI();
    Thread _guiThread;
    AbstractDisplayImpl *_impl;
    

};

#endif /* Display_hpp */
