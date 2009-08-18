#include "vm_ops.hpp"
namespace smart
{
  namespace vm
  {

    enum op_code {
      op_code_noop,
      op_code_call,

      _number_of_ops,
    };

    struct op_t
    {
      op_code code;
      object_ptr (*op)( context & ctx );
    };

    static object_ptr (*op_noop)( context & ctx )
    {
    }

    static s_ops[_number_of_ops] = {
      { op_code_noop,  }
      { op_code_call, }
    };
    
  }//namespace vm
}//namespace smart
