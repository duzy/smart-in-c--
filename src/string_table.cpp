/**
 *    Copyright 2009-08-25 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include <string>
#include "string_table.hpp"

namespace smart
{
  string_table::string_table()
  //: _table()
  {
  }

  string_table::~string_table()
  {
    //struct delete_entry { void operator()( std::string * p ) { delete p; } };
    //std::for_each( _entries.begin(), _entries.end(), delete_entry() );
    //_entries.clear();
  }

  int string_table::size() const
  {
    return _entries.size();
  }

  string_table::entry string_table::add( const std::string & s )
  {
  # ifndef NO_FLYWEIGHT_STRING

    flyweight_string fs( s );
    int i( _entries.size() );
    _entries.push_back( fs );
    entry ent = { &(fs.get()), {i} };
    return ent;

  # else//NO_FLYWEIGHT_STRING

    typedef table_t::const_iterator iterator_t;
    typedef std::pair<iterator_t, bool> result_t;
    int i( _entries.size() );
    result_t res( _table.insert(std::make_pair(s, i)) );
    if ( res.second ) {
      entry ent = { &(res.first->first), {i} };
      _entries.push_back( ent.ptr );
      return ent;
    }
    return get( s ); //return NULL;

  #endif//NO_FLYWEIGHT_STRING
  }

  string_table::entry string_table::get( const std::string & s )
  {
  # ifndef NO_FLYWEIGHT_STRING

    flyweight_string fs( s );
    int i( 0 ); //!< TODO: the entry index
    entry ent = { &(fs.get()), {i} };
    return ent;
    
  # else//NO_FLYWEIGHT_STRING

    entry ent = { NULL, {0} }; //entry( NULL );
    typedef table_t::const_iterator iterator_t;
    iterator_t it( _table.find(s) );
    if ( it == _table.end() ) return ent;
    ent.ptr = &(it->first);
    ent.index.num = it->second;
    return ent;

  # endif//NO_FLYWEIGHT_STRING
  }

  string_table::entry string_table::get( index i )
  {
  # ifndef NO_TABLE_INDEX_CHECKING
    if ( i.num < 0 || _entries.size() <= i.num ) {
      entry ent = { NULL, {0} }; //entry( NULL );
      return ent;
    }
  # endif//NO_TABLE_INDEX_CHECKING

  # ifndef NO_FLYWEIGHT_STRING

    entry ent = { &_entries[ i.num ].get(), {i.num} };
    return ent;

  # else//NO_FLYWEIGHT_STRING
    entry ent = { _entries[ i.num ], {i.num} };
    return ent;
  # endif//NO_FLYWEIGHT_STRING
  }

}//namespace smart
