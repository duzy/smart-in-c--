/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ĞÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ĞÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "builtin_target.hpp"
#include "builtin_target_imp.hpp"

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
    
    vm::type_string target::object() const
    {
      return _i->_object;
    }
    
  }//namespace builtin
}//namespace smart
