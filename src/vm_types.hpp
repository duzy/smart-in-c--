
#ifndef __SMART_VM_TYPES__hpp____by_Duzy_Chan__
#define __SMART_VM_TYPES__hpp____by_Duzy_Chan__ 1

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
      enum {
	variable, //!< variable string value
	constant, //!< constant string value
	//name, //!< macro name, function name, etc..
      };

      bool is_constant() const;

      explicit type_string( const std::string & v );
      explicit type_string( const string_table_entry & );

      type_string( const type_string & );
      type_string & operator=( const type_string & );

      virtual ~type_string();

    private:
      unsigned is_constant_ : 1; //!< constant or variable
      unsigned is_copied_ : 1;
      std::string * ptr_;
    };//struct type_string

    struct type_object : type_base<type_object>
    {
    };//struct type_object

  }//namespace vm
}//namespace smart

#endif//__SMART_VM_TYPES__hpp____by_Duzy_Chan__
