#ifndef __SMART_CONTEXT__HPP____by_Duzy_Chan__
#define __SMART_CONTEXT__HPP____by_Duzy_Chan__ 1
#	include <vm_fwd.hpp>

namespace smart
{
  struct string_table;

  /**
   *  @brief Smart script running context
   */
  struct context
  {
    /**
     *  @brief Calling stuffs 
     *  @{
     */
    frame * current_frame();
    frame * push_frame(); //!< return the new top frame
    /*  @}
     */

  private:
    string_table *_stringTable;
    std::stack< frame* > _frames;
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
