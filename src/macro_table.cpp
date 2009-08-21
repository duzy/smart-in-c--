#include "macro_table.hpp"
namespace smart
{
  macro_table::macro_table()
    : _table()
  {
  }

  builtin::macro macro_table::map( vm::type_string name )
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
}//namespace smart
