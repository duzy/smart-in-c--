/**
 *    Copyright 2009-08-25 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#ifndef __SMART_BUILTIN_MACRO_IMP__HPP____by_Duzy_Chan__
#define __SMART_BUILTIN_MACRO_IMP__HPP____by_Duzy_Chan__ 1

namespace smart
{
  namespace builtin
  {
    struct macro::imp
    {
      long usage;
      vm::type_string origin;
      vm::type_string flavor;
      vm::type_string name;
      vm::type_string value;

      imp( const vm::type_string & ori, const vm::type_string & fla,
	   const vm::type_string & nam, const vm::type_string & val )
	: usage( 0 )
	, origin( ori )
	, flavor( fla )
	, name( nam )
	, value( val )
      {
      }

      static inline void inref( imp * p )
      {
	++p->usage;
      }

      static inline void deref( imp * & p )
      {
	if ( 0 == --p->usage ) {
	  delete p;
	  p = 0;
	}
      }
    };//struct macro::imp
  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN_MACRO_IMP__HPP____by_Duzy_Chan__
