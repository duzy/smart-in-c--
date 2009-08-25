/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "vm_cpu.hpp"

namespace smart
{
  namespace vm
  {

    static void op_end( jit_info_t *ji, context * ctx )
    {
    }

    static void op_noop( jit_info_t *ji, context * ctx )
    {
    }

    static void op_call( jit_info_t *ji, context * ctx )
    {
    }

    static op_t s_ops[_number_of_ops] = {
      { op_end,  opcode_end },
      { op_noop, opcode_noop },
      { op_call, opcode_call }
    };

    op_t *op_jit = &s_ops[0];

  }//namespace vm
}//namespace smart
