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

class AbstractDisplayImpl;
class GXRenderer;

class Display : public virtual CLElement
{
public:
    Display();
    ~Display();
    
    void setRenderer(GXRenderer* );
    
    bool init();
    bool deInit();
    bool update();
    
    bool start();
    bool stop();
    
private:
    
    void startGUI();
    Thread _guiThread;
    AbstractDisplayImpl *_impl;
    
    GXRenderer *_renderer;
};

#endif /* Display_hpp */
