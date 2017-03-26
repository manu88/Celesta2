//
//  Element.hpp
//  Celesta
//
//  Created by Manuel Deneu on 24/03/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CLElement_hpp
#define CLElement_hpp

#include <string>
#include <map>
#include <functional>
#include <GBVariant.hpp>



class CLElement
{
    
public:
    typedef std::string Selector;
    typedef std::function<const GB::Variant(const GB::Variant &)> Callable;
    
    virtual ~CLElement();
    
    const std::string &getClassName() const noexcept;
    const GB::Variant perform( const Selector & , const GB::Variant &args = GB::Variant::null());
    bool respondsTo( const Selector &) const;
protected:
    CLElement( const std::string &className );
    
    
    bool registerSelector( const Selector &name , Callable func);
private:
    const std::string _className;
    std::map<const Selector , Callable> _selectors;
};

#endif /* CLElement_hpp */
