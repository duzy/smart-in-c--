#include "vm_types.hpp"
#include "vm_string_imp.hpp"
namespace smart
{
  namespace vm
  {
    
    type_string::type_string( const std::string & v )
      : _i( new imp/*(v)*/ )
    {
    }

    type_string::type_string( const string_table_entry & e )
      : _i( new imp/*(e)*/ )
    {
    }

    type_string::type_string( const type_string & o )
    {
      this->operator=( o );
    }

    type_string & type_string::operator=( const type_string & o )
    {
      //deref( _i );

      //if (

      *_i = *o._i ;
      return *this;
    }

    type_string::~type_string()
    {
      //if ( is_copied_ ) delete ptr_;
    }

  }//namespace vm
}//namespace smart
