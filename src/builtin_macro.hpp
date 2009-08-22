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
      explicit macro( const vm::type_string & name,
                      const vm::type_string & value = vm::type_string() );

      virtual ~macro();

      vm::type_string name() const;

      /**
       *  @brief Unexpended value
       */
      vm::type_string value() const;
      void set_value( const vm::type_string & );

      vm::type_string expand( const context & ) const;
      vm::type_string expand( const context &, const std::vector<vm::type_string> & args ) const;

      void assign( const vm::type_string & );
      void append( const vm::type_string & );

      static const vm::type_string origin_undefined;
      static const vm::type_string origin_default;
      static const vm::type_string origin_environment;
      static const vm::type_string origin_environment_override;
      static const vm::type_string origin_file;
      static const vm::type_string origin_command_line;
      static const vm::type_string origin_override;
      static const vm::type_string origin_automatic;
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
      void set_origin( const vm::type_string & );

      static const vm::type_string flavor_undefined;
      static const vm::type_string flavor_recursive;
      static const vm::type_string flavor_simple;
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
      void set_flavor( const vm::type_string & );

    private:
      struct imp;
      imp *_i;
    };//struct macro
  
  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN_MACRO__HPP____by_Duzy_Chan__
