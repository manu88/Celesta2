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
    
private:

    GB::RunLoop _runLoop;
    GB::Dictionary _datas;
    CLApplicationDelegate *_delegate;
};

#endif /* CLApplication_hpp */
