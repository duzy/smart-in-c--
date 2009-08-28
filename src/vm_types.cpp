/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "string_table.hpp"
#include "vm_types.hpp"
#include "vm_string_imp.hpp"
#include <boost/algorithm/string/trim.hpp>
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

    type_string & type_string::operator=( const std::string & s )
    {
      imp::copy_if_refs( _i );
      *_i->_str = s;
      return *this;
    }

    type_string::~type_string()
    {
      imp::deref( _i );
    }

    type_string::operator const std::string&() const
    {
      return *_i->_str;
    }

    std::ostream & operator<<( std::ostream &os, const type_string & s )
    {
      os << ( *s._i->_cstr );
      return os;
    }

    std::istream & operator>>( std::istream &is, type_string & s )
    {
      if ( s._i->_usage == -1 ) {
	std::ostringstream err;
	err<<"overide a constant string";
	throw std::runtime_error( err.str() );
      }
      is >> ( *s._i->_str );
      return is;
    }

    bool type_string::operator<( const type_string & o ) const
    {
      return *_i->_cstr < *o._i->_cstr;
    }

    bool type_string::operator==( const type_string & o ) const
    {
      if ( _i == o._i ) return true;
      return *_i->_cstr == *o._i->_cstr;
    }

    bool type_string::operator==( const std::string & o ) const
    {
      //return _i && *_i->_cstr == o;
      return *_i->_cstr == o;
    }

    type_string & type_string::operator+=( const type_string & o )
    {
      imp::copy_if_refs( _i );
      *_i->_str += *o._i->_cstr;
      return *this;
    }

    type_string & type_string::operator+=( const std::string & s )
    {
      imp::copy_if_refs( _i );
      *_i->_str += s;
      return *this;
    }

    type_string operator+( const type_string & lhs, const type_string & rhs )
    {
      const std::string & s( lhs );
      type_string tmp( lhs );
      tmp += rhs;
      return tmp;
    }

    type_string operator+( const std::string & lhs, const type_string & rhs )
    {
      type_string tmp( lhs );
      tmp += rhs;
      return tmp;
    }

    type_string operator+( const type_string & lhs, const std::string & rhs )
    {
      const std::string & s( lhs );
      type_string tmp( lhs );
      *tmp._i->_str += rhs;
      return tmp;
    }

    long type_string::refcount() const
    {
      return _i->_usage;
    }

    std::size_t type_string::hash_value() const
    {
      //return boost::hash_value( _i );
      return boost::hash_value( *_i->_cstr );
    }

    bool type_string::empty() const
    {
      return _i->_cstr->empty();
    }

    void type_string::trim()
    {
      imp::copy_if_refs( _i );
      boost::trim( *_i->_str );
    }
  }//namespace vm
}//namespace smart

