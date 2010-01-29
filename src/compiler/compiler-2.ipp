/**								-*- c++ -*-
 *    Copyright 2009-01-07 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "../compiler.hpp"
#include "../context.hpp"
#include "../string_table.hpp"
#include "../macro_table.hpp"
#include "../builtin.hpp"
#include "../vm/vm_types.hpp"
#include "../expand.hpp"
#include "../exceptions.hpp"

#include <sstream>
#include <fstream>

//#include "parse_tree.ipp"
#include "grammar-2.ipp"
#include "compiling.ipp"

//#include <boost/spirit/home/qi/parse.hpp>

namespace smart
{
  void include( context &, const std::string & filename )
  {
  }

  compiler::compiler( context & ctx )
    : _context(ctx)
  {
  }

  void compiler::compile_file( const std::string & filename )
  {
    std::ifstream ifs( filename.c_str() );
    if ( !ifs ) {
      std::ostringstream err;
      err<<"smart: Can't open script '"<<filename<<"'.";
      throw smart::runtime_error( err.str() );
    }

    ifs.seekg( 0, ifs.end );
    int sz( ifs.tellg() );
    if ( 0 < sz ) {
      std::string code( sz, '\0' );
      ifs.seekg( 0, ifs.beg );
      ifs.read( &code[0], sz );

      _context._files.push_back( filename );
      compile( code.begin(), code.end() );
      _context._files.pop_back();
    }
  }

  void compiler::compile( const std::string & code )
  {
    compile( code.begin(), code.end() );
  }

  void compiler::compile( const std::string::const_iterator & codeBegin,
			  const std::string::const_iterator & codeEnd )
  {
    grammar<std::string::const_iterator> g;
    parse_tree tree; //!< abstract syntax tree

    std::string::const_iterator beg(codeBegin);
    std::string::const_iterator end(codeEnd);

    if ( !boost::spirit::qi::parse(beg, end, g, tree) ) {
      std::ostringstream err;
      err<<"smart: Failed parsing code.";
      throw smart::runtime_error( err.str() );
    }

    compile_parse_tree( tree );
  }
}
