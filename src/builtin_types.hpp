#ifndef __SMART_BUILTIN_TYPES__hpp____by_Duzy_Chan__
#define __SMART_BUILTIN_TYPES__hpp____by_Duzy_Chan__ 1
#	include "vm_types.hpp"

namespace smart
{
  namespace builtin
  {

//     struct integer : vm::type_integer
//     {
//     };//struct integer

    struct macro : vm::type_object
    {
      explicit macro( vm::type_string name );

      vm::type_string expand() const;
      vm::type_string expand( const std::vector<vm::type_string> & args ) const;
      
      void assign( vm::type_string );
      void append( vm::type_string );
      
      vm::type_string str() const;
    };//struct macro

  }//namespace builtin
}//namespace smart
#endif//__SMART_BUILTIN_TYPES__hpp____by_Duzy_Chan__
