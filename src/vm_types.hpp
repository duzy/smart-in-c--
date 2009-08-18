
#ifndef __SMART_VM_TYPES__hpp____by_Duzy_Chan__
#define __SMART_VM_TYPES__hpp____by_Duzy_Chan__ 1

namespace smart
{
  namespace vm
  {

    template<typename Concrete, typename T = void*>
    struct type_base
    {
    protected:
      //T ptr;
    };//struct type_base

    struct type_integer : type_base<type_integer>
    {
    };//struct type_integer

    struct type_float : type_base<type_float>
    {
    };//struct type_float

    struct type_string : type_base<type_string>
    {
    };//struct type_string

    struct type_object : type_base<type_object>
    {
    };//struct type_object

  }//namespace vm
}//namespace smart

#endif//__SMART_VM_TYPES__hpp____by_Duzy_Chan__
