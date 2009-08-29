/**
 *    Copyright 2009-08-29 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "exceptions.hpp"

namespace smart
{

  exception::exception( const std::string & s ) throw()
    : _what(s)
  {
  }

  exception::~exception() throw()
  {
  }

  const char * exception::what() const throw()
  {
    return _what.c_str();
  }

  //======================================================================

  compile_error::compile_error( const std::string & f, long line, long column, const std::string & w ) throw()
    : exception(w), _file(f), _line(line), _column(column)
  {
  }

  compile_error::~compile_error() throw()
  {
  }

}//namespace smart
