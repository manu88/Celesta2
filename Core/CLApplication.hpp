//
//  CLApplication.hpp
//  Celesta
//
//  Created by Manuel Deneu on 22/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CLApplication_hpp
#define CLApplication_hpp

#include <GroundBase.hpp>
#include <list>
#include "CLElement.hpp"
class CLApplicationDelegate;

class CLApplication : public CLElement
{
public:
    
    CLApplication( const std::string &identifier );
    ~CLApplication();
    
    void setDelegate( CLApplicationDelegate *delegate);
    
    bool start() noexcept;
    bool stop() noexcept;
    
    GB::RunLoop& getRunLoop() noexcept
    {
        return _runLoop;
    }
    
    GB::Variant getValueForKey( const std::string &key) const noexcept;
    
    void addElement( CLElement*);
    CLElement* getElement( const std::string &identifier) const;
    
    const std::list<CLElement*> getElements() const noexcept
    {
        return _elements;
    }
    
private:

    GB::RunLoop _runLoop;
    GB::Dictionary _datas;
    CLApplicationDelegate *_delegate;
    
    std::list<CLElement*> _elements;
};

#endif /* CLApplication_hpp */
