#ifndef __SMART_BUILTINS__hpp____by_Duzy_Chan__
#define __SMART_BUILTINS__hpp____by_Duzy_Chan__ 1
#	include "vm_fwd.hpp"

namespace smart
{
  struct context;

  namespace builtins
  {

    void noop( context & ctx );
    void assign_macro( context & ctx );
    void expand_macro( context & ctx );

  }//namespace builtins
}//namespace smart

#endif//__SMART_BUILTINS__hpp____by_Duzy_Chan__
