/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#ifndef __SMART_BUILTIN_TARGET_IMP__HPP____by_Duzy_Chan__
#define __SMART_BUILTIN_TARGET_IMP__HPP____by_Duzy_Chan__ 1

namespace smart
{
  namespace builtin
  {

    struct target::imp
    {
      long _usage;
      vm::type_string _object;
      std::vector<make_rule*> _rules;

      imp( const vm::type_string & obj = vm::type_string() )
	: _usage( 0 )
	, _object( obj )
      {
      }

      static inline void inref( imp * p )
      {
	++p->_usage;
      }

      static inline void deref( imp * & p )
      {
	if ( 0 == --p->_usage ) {
	  delete p;
	  p = 0;
	}
      }
    };//struct target::imp

  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN_TARGET_IMP__HPP____by_Duzy_Chan__
