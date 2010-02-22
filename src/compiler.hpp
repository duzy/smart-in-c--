/**
 *    Copyright 2009-08-25 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#ifndef __SMART_COMPILER__HPP____by_Duzy_Chan__
#define __SMART_COMPILER__HPP____by_Duzy_Chan__ 1
#	include <string>

namespace smart
{
  struct context;
  struct compiler
  {
    compiler( context & );
    void compile_file( const std::string & filename );
    void compile( const std::string & code );
    void compile( const std::string::const_iterator & codeBeg,
                  const std::string::const_iterator & codeEnd );

  private:
    context & _context;
  };//struct compiler

  void include( context &, const std::string & filename );
  
}//namespace smart

#endif//__SMART_COMPILER__HPP____by_Duzy_Chan__
