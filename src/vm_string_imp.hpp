#ifndef __SMART_VM_STRING_IMP__HPP____by_Duzy_Chan__
#define __SMART_VM_STRING_IMP__HPP____by_Duzy_Chan__ 1
#	include <string>

namespace smart
{
  namespace vm
  {

    struct type_string::imp
    {
      std::string * _str;
    };//struct type_string::imp

  }//namespace vm
}//namespace smart

#endif//__SMART_VM_STRING_IMP__HPP____by_Duzy_Chan__
