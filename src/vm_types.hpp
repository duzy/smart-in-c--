
#ifndef __SMART_VM_TYPES__hpp____by_Duzy_Chan__
#define __SMART_VM_TYPES__hpp____by_Duzy_Chan__ 1
#	include <string>
#	include <istream>
#	include <ostream>

namespace smart
{
  struct string_table_entry;

  namespace vm
  {

    template<typename Concrete, typename T = void*>
    struct type_base
    {
      virtual ~type_base() {}

    protected:
      //T ptr;
    };//struct type_base

    struct type_integer : type_base<type_integer>
    {
    };//struct type_integer

    struct type_real : type_base<type_real>
    {
    };//struct type_real

    struct type_string : type_base<type_string>
    {
      explicit type_string( const std::string & v );
      explicit type_string( const string_table_entry & );

      type_string( const type_string & );
      type_string & operator=( const type_string & );

      virtual ~type_string();

      operator const std::string&();

      std::ostream & operator<<( std::ostream & );
      std::istream & operator>>( std::istream & );

      bool operator==( const type_string & o );

      long refcount() const;

    private:
      struct imp;
      imp * _i;
    };//struct type_string

    struct type_object : type_base<type_object>
    {
      virtual ~type_object() {}
    };//struct type_object

  }//namespace vm
}//namespace smart

#endif//__SMART_VM_TYPES__hpp____by_Duzy_Chan__
