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
#include "GXColors.hpp"

class GXElement : public virtual CLElement
{
public:
    friend class GXRenderer;
    
    typedef std::vector<GXElement*> GXChildList;
    
    virtual ~GXElement();
    
    /* Geometry */
    void setBounds( const GXRect & );
    const GXRect& getBounds() const;
    
    void setSize( const GXSize &size);
    
    void moveTo( const GXPoint & );
    void moveOf( int dX , int dY);
    void moveTo( int x  , int y);
    
    void setVisible( bool);
    bool isVisible() const noexcept
    {
        return _visible;
    }
    
    // 1 atop 0
    void setZPos( int );
    int  getZPos() const;
    
    /**/
    void setBackgroundColor(const GXColor &);
    
    const GXColor & getBackgroundColor() const
    {
        return _backgroundColor;
    }
    /* Updates */
    void setNeedsDisplay( const GXRect &  );
    void setNeedsDisplay();
    
    /* Hierarchy */
    
    const GXElement* getParent() const noexcept
    {
        return _parent;
    }
    
    /*
      Children are stored from ZPos+ to ZPos-.
     */
    const GXChildList &getChildren() const noexcept
    {
        return _children;
    }
    /* return true if the element is succesfully added (also true if the element has already in the children*/
    bool addChild( GXElement* );
    bool removeChild(GXElement *);
    
    bool contains(GXElement*) const;
    
    void printInfos( std::ostream &stream) const;
    
    GB::Variant serialize() const override ;
protected:
    GXElement(); // Public is temp. for tests
    
    virtual void needsDisplay();
    virtual void needsReorder();
    virtual void paint(const GXRect &rect); // should go pure virtual
    //GXElement();
    
private:
    void initSelectors();
    
    void sortChildren();
    
    bool _visible;
    GXRect _bounds;
    int    _zOrder; // 1 atop 0
    
    GXColor _backgroundColor;

    GXElement*  _parent;
    GXChildList _children;
    
    /**/
    bool   _needsUpdate;
    GXRect _updateRect;
    
};

#endif /* GXElement_hpp */
