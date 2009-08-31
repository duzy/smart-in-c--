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

  parser_error::parser_error( long line, long column, const std::string & w ) throw()
    : exception( w ), _line(line), _column(column)
  {
  }

  parser_error::~parser_error() throw()
  {
  }

  long parser_error::line() const throw()
  {
    return _line;
  }

  long parser_error::column() const throw()
  {
    return _column;
  }

  //======================================================================

  compile_error::compile_error( const std::string & f, long line, long column, const std::string & w ) throw()
    : exception(w), _file(f), _line(line), _column(column)
  {
  }

  compile_error::~compile_error() throw()
  {
  }

  const std::string & compile_error::file() const throw()
  {
    return _file;
  }

  long compile_error::line() const throw()
  {
    return _line;
  }

  long compile_error::column() const throw()
  {
    return _column;
  }

  //======================================================================

  make_error::make_error( const std::string & err ) throw()
    : exception( err )
  {
  }

  make_error::~make_error() throw()
  {
  }

  //======================================================================

  runtime_error::runtime_error( const std::string & err ) throw()
    : exception( err )
  {
  }

  runtime_error::~runtime_error() throw()
  {
  }

}//namespace smart
