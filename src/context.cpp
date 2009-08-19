#include "context.hpp"
#include "string_table.hpp"
#include "vm_types.hpp"
namespace smart
{

  context::context()
    : _string_table( new string_table )
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

}//namespace smart
