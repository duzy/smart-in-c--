#include <string>
#include "string_table.hpp"

namespace smart
{
  string_table::string_table()
    : _table()
  {
  }

  string_table::entry string_table::add( const std::string & s )
  {
//     typedef std::set<std::string>::const_iterator iterator_t;
//     typedef std::pair<iterator_t, bool> result_t;
//     result_t res( _table.insert(s) );
//     if ( res.second ) return &(*res.first);
//     return get( s ); //return NULL;
    entry ent = { NULL }; //entry( NULL );
    return ent;
  }

  string_table::entry string_table::get( const std::string & s )
  {
//     typedef std::set<std::string>::const_iterator iterator_t;
//     iterator_t it( _table.find(s) );
//     if ( it == _table.end() ) return NULL;
//     return &(*it);
    entry ent = { NULL }; //entry( NULL );
    return ent;
  }
}//namespace smart
