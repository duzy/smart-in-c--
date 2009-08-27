/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "builtin_target.hpp"
#include "builtin_target_imp.hpp"
#include "builtin_make_rule.hpp"
#include <boost/ref.hpp>
#include <algorithm>

namespace smart
{
  namespace builtin
  {

    void intrusive_ptr_add_ref( target::imp *p )
    {
      target::imp::inref( p );
    }

    void intrusive_ptr_release( target::imp * & p )
    {
      target::imp::deref( p );
    }
    
    target::target()
      : vm::type_ext()
      , _i( new imp )
    {
    }
    
    target::target( const vm::type_string & str )
      : vm::type_ext()
      , _i( new imp(str) )
    {
    }

    long target::refcount() const
    {
      return _i->_usage;
    }
    
    vm::type_string target::object() const
    {
      return _i->_object;
    }

    const std::vector<make_rule> & target::rules() const
    {
      return _i->_rules;
    }

    /**
     *  * Each target binds to one make-rule
     *  * New binding will overrides the previous commands
     *  * New binding combines prerequisites with the previous binding
     */
    void target::bind( const make_rule & r )
    {
      _i->_rules.push_back( r );
    }
    
  }//namespace builtin
}//namespace smart
