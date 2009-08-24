
#ifndef __SMART_VM_TYPES__hpp____by_Duzy_Chan__
#define __SMART_VM_TYPES__hpp____by_Duzy_Chan__ 1
#	include <string>
#	include <istream>
#	include <ostream>
#	include <typeinfo>

namespace smart
{
  struct string_table_entry;

  namespace vm
  {
    struct type
    {
      virtual ~type() {}

      //virtual std::typeinfo typeinfo() const = 0;
    };//struct type

    template<typename Concrete, typename T = void*>
    struct type_base : type
    {
      

    protected:
      //T ptr;
    };//struct type_base

    struct type_integer : type_base<type_integer>
    {
    };//struct type_integer

    struct type_real : type_base<type_real>
    {
    };//struct type_real

    //--------------------------------------------------

    struct type_string : type_base<type_string>
    {
      /*explicit*/ type_string( const std::string & v = "" );
      explicit type_string( const string_table_entry & );

      type_string( const type_string & );
      type_string & operator=( const type_string & );
      type_string & operator=( const std::string & );

      virtual ~type_string();

      std::size_t hash_value() const;

      operator const std::string&() const;

      bool operator==( const type_string & o ) const;
      bool operator==( const std::string & o ) const;
      bool operator!=( const type_string & o ) const { return !(*this == o); }
      bool operator!=( const std::string & o ) const { return !(*this == o); }
      type_string & operator+=( const type_string & o );
      type_string & operator+=( const std::string & s );

      long refcount() const;

      bool empty() const;

    private:
      struct imp;
      imp * _i;

      friend std::ostream & operator<<( std::ostream &, const type_string & );
      friend std::istream & operator>>( std::istream &, type_string & );
      friend type_string operator+( const type_string &, const std::string & );
    };//struct type_string

    //--------------------------------------------------

    struct type_ext : type_base<type_ext>
    {
      virtual ~type_ext() {}
    };//struct type_object

    //--------------------------------------------------

    std::ostream & operator<<( std::ostream &, const type_string & );
    std::istream & operator>>( std::istream &, type_string & );
    type_string operator+( const type_string & lhs, const type_string & rhs );
    type_string operator+( const std::string & lhs, const type_string & rhs );
    type_string operator+( const type_string & lhs, const std::string & rhs );
  }//namespace vm
}//namespace smart

//==================================================
#	include <boost/functional/hash.hpp>
namespace boost
{
  template <>
  struct hash<smart::vm::type_string>
    : std::unary_function<smart::vm::type_string, std::size_t>
  {
    std::size_t operator()(smart::vm::type_string const& val) const
    {
      return val.hash_value();
    }
  };
}//namespace boost

#endif//__SMART_VM_TYPES__hpp____by_Duzy_Chan__
