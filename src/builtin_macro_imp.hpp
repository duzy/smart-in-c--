#ifndef __SMART_BUILTIN_MACRO_IMP__HPP____by_Duzy_Chan__
#define __SMART_BUILTIN_MACRO_IMP__HPP____by_Duzy_Chan__ 1

namespace smart
{
  namespace builtin
  {
    struct macro::imp
    {
      vm::type_string origin;
      vm::type_string flavor;
      vm::type_string name;
      vm::type_string value;

      imp( const vm::type_string & ori, const vm::type_string & fla,
	   const vm::type_string & nam, const vm::type_string & val )
	: origin( ori )
	, flavor( fla )
	, name( nam )
	, value( val )
      {
      }
    };//struct macro::imp
  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN_MACRO_IMP__HPP____by_Duzy_Chan__
