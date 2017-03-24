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


class CLApplicationDelegate;

class CLApplication
{
public:
    
    CLApplication( const std::string &identifier );
    ~CLApplication();
    
    void setDelegate( CLApplicationDelegate *delegate);
    
    bool start() noexcept;
    bool stop() noexcept;
    
    RunLoop& getRunLoop() noexcept
    {
        return _runLoop;
    }
    
    Variant getValueForKey( const std::string &key) const noexcept;
    
private:
    const std::string &_identifier;
    RunLoop _runLoop;
    Dictionary _datas;
    CLApplicationDelegate *_delegate;
};

#endif /* CLApplication_hpp */
