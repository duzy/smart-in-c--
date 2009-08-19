#ifndef __SMART_CONTEXT__HPP____by_Duzy_Chan__
#define __SMART_CONTEXT__HPP____by_Duzy_Chan__ 1
#	include "vm_fwd.hpp"
#	include <string>

namespace smart
{
  struct string_table;
  struct real_table;

  /**
   *  @brief Smart script running context
   */
  struct context
  {
    context();

    string_table * stable() const;

    vm::type_string const_string( const std::string & c );
    //vm::type_real const_number( double c );

  private:
    string_table *_string_table; //!< for string constants
    //real_table *_number_table; //!< for real number constants
    //std::stack< frame* > _frames;
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
