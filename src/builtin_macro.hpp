#ifndef __SMART_BUILTIN_MACRO__HPP____by_Duzy_Chan__
#define __SMART_BUILTIN_MACRO__HPP____by_Duzy_Chan__ 1
#	include "vm_types.hpp"
#	include <vector>

namespace smart
{
  struct context;

  namespace builtin
  {

    struct macro : vm::type_object
    {
      macro();
      explicit macro( vm::type_string name );

      bool is_defined();

      /**
       *  @brief Unexpended value
       */
      vm::type_string value() const;

      vm::type_string expand( const context & ) const;
      vm::type_string expand( const context &, const std::vector<vm::type_string> & args ) const;

      void assign( vm::type_string );
      void append( vm::type_string );

      /**
       *  @brief Tells where the macro come from.
       *        `undefined'
       *        `default'
       *        `environment'
       *        `environment override'
       *        `file'
       *        `command line'
       *        `override'
       *        `automatic'
       */
      vm::type_string origin() const;

      /**
       *  @brief The flavor of the macro
       *  @return One of the following:
       *        `undefined'
       *                if MACRO was never defined.
       *        `recursive'
       *                if MACRO is a recursively expanded variable.
       *        `simple'
       *                if MACRO is a simply expanded variable.
       */
      vm::type_string flavor() const;

    private:
      struct imp;
      imp *_i;
    };//struct macro
  
  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN_MACRO__HPP____by_Duzy_Chan__
