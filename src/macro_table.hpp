/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#ifndef __SMART_MACRO_TABLE__HPP____by_Duzy_Chan__
#define __SMART_MACRO_TABLE__HPP____by_Duzy_Chan__ 1
#	include <boost/unordered/unordered_map.hpp>
#	include "builtin_macro.hpp"

namespace smart
{

  struct macro_table
  {
    macro_table();

    builtin::macro map( const vm::type_string & name );
    builtin::macro get( const vm::type_string & name );

  private:
    typedef boost::unordered_map<vm::type_string, builtin::macro> table_t;
    table_t _table;
  };//struct macro_table

}//namespace smart

#endif//__SMART_MACRO_TABLE__HPP____by_Duzy_Chan__
