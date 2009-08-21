#include "builtin_macro.hpp"
#include "builtin_macro_imp.hpp"
namespace smart
{
  namespace builtin
  {

    macro::macro()
      : _i( NULL )
    {
    }

    macro::macro( vm::type_string name )
      : _i( new imp )
    {
    }

    bool macro::is_defined()
    {
      return _i != NULL;
    }

    vm::type_string macro::expand( const context & ) const
    {
      vm::type_string str;
      if ( !_i ) return str;
      return str;
    }

    vm::type_string macro::expand( const context &, const std::vector<vm::type_string> & args ) const
    {
      vm::type_string str;
      if ( !_i ) return str;
      return str;
    }
      
    void macro::assign( vm::type_string s )
    {
      if ( !_i ) return;
      _i->value = s;
    }

    void macro::append( vm::type_string s )
    {
      if ( !_i ) return;
      _i->value += s;
    }
      
    vm::type_string macro::value() const
    {
      vm::type_string str;
      if ( !_i ) return str;
      return str;
    }

    vm::type_string macro::origin() const
    {
      vm::type_string str;
      if ( !_i ) return str;
      return _i->origin;
    }

    vm::type_string macro::flavor() const
    {
      vm::type_string str;
      if ( !_i ) return str;
      return _i->flavor;
    }

  }//namespace builtin
}//namespace smart
