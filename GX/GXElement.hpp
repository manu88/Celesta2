//
//  GXElement.hpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef GXElement_hpp
#define GXElement_hpp

#include "../Core/CLElement.hpp"
#include "GXGeometry.hpp"

class GXElement : public virtual CLElement
{
public:
    virtual ~GXElement();
    
    void setBounds( const GXRect & );
    const GXRect& getBounds() const;
    
    void setSize( const GXSize &size);
protected:
    GXElement();
    
private:
    GXRect _bounds;
};

#endif /* GXElement_hpp */
