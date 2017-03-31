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

namespace GB
{
    class RunLoop;
    class SequenceType;
}
class CLElement
{

public:
    typedef std::string Selector;
    typedef std::function<const GB::Variant(const GB::Variant &)> CallableFunction;
    
    virtual ~CLElement();
    
    const std::string &getClassName() const noexcept;
    
    const GB::Variant perform( const Selector & , const GB::Variant &args = GB::Variant::null());
    bool respondsTo( const Selector &) const;
    const std::map<const Selector , CallableFunction>& getSelectors() const;
    
    static const GB::Variant performAsync( const GB::RunLoop&, CLElement* , const Selector & , const GB::Variant &args = GB::Variant::null());
    bool registerSelector( const Selector &name , CallableFunction func);
    
    const std::string &getIdentifier() const noexcept
    {
        return _identifier;
    }
    
    void setIdentifier( const std::string &id) noexcept;
    virtual GB::Variant serialize() const ;
protected:
    CLElement( const std::string &className );
    
    
    
    //virtual GB::Coder& operator<<( GB::Coder& coder);
    
    
private:
    const std::string _className;
    std::map<const Selector , CallableFunction> _selectors;
    std::string _identifier;
};




#endif /* CLElement_hpp */
