#ifndef __SMART_OPS__HPP____by_Duzy_Chan__
#define __SMART_OPS__HPP____by_Duzy_Chan__ 1
//#	include <boost/function.hpp>
#	include <functional>

namespace smart
{
  namespace vm
  {
    enum opcode_e {
      op_noop,
      op_sum,
      op_sub,
      op_mul,
      op_div,
      op_mod,
      
    };//enum opcode_e

    struct operand
    {
    };//struct operand

    struct operands
    {
    };//struct operands

    struct op
    {
      opcode_e code;
      std::function<void(const operands &)> fun;
    };//struct op
  }//namespace vm
}//namespace smart

#endif//__SMART_OPS__HPP____by_Duzy_Chan__
