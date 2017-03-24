//
//  AbstractDisplayImpl.hpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef AbstractDisplayImpl_hpp
#define AbstractDisplayImpl_hpp

class AbstractDisplayImpl
{
public:
    virtual ~AbstractDisplayImpl(){}
    
    virtual bool init() = 0;
    virtual bool deInit() = 0;
    
    virtual bool update() = 0;
    
protected:
    AbstractDisplayImpl(){}
private:
    
};

#endif /* AbstractDisplayImpl_hpp */
