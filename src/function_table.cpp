#include "function_table.hpp"
#include "builtins.hpp"
namespace smart
{
  static struct {
    const char * name;
    function_table::function_t fun;
  } s_builtin_functions[] = {
    { "noop", builtin::noop },
    { "subst", builtin::subst },
    { "patsubst", builtin::patsubst },
    { "strip", builtin::strip },
    { "findstring", builtin::findstring },
    { "filter", builtin::filter },
    { "filter_out", builtin::filter_out },
    { "sort", builtin::sort },
    { "word", builtin::word },
    { "wordlist", builtin::wordlist },
    { "firstword", builtin::firstword },
    { "lastword", builtin::lastword },
    { "if", builtin::if_f },
    { "or", builtin::or_f },
    { "and", builtin::and_f },
    { "foreach", builtin::foreach_f },
    { "call", builtin::call },
    { "value", builtin::value },
    { "origin", builtin::origin },
    { "flavor", builtin::flavor },
    { "error", builtin::error },
    { "warning", builtin::warning },
    { "info", builtin::info },
    { "assign_macro", builtin::assign_macro },
    { "expand_macro", builtin::expand_macro },
  };

  function_table::function_table()
    : _table()
  {
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
