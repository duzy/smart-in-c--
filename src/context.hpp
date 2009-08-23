#ifndef __SMART_CONTEXT__HPP____by_Duzy_Chan__
#define __SMART_CONTEXT__HPP____by_Duzy_Chan__ 1
#	include "vm_fwd.hpp"
#	include "builtin_macro.hpp"
#	include <string>

namespace smart
{
  struct string_table;
  struct real_table;
  struct macro_table;
  struct rule_table;
  struct function_table;

  /**
   *  @brief Smart script running context
   */
  struct context
  {
    context();

    string_table * stable() const;

    vm::type_string const_string( const std::string & c );
    //vm::type_real const_number( double c );

    macro_table *mtable() const;
    builtin::macro macro( const vm::type_string & v );
    builtin::macro macro( const std::string & v );

    /**
     * setup $1, $2, $3, $4, ....
     */
    void setup_macro_args( const std::vector<vm::type_string> & args );
    void clear_macro_args();

    function_table *ftable() const;

  private:
    string_table *_string_table; //!< for string constants
    //real_table *_number_table; //!< for real number constants
    macro_table *_macro_table;
    rule_table *_rule_table;
    function_table *_function_table;
  };//struct context

}//namespace smart

/**
 *	Macro	- Expandable makefile variable
 *	Rule	- Target building rule
 *	Target	- A file to be built according a defined rule
 *	Prerequisite - Targets required by the currently building target
 *	Variable - Smart script variable: string, integer, float, array
 */

#endif//__SMART_CONTEXT__HPP____by_Duzy_Chan__
