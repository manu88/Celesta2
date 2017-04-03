//
//  UICursor.hpp
//  Celesta
//
//  Created by Manuel Deneu on 03/04/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef UICursor_hpp
#define UICursor_hpp

#include "GXElement.hpp"
class UICursor : public GXElement
{
public:
    UICursor();
    ~UICursor();
    
private:
    void paint(const GXRect &rect) override;
};

#endif /* UICursor_hpp */
