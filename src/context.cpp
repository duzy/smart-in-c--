/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

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
    , _targets()
    , _phony_targets()
    , _rules()
    , _macroArgs()
    , _frames()
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
    _macroArgs.push_back( args );
    for (int n=0; n < args.size(); ++n) {
      std::ostringstream oss; oss<<n+1;
      builtin::macro m( _macro_table->map(oss.str()) );
      m.set_origin( builtin::macro::origin_automatic );
      m.set_value( args[n] );
    }//for
  }

  void context::clear_macro_args()
  {
    if ( _macroArgs.empty() ) return;
    vm::type_string empty;
    for (int n=0; n < _macroArgs.back().size(); ++n) {
      std::ostringstream oss; oss<<n+1;
      builtin::macro m( _macro_table->map(oss.str()) );
      m.set_value( empty );
    }
    _macroArgs.pop_back();
  }

  builtin::target context::target( vm::type_string const& object )
  {
    target_table::iterator it( _targets.find(object) );
    if ( it == _targets.end() ) return builtin::target();
    assert( 1 <= it->second.refcount() );
    return it->second;
  }

  builtin::target context::map_target( const vm::type_string & object )
  {
    target_table::iterator it( _targets.find(object) );
    if ( it == _targets.end() ) {
      builtin::target t( object );
      assert( t.refcount() == 1 );
      _targets.insert(std::make_pair(object, t));
      assert( t.refcount() == 2 );
      return t;
    }
    assert( 1 <= it->second.refcount() );
    return it->second;
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

  const std::vector<std::string> context::files()
  {
    return _files;
  }

  std::string context::file() const
  {
    if ( _files.empty() ) return std::string();
    return _files.back();
  }

  bool context::is_phony( const builtin::target & tar ) const
  {
    if ( _phony_targets.empty() ) return false;
    return _phony_targets.find( tar ) != _phony_targets.end();
  }
}//namespace smart
