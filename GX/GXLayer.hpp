//
//  GXLayout.hpp
//  Celesta
//
//  Created by Manuel Deneu on 29/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef GXLayer_hpp
#define GXLayer_hpp

#include "GXElement.hpp"

class GXLayer : public GXElement
{
public:
    GXLayer();
    ~GXLayer();
private:
    
    void paint(const GXRect &rect) override ;
};

#endif /* GXLayer */
