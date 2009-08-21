#include "builtin_macro.hpp"
#include "builtin_macro_imp.hpp"
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

    macro::macro()
      : _i( new imp( origin_undefined, flavor_undefined, vm::type_string(), vm::type_string() ) )
    {
    }

    macro::macro( const vm::type_string & name, const vm::type_string & value )
      : _i( new imp( origin_undefined, flavor_undefined, name, value ) )
    {
    }

    vm::type_string macro::expand( const context & ) const
    {
      vm::type_string str;
      return str;
    }

    vm::type_string macro::expand( const context &, const std::vector<vm::type_string> & args ) const
    {
      vm::type_string str;
      return str;
    }
      
    void macro::assign( const vm::type_string & s )
    {
      _i->value = s;
    }

    void macro::append( const vm::type_string & s )
    {
      _i->value += s;
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

  }//namespace builtin
}//namespace smart
