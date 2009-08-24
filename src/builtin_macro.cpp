#include "builtin_macro.hpp"
#include "builtin_macro_imp.hpp"
#include "expand.hpp"
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/finder.hpp>
//#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
namespace smart
{
  namespace builtin
  {
    const vm::type_string macro::origin_undefined       = vm::type_string("undefined");
    const vm::type_string macro::origin_default         = vm::type_string("default");
    const vm::type_string macro::origin_environment     = vm::type_string("environment");
    const vm::type_string macro::origin_environment_override = vm::type_string("environment_override");
    const vm::type_string macro::origin_file            = vm::type_string("file");
    const vm::type_string macro::origin_command_line    = vm::type_string("command_line");
    const vm::type_string macro::origin_override        = vm::type_string("override");
    const vm::type_string macro::origin_automatic       = vm::type_string("automatic");

    const vm::type_string macro::flavor_undefined       = vm::type_string("undefined");
    const vm::type_string macro::flavor_recursive       = vm::type_string("recursive");
    const vm::type_string macro::flavor_simple          = vm::type_string("simple");

    //======================================================================

    pattern::pattern( const std::string & pat )
      : head()
      , tail()
      , is_valid( false )
    {
      std::size_t pos( pat.find( '%' ) );
      if ( pos != std::string::npos ) {
	head = pat.substr( 0, pos );
	tail = pat.substr( pos + 1, std::string::npos );
	is_valid = true;
      }
    }

    std::string pattern::match( const std::string & s )
    {
      std::string stem;
      if ( s.size() < head.size() + tail.size() ) return stem;
      if ( head != s.substr( 0, head.size() ) ) return stem;
      if ( tail != s.substr( s.size()-tail.size(), tail.size() ) ) return stem;
      stem = s.substr( head.size(), s.size()-head.size()-tail.size() );
      return stem;
    }

    vm::type_string pattern::convert( const pattern & pat1, const std::string & str )
    {
      vm::type_string v;
      if ( !is_valid || !pat1.is_valid ) return v;

      typedef boost::split_iterator<std::string::const_iterator> iter_t;
      iter_t it( boost::make_split_iterator(str, boost::token_finder(boost::is_any_of(" \t"))) );
      iter_t const end;
      for(; it != end; ++it) {
	if ( it->empty() ) continue;
	std::string stem( this->match(boost::copy_range<std::string>( *it )) );
	std::string s( pat1.head + stem + pat1.tail );
	if ( !v.empty() ) v += " ";
	v += s;
      }
      return v;
    }

    //======================================================================

    macro::macro()
      : _i( new imp( origin_undefined, flavor_undefined, vm::type_string(), vm::type_string() ) )
    {
    }

    macro::macro( const vm::type_string & name, const vm::type_string & value )
      : _i( new imp( origin_undefined, flavor_undefined, name, value ) )
    {
    }

    macro::~macro()
    {
      imp::deref( _i );
    }

    macro::macro( const macro & o )
      : _i( o._i )
    {
      imp::inref( _i );
    }

    macro & macro::operator=( const macro & o )
    {
      imp::deref( _i );
      _i = o._i;
      imp::inref( _i );
      return *this;
    }

    vm::type_string macro::expand( const context & ctx ) const
    {
      return smart::expand( ctx, _i->value );
    }

    vm::type_string macro::expand( const context & ctx, const std::vector<vm::type_string> & args ) const
    {
      return smart::expand( ctx, _i->value, args );
    }

    vm::type_string macro::subst( const std::vector<vm::type_string> & pats ) const
    {
      vm::type_string v;
      return v;
    }

    vm::type_string macro::patsubst( const std::vector<vm::type_string> & pats ) const
    {
      if ( pats.size() < 2 ) return vm::type_string();

      pattern pat0( pats[0] );
      pattern pat1( pats[1] );
      return pat0.convert( pat1, _i->value );
    }
      
    void macro::assign( const vm::type_string & s )
    {
      _i->value = s;
    }

    void macro::append( const vm::type_string & s )
    {
      _i->value += s;
    }

    vm::type_string macro::name() const
    {
      return _i->name;
    }

    vm::type_string macro::value() const
    {
      return _i->value;
    }

    vm::type_string macro::origin() const
    {
      return _i->origin;
    }

    vm::type_string macro::flavor() const
    {
      return _i->flavor;
    }

    void macro::set_value( const vm::type_string & s )
    {
      _i->value = s;
    }

    void macro::set_origin( const vm::type_string & s )
    {
      _i->origin = s;
    }

    void macro::set_flavor( const vm::type_string & s )
    {
      _i->flavor = s;
    }

  }//namespace builtin
}//namespace smart
