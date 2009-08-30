/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "context.hpp"
#include "compiler.hpp"
#include "exceptions.hpp"
#include <boost/filesystem/operations.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main(int argc, const char** argv)
{
  std::set_terminate(__gnu_cxx::__verbose_terminate_handler);

  const char * files[] = {
    "Smartfile",
    NULL,
  };

  try {
    smart::context ctx;
    smart::compiler sm( ctx );

    for( int n=0; files[n] != NULL; ++n ) {
      std::string f( files[n] );
      if ( fs::exists( f ) ) {
	sm.compile_file( f );
	break;
      }
    }

    {
      smart::builtin::target tar( ctx.default_goal() );
      if ( tar.is_null() ) return 0;
      tar.update( ctx );
    }
  }//try

  catch( const smart::compile_error & e ) {
    std::clog<<e.file()<<":"<<e.line()<<":"<<e.column()<<": "
	     <<e.what()<<std::endl;
  }//catch( compile-error )

  catch( const smart::make_error & e ) {
    std::clog<<e.what()<<std::endl;
  }//catch( make-error )

  catch( const smart::runtime_error & e ) {
    std::clog<<e.what()<<std::endl;
  }//catch( runtime-error )
  
  return 0;
}
