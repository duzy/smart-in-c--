#ifndef __SMART_VM_STRING_IMP__HPP____by_Duzy_Chan__
#define __SMART_VM_STRING_IMP__HPP____by_Duzy_Chan__ 1
#	include <string>

namespace smart
{
  namespace vm
  {

    struct type_string::imp
    {
      union {
	std::string * _str;
	const std::string * _cstr;
      };
      long _usage;

      explicit imp( const std::string & v )
	: _str( new std::string(v) )
	, _usage( 1 )
      {
      }

      explicit imp( const string_table_entry & e )
	: _cstr( e.ptr )
	, _usage( -1 )
      {
      }

      static long inref( imp * p )
      {
	if ( p->_usage < 0 ) return p->_usage;
	return ++p->_usage;
      }

      static long deref( imp * & p )
      {
	if ( p->_usage < 0 ) return p->_usage;
	if ( --p->_usage == 0 ) {
	  delete p;
	  p = 0;
	  return 0;
	}
	return p->_usage;
      }
    };//struct type_string::imp

  }//namespace vm
}//namespace smart

#endif//__SMART_VM_STRING_IMP__HPP____by_Duzy_Chan__
