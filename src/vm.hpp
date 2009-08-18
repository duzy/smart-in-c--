#ifndef __SMART_VM__HPP____by_Duzy_Chan__
#define __SMART_VM__HPP____by_Duzy_Chan__ 1
#	include "vm_fwd.hpp"

namespace smart
{
  namespace vm
  {

    struct frame
    {
      object_ptr operator[] ( int ); //!< indexed
      object_ptr operator[] ( const std::string & ); //!< named
    };//struct frame

    /**
     *  @brief Executor
     */
    struct exec
    {
    };//struct exec

    /**
     *  @brief Just In Time Executor
     */
    struct jit
    {
      //!< ???
    };//struct jit

  }//namespace vm
}//namespace smart

#endif//__SMART_VM__HPP____by_Duzy_Chan__
