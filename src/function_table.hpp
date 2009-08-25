/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#ifndef __SMART_FUNCTION_TABLE__HPP____by_Duzy_Chan__
#define __SMART_FUNCTION_TABLE__HPP____by_Duzy_Chan__ 1
#	include <boost/unordered/unordered_map.hpp>
//#	include "vm_fwd.hpp"
#	include "vm_types.hpp"

namespace smart
{
  struct context;

  struct function_table
  {
    function_table();

    typedef void (*function_t)( context & ctx );
    function_t get( const vm::type_string & name );

  private:
    typedef boost::unordered_map<vm::type_string, function_t> table_t;
    table_t _table;
  };//struct function_table
}//namespace smart

#endif//__SMART_FUNCTION_TABLE__HPP____by_Duzy_Chan__
