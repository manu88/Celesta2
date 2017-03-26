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

namespace GB
{
    class VariantList;
    class Variant;
}
class CLElement
{
    
public:
    typedef std::string Selector;
    typedef std::function<const GB::Variant(const GB::VariantList &)> Callable;
    
    virtual ~CLElement();
    
    const std::string &getClassName() const noexcept;
    virtual const GB::Variant perform( const Selector & , const GB::VariantList &args);
protected:
    CLElement( const std::string &className );
    
    const GB::Variant test(const GB::VariantList &args);
    
    bool registerSelector( const Selector &name , Callable func);
private:
    const std::string _className;
    std::map<const Selector , Callable> _selectors;
};

#endif /* CLElement_hpp */
