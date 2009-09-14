/**
 *    Copyright 2009-08-25 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
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
      //std::vector<make_rule> _rules;
      make_rule _rule;

      imp( const vm::type_string & obj = vm::type_string() )
	: _usage( 0 )
	, _object( obj )
	, _rule()
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
