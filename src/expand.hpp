#ifndef __SMART_EXPAND__HPP____by_Duzy_Chan__
#define __SMART_EXPAND__HPP____by_Duzy_Chan__ 1

namespace smart
{
  vm::type_string expand( const context & ctx, const vm::type_string & str );
  vm::type_string expand( const context & ctx, const vm::type_string & str,
			  const std::vector<vm::type_string> & args );
}//namespace smart

#endif//__SMART_EXPAND__HPP____by_Duzy_Chan__
