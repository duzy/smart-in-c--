/**
 *    Copyright 2009-08-25 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "macro_table.hpp"
namespace smart
{
  macro_table::macro_table()
    : _table()
  {
  }

  builtin::macro macro_table::map( const vm::type_string & name )
  {
    typedef table_t::const_iterator iterator_t;

    iterator_t it( _table.find(name) );
    if ( it == _table.end() ) {
      typedef std::pair<iterator_t, bool> result_t;
      builtin::macro m( name );
      result_t res( _table.insert(std::make_pair(name, m)) );
      if ( !res.second ) {
	throw std::runtime_error("can't insert macro");
	return builtin::macro();
      }
      return m;
    }
    return it->second;
  }

  builtin::macro macro_table::get( const vm::type_string & name )
  {
    typedef table_t::const_iterator iterator_t;
    iterator_t it( _table.find(name) );
    if ( it == _table.end() ) return builtin::macro( name );
    return it->second;
  }

}//namespace smart
