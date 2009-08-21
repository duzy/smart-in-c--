#include "string_table.hpp"
#include "vm_types.hpp"
#include "vm_string_imp.hpp"
#include <sstream>

namespace smart
{
  namespace vm
  {
    
    type_string::type_string( const std::string & v )
      : _i( new imp(v) )
    {
    }

    type_string::type_string( const string_table_entry & e )
      : _i( new imp(e) )
    {
    }

    type_string::type_string( const type_string & o )
      : _i( NULL )
    {
      _i = o._i ;
      imp::inref( _i );
    }

    type_string & type_string::operator=( const type_string & o )
    {
      imp::deref( _i );
      _i = o._i ;
      imp::inref( _i );
      return *this;
    }

    type_string::~type_string()
    {
      imp::deref( _i );
    }

    type_string::operator const std::string&()
    {
      return *_i->_str;
    }

    std::ostream & type_string::operator<<( std::ostream & os ) const
    {
      os << ( *_i->_cstr );
      return os;
    }

    std::istream & type_string::operator>>( std::istream & is )
    {
      if ( _i->_usage == -1 ) {
	std::ostringstream err;
	err<<"overide a constant string";
	throw std::runtime_error( err.str() );
      }
      is >> ( *_i->_str );
      return is;
    }

    bool type_string::operator==( const type_string & o ) const
    {
      return _i == o._i;
    }

    long type_string::refcount() const
    {
      return _i->_usage;
    }

    std::size_t type_string::hash_value() const
    {
      return boost::hash_value( _i );
    }
  }//namespace vm
}//namespace smart

