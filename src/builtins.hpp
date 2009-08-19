#ifndef __SMART_BUILTINS__hpp____by_Duzy_Chan__
#define __SMART_BUILTINS__hpp____by_Duzy_Chan__ 1
#	include "vm_ops.hpp"

namespace smart
{
  struct context;

  namespace vm
  {
    struct type_object;
  }//namespace vm

  namespace builtin
  {

    void expand_macro( vm::jit_info_t *ji, context *ctx );

  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTINS__hpp____by_Duzy_Chan__
