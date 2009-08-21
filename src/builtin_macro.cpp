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
      return str;
    }

    vm::type_string macro::expand( const context &, const std::vector<vm::type_string> & args ) const
    {
      vm::type_string str;
      return str;
    }
      
    void macro::assign( vm::type_string )
    {
    }

    void macro::append( vm::type_string )
    {
    }
      
    vm::type_string macro::value() const
    {
      vm::type_string str;
      return str;
    }
    
  }//namespace builtin
}//namespace smart
