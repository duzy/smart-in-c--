#include "context.hpp"
#include "string_table.hpp"
#include "macro_table.hpp"
#include "function_table.hpp"
#include "vm_types.hpp"
#include <sstream>
#include <iostream>
namespace smart
{

  void info( const vm::type_string & s )
  {
    std::clog<<"info: "<<s<<std::endl;
  }

  void warning( const vm::type_string & s )
  {
    std::clog<<"warning: "<<s<<std::endl;
  }

  void error( const vm::type_string & s )
  {
    std::cerr<<"error: "<<s<<std::endl;
  }

  //======================================================================

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

  void context::setup_macro_args( const std::vector<vm::type_string> & args )
  {
    argsStack.push_back( args );
    for (int n=0; n < args.size(); ++n) {
      std::ostringstream oss; oss<<n+1;
      builtin::macro m( _macro_table->map(oss.str()) );
      m.set_origin( builtin::macro::origin_automatic );
      m.set_value( args[n] );
    }//for
  }

  void context::clear_macro_args()
  {
    if ( argsStack.empty() ) return;
    vm::type_string empty;
    for (int n=0; n < argsStack.back().size(); ++n) {
      std::ostringstream oss; oss<<n+1;
      builtin::macro m( _macro_table->map(oss.str()) );
      m.set_value( empty );
    }
    argsStack.pop_back();
  }

  function_table *context::ftable() const
  {
    return _function_table;
  }

  vm::type_string context::invoke( const vm::type_string & name,
				   const std::vector<vm::type_string> & args )
  {
    function_table::function_t fun(_function_table->get(name));
    if ( !fun ) return vm::type_string();

    _frames.push_back( frame() );

    frame & f( _frames.back() );
    f.resize( args.size() + 1 );
    for( int n=0; n < args.size(); ++n ) f[n+1] = args[n];

    fun( *this );

    vm::type_string result( f[0] );

    _frames.pop_back();

    return result;
  }

  frame & context::current_frame()
  {
    if ( _frames.empty() ) _frames.push_back( frame() );
    return _frames.front();
  }
}//namespace smart
