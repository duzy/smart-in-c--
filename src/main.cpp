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
#include <boost/program_options.hpp>
#include <iostream>
//#include <string>
//#include <vector>

namespace fs = boost::filesystem;
namespace po = boost::program_options;

static void print_version()
{
  std::cout
    <<"Version 1.0"
    <<std::endl
    ;
}

int main(int ac, char** av)
{
  std::set_terminate(__gnu_cxx::__verbose_terminate_handler);

  po::variables_map opts;
  {
    po::options_description generic( "Generic smart options" );
    generic.add_options()
      ( "help", "Prints this screen of help message." )
      ( "version,v", "Prints the version information." )
      ( "file,f", po::value<std::string>(),
	"Read specified file as Smartfile." )
      ;
    po::options_description hidden( "Hidden options" );
    hidden.add_options()
      ( "targets", po::value<std::vector<std::string> >(), "specify target" )
      ;
    po::options_description all( "Allowed smart options" );
    all.add( generic ).add( hidden );
    po::options_description visible( "Allowed options" );
    visible.add( generic );

    //po::store( po::parse_command_line(ac, av, desc), opts );
    po::positional_options_description p;
    p.add( "targets", -1 );
    po::store( po::command_line_parser(ac, av).
	       options(all).positional(p).run(), opts );
    po::notify( opts );

    if ( opts.count("help") ) {
      std::cout << visible << std::endl;
      return 1;
    }
    else if ( opts.count("version") ) {
      print_version();
      return 1;
    }
  }

  //!< Default Smartfile names
  const char * default_files[] = {
    "Smartfile",
    NULL,
  };

  smart::context ctx;
  try {
    smart::compiler sm( ctx );

    if ( opts.count("file") ) {
      sm.compile_file( opts["file"].as<std::string>() );
    }
    else {
      for( int n=0; default_files[n] != NULL; ++n ) {
	std::string f( default_files[n] );
	if ( fs::exists( f ) ) {
	  sm.compile_file( f );
	  break;
	}
      }//for
    }

    if ( opts.count("targets") ) {
      typedef std::vector<std::string> svec_t;
      svec_t vec( opts["targets"].as<svec_t>() );
      //std::cout<<vec.size()<<std::endl;
      svec_t::iterator it( vec.begin() );
      for(; it != vec.end(); ++it) {
	smart::builtin::target tar( ctx.target( *it ) );
	tar.update( ctx );
      }
    }
    else {
      smart::builtin::target tar( ctx.default_goal() );
      if ( tar.is_null() ) return 0;
      tar.update( ctx );
    }
  }//try

  catch( const smart::parser_error & e ) {
    std::clog<<ctx.file()<<":"<<e.line()<<":"<<e.column()<<": "
	     <<e.what()<<std::endl;
  }//catch( parser-error )

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
