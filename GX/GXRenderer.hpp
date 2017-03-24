//
//  GXRenderer.hpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef GXRenderer_hpp
#define GXRenderer_hpp

#include "../Core/CLElement.hpp"
#include "GXElement.hpp"

class GXRenderer : public GXElement
{
    
public:
    GXRenderer();
    ~GXRenderer();
    
    bool setDisplayedElement(GXElement*);
    
    bool update();
    
    GXElement* getRootElement() const
    {
        return _rootElement;
    }
    
private:
    GXElement* _rootElement;
};

#endif /* GXRenderer_hpp */
