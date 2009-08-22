#include "function_table.hpp"
#include "builtins.hpp"
namespace smart
{
  static struct {
    const char * name;
    function_table::function_t fun;
  } s_builtin_functions[3] = {
    { "noop", &builtins::noop },
    { "assign_macro", builtins::assign_macro },
    { "expand_macro", builtins::expand_macro }
  };

  function_table::function_table()
    : _table()
  {
    //_table.insert(std::make_pair("assign_macro", &builtin::assign_macro));
    //_table.insert(std::make_pair("expand_macro", &builtin::expand_macro));
    std::size_t sz(sizeof(s_builtin_functions)/sizeof(s_builtin_functions[0]));
    for( int n=0; n < sz; ++n ) {
      _table.insert(std::make_pair( s_builtin_functions[n].name,
				    s_builtin_functions[n].fun ));
    }
  }

  function_table::function_t function_table::get( const vm::type_string & name )
  {
    typedef table_t::const_iterator iterator_t;
    iterator_t it( _table.find(name) );
    if ( it == _table.end() ) return function_t( s_builtin_functions[0].fun );
    return it->second;
  }

}//namespace smart
