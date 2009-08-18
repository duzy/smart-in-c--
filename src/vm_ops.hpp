#ifndef __SMART_VM_OPS__hpp____by_Duzy_Chan__
#define __SMART_VM_OPS__hpp____by_Duzy_Chan__ 1

namespace smart
{
  namespace vm
  {
    typedef long opcode_t;

    enum opcode_enum
      {
	opcode_end,
	opcode_noop,
	opcode_call,
	_number_of_ops,
      };

    /**
     *  @brief Argument for ops
     *	Of the following types:
     *		o Integer
     *		o Real(floating)
     *		o String
     *		o Object
     */
    struct operand
    {
      unsigned type : 2; //!< decide which register to use
      unsigned index : 30; //32-2
    };//struct operand

    struct jit_info_t
    {
      int registers[];
    };//struct jit_info_t

    typedef void (*jit_fn_t)( jit_info_t *ji, context * ctx );

    struct op_t
    {
      jit_fn_t fn;
      opcode_t code;
    };//struct op_t

    extern op_t *op_jit;
    
  }//namespace vm
}//namespace smart

#endif//__SMART_VM_OPS__hpp____by_Duzy_Chan__
