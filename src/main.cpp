/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include <exception>
#include "context.hpp"
#include "compiler.hpp"
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

int main(int argc, const char** argv)
{
  std::set_terminate(__gnu_cxx::__verbose_terminate_handler);

  const char * files[] = {
    "Smartfile",
    NULL,
  };

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
  
  return 0;
}
