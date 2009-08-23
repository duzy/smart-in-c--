#include "context.hpp"
#include "string_table.hpp"
#include "macro_table.hpp"
#include "function_table.hpp"
#include "vm_types.hpp"
namespace smart
{

  context::context()
    : _string_table( new string_table )
    , _macro_table( new macro_table )
    , _rule_table()
    , _function_table( new function_table )
  {
  }

  string_table * context::stable() const
  {
    return _string_table;
  }

  vm::type_string context::const_string( const std::string & c )
  {
    string_table::entry v( _string_table->add( c ) );
    return vm::type_string( v );
  }

//   vm::type_real context::const_number( double c )
//   {
//   }

  macro_table *context::mtable() const
  {
    return _macro_table;
  }

  builtin::macro context::macro( const vm::type_string & name )
  {
    //return _macro_table->map( name );
    return _macro_table->get( name );
  }

  builtin::macro context::macro( const std::string & name )
  {
    return _macro_table->get( vm::type_string(name) );
  }

  function_table *context::ftable() const
  {
    return _function_table;
  }
}//namespace smart
