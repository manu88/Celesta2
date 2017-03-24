//
//  GXElement.hpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef GXElement_hpp
#define GXElement_hpp

#include <iostream>
#include <vector>
#include "GXGeometry.hpp"
#include "../Core/CLElement.hpp"

class GXElement : public virtual CLElement
{
public:
    friend class GXRenderer;
    
    typedef std::vector<GXElement*> GXChildList;
    GXElement(); // Public is temp. for tests
    virtual ~GXElement();
    
    /* Geometry */
    void setBounds( const GXRect & );
    const GXRect& getBounds() const;
    
    void setSize( const GXSize &size);
    
    // 1 atop 0
    void setZPos( int );
    int  getZPos() const;
    
    /* Hierarchy */
    
    const GXElement* getParent() const noexcept
    {
        return _parent;
    }
    
    const GXChildList &getChildren() const noexcept
    {
        return _children;
    }
    
    bool addChild( GXElement* );
    
    void printInfos( std::ostream &stream) const;
protected:
    
    virtual void paint(const GXRect &rect); // should go pure virtual
    //GXElement();
    
private:
    
    void sortChildren();
    
    GXRect _bounds;
    int    _zOrder; // 1 atop 0
    
    GXElement*  _parent;
    GXChildList _children;
};

#endif /* GXElement_hpp */
