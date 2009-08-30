/**								-*- c++ -*-
 *
 */

//#define BOOST_SPIRIT_DEBUG
//#define BOOST_SPIRIT_DEBUG_XML
#include "../src/context.hpp"
#include "../src/compiler.hpp"
#include "../src/string_table.hpp"
#include "../src/exceptions.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/operations.hpp>

#include <fstream>
#include <iostream>

namespace fs = boost::filesystem;

BOOST_AUTO_TEST_CASE( assignments )
{
  smart::context ctx;
  {
    std::string code
      ( "##############\n"
	"N = n\n"
	"N$(N)N = nnn\n"
	"##############\n"
	"L1 = i1\\\n"
	"   i2\\\n"
	"i3   \\\n"
	"i4\n"
	"L2 := i1\\\n"
	"   i2\\\n"
	"i3   \\\n"
	"i4\n"
	"##############\n"
	"" );

    smart::compiler sm( ctx );
    sm.compile( code );
    BOOST_CHECK( ctx.stable()->size() == 10 );
    //BOOST_CHECK( ctx.stable()->get("NnN").ptr != NULL );
    BOOST_CHECK( ctx.stable()->get("N").ptr != NULL );
    BOOST_CHECK( ctx.stable()->get("L1").ptr != NULL );
    BOOST_CHECK( ctx.stable()->get("L2").ptr != NULL );
    BOOST_CHECK( ctx.stable()->get("i1").ptr != NULL );
    BOOST_CHECK( ctx.stable()->get("i2").ptr != NULL );
    BOOST_CHECK( ctx.stable()->get("i3   ").ptr != NULL );
    BOOST_CHECK( ctx.stable()->get("i4").ptr != NULL );
    //BOOST_CHECK( *ctx.stable()->get("NnN").ptr == "NnN" );
    BOOST_CHECK( *ctx.stable()->get("N").ptr == "N" );
    BOOST_CHECK( *ctx.stable()->get("L1").ptr == "L1" );
    BOOST_CHECK( *ctx.stable()->get("L2").ptr == "L2" );
    BOOST_CHECK( *ctx.stable()->get("i1").ptr == "i1" );
    BOOST_CHECK( *ctx.stable()->get("i2").ptr == "i2" );
    BOOST_CHECK( *ctx.stable()->get("i3   ").ptr == "i3   " );
    BOOST_CHECK( *ctx.stable()->get("i4").ptr == "i4" );

    smart::builtin::macro m1( ctx.macro("N") );
    smart::builtin::macro m2( ctx.macro("NnN") );
    BOOST_CHECK( m1.name() == "N" );
    BOOST_CHECK( m1.value() == "n" );
    BOOST_CHECK( m2.name() == "NnN" );
    BOOST_CHECK( m2.value() == "nnn" );
    BOOST_CHECK( m1.origin() == smart::builtin::macro::origin_file );
    BOOST_CHECK( m2.origin() == smart::builtin::macro::origin_file );
    BOOST_CHECK( m1.flavor() == smart::builtin::macro::flavor_recursive );
    BOOST_CHECK( m2.flavor() == smart::builtin::macro::flavor_recursive );

    smart::builtin::macro m3( ctx.macro("L1") );
    smart::builtin::macro m4( ctx.macro("L2") );
    BOOST_CHECK( m3.name() == "L1" );
    BOOST_CHECK( m3.value() == "i1 i2 i3    i4" );
    BOOST_CHECK( m3.origin() == smart::builtin::macro::origin_file );
    BOOST_CHECK( m3.flavor() == smart::builtin::macro::flavor_recursive );
    BOOST_CHECK( m4.name() == "L2" );
    BOOST_CHECK( m4.value() == "i1 i2 i3    i4" );
    BOOST_CHECK( m4.origin() == smart::builtin::macro::origin_file );
    BOOST_CHECK( m4.flavor() == smart::builtin::macro::flavor_simple );
  }
  {
    {
      smart::builtin::macro m0( ctx.macro("N2") );
      BOOST_CHECK( m0.flavor() == smart::builtin::macro::flavor_undefined );
      BOOST_CHECK( m0.origin() == smart::builtin::macro::origin_undefined );
      BOOST_CHECK( m0.name() == "N2" );
      BOOST_CHECK( m0.value() == "" );
    }

    std::string code
      ( "##############\n"
	"N ?= xxx\n"
	"N2 ?= n2\n"
	"##############\n"
	"v = v\n"
	"V = $(v)\n"
	"V1 = $(V)$(V)\n"
	"V2 := $(V)$(V)\n"
	"" );
    smart::compiler sm( ctx );
    sm.compile( code );
    {
      smart::builtin::macro m1( ctx.macro("N") );
      smart::builtin::macro m2( ctx.macro("N2") );
      BOOST_CHECK( m1.name() == "N" );
      BOOST_CHECK( m1.value() == "n" );
      BOOST_CHECK( m1.origin() == smart::builtin::macro::origin_file );
      BOOST_CHECK( m1.flavor() == smart::builtin::macro::flavor_recursive );
      BOOST_CHECK( m2.name() == "N2" );
      BOOST_CHECK( m2.value() == "n2" );
      BOOST_CHECK( m2.origin() == smart::builtin::macro::origin_file );
      BOOST_CHECK( m2.flavor() == smart::builtin::macro::flavor_recursive );
    }
    {
      smart::builtin::macro v( ctx.macro("v") );
      smart::builtin::macro m1( ctx.macro("V1") );
      smart::builtin::macro m2( ctx.macro("V2") );
      //std::clog<<m2.value()<<std::endl;
      BOOST_CHECK( v.name() == "v" );
      BOOST_CHECK( v.value() == "v" );
      BOOST_CHECK( m1.flavor() == smart::builtin::macro::flavor_recursive );
      BOOST_CHECK( m1.value() == "$(V)$(V)" );
      BOOST_CHECK( m2.flavor() == smart::builtin::macro::flavor_simple );
      BOOST_CHECK( m2.value() == "vv" );
    }
  }
  {
    std::string code
      ( "##############\n"
	"V1 += $(V)\n"
	"V2 += $(V)\n"
	"" );
    smart::compiler sm( ctx );
    sm.compile( code );
    {
      smart::builtin::macro m1( ctx.macro("V1") );
      smart::builtin::macro m2( ctx.macro("V2") );
      BOOST_CHECK( m1.flavor() == smart::builtin::macro::flavor_recursive );
      BOOST_CHECK( m1.value() == "$(V)$(V)$(V)" );
      BOOST_CHECK( m2.flavor() == smart::builtin::macro::flavor_simple );
      BOOST_CHECK( m2.value() == "vvv" );
    }
  }
  {
    std::string code
      ( "##############\n"
	"VV = a b c	d 	 e    f\n"
	"fun = $1;$2\n"
	"CALL := $(call fun,abc,def)\n"
	"PAT1 := $(VV:%=%.o)\n"
	"PAT2 := $(patsubst %,%.o,$(VV))\n"
	"" );
    smart::compiler sm( ctx );
    sm.compile( code );
    {
      smart::builtin::macro m0( ctx.macro("fun") );
      smart::builtin::macro m1( ctx.macro("CALL") );
      smart::builtin::macro m2( ctx.macro("PAT1") );
      smart::builtin::macro m3( ctx.macro("PAT2") );
      //std::clog<<"m2: "<<m2.value()<<std::endl;
      BOOST_CHECK( m0.flavor() == smart::builtin::macro::flavor_recursive );
      BOOST_CHECK( m0.value() == "$1;$2" );
      BOOST_CHECK( m1.flavor() == smart::builtin::macro::flavor_simple );
      BOOST_CHECK( m1.value() == "abc;def" );
      BOOST_CHECK( m2.flavor() == smart::builtin::macro::flavor_simple );
      BOOST_CHECK( m2.value() == "a.o b.o c.o d.o e.o f.o" );
      BOOST_CHECK( m3.flavor() == smart::builtin::macro::flavor_simple );
      BOOST_CHECK( m3.value() == "a.o b.o c.o d.o e.o f.o" );
    }
  }
}//test_assignments()

BOOST_AUTO_TEST_CASE( function_call )
{
  smart::context ctx;
  {
    std::string code
      ( "##############\n"
	"$(info informative text)\n"
	"$(info informative text	 2,)\n"
	"$(warning warning text)\n"
	"$(error error text)\n"
	"" );
    smart::compiler sm( ctx );
    sm.compile( code );
  }
  {// if, or, and
    std::string code
      ( "##############\n"
	"VV1 := \n"
	"RES1 := $(if $(VV1),vv,empty)\n"
	"VV2 := vv\n"
	"RES2 := $(if $(VV2),vv,empty)\n"
	"RES3 := $(or $(VV1),$(VV2),xx)\n"
	"RES4 := $(and $(VV1),$(VV2),xx)\n"
	"RES5 := $(and $(VV2),xx,yy)\n"
	"" );
    smart::compiler sm( ctx );
    sm.compile( code );
    {
      smart::builtin::macro m1( ctx.macro("RES1") );
      smart::builtin::macro m2( ctx.macro("RES2") );
      smart::builtin::macro m3( ctx.macro("RES3") );
      smart::builtin::macro m4( ctx.macro("RES4") );
      smart::builtin::macro m5( ctx.macro("RES5") );
      //std::clog<<"m1: "<<m1.value()<<std::endl;
      //std::clog<<"m2: "<<m2.value()<<std::endl;
      //std::clog<<"m5: "<<m5.value()<<std::endl;
      BOOST_CHECK( m1.flavor() == smart::builtin::macro::flavor_simple );
      BOOST_CHECK( m1.value() == "empty" );
      BOOST_CHECK( m2.value() == "vv" );
      BOOST_CHECK( m3.value() == "vv" );
      BOOST_CHECK( m4.value() == "" );
      BOOST_CHECK( m5.value() == "yy" );
    }
  }
  {// foreach
    std::string code
      ( "##############\n"
	"VV = a b c	d 	 e    f\n"
	"RES := $(foreach v,$(VV),$v.o)\n"
	"" );
    smart::compiler sm( ctx );
    sm.compile( code );
    {
      smart::builtin::macro m0( ctx.macro("VV") );
      smart::builtin::macro m1( ctx.macro("RES") );
      //std::clog<<"m1: "<<m1.value()<<std::endl;
      BOOST_CHECK( m1.flavor() == smart::builtin::macro::flavor_simple );
      BOOST_CHECK( m1.value() == "a.o b.o c.o d.o e.o f.o" );
    }
  }
}//test_function_call()

BOOST_AUTO_TEST_CASE( make_rules )
{
  smart::context ctx;
  smart::compiler sm( ctx );

  std::string code
    ( "##############\n"
      "foobar: foo bar\n"
      "\t@echo command line 1\n"
      "\t@echo command line 2\n"
      "xx yy: x\n"
      "\t@echo command 1\n"
      "\t@echo command 2\n"
      "xx: y\n"
      "xx:\r"
      "\t@echo command 3\n"
      "" );
  sm.compile( code );

  smart::vm::type_string name( "foobar" );
  smart::builtin::target foobar( ctx.target(name) );
  //std::clog<<foobar<<std::endl;
  //std::clog<<foobar.rules().size()<<std::endl;
  BOOST_CHECK( foobar.object() == "foobar" );
  BOOST_CHECK( foobar.refcount() == 3/*2*/ ); //!< default goal
  BOOST_CHECK( foobar.rule().prerequisites().size() == 2 );
  BOOST_CHECK( foobar.rule().prerequisites()[0].object() == "foo" );
  BOOST_CHECK( foobar.rule().prerequisites()[1].object() == "bar" );
  BOOST_CHECK( foobar.rule().commands().size() == 2 );
  BOOST_CHECK( foobar.rule().commands()[0] == "@echo command line 1" );
  BOOST_CHECK( foobar.rule().commands()[1] == "@echo command line 2" );

  name = "foo";
  smart::builtin::target foo( ctx.target(name) );
  //std::clog<<foo.refcount()<<std::endl;
  BOOST_CHECK( foo.object() == "foo" );
  BOOST_CHECK( foo.refcount() == 3 );
  BOOST_CHECK( foo.rule().prerequisites().size() == 0 );
  BOOST_CHECK( foo.rule().commands().size() == 0 );
  BOOST_CHECK( foo.rule().empty() );

  name = "bar";
  smart::builtin::target bar( ctx.target(name) );
  //std::clog<<bar.refcount()<<std::endl;
  BOOST_CHECK( bar.object() == "bar" );
  BOOST_CHECK( bar.refcount() == 3 );
  BOOST_CHECK( bar.rule().prerequisites().size() == 0 );
  BOOST_CHECK( bar.rule().empty() );

  name = "xx";
  smart::builtin::target xx( ctx.target(name) );
  //std::clog<<xx.rule().commands().size()<<std::endl;
  //std::clog<<xx.rule().prerequisites().size()<<std::endl;
  BOOST_CHECK( xx.object() == "xx" );
  BOOST_CHECK( xx.refcount() == 2 );
  BOOST_CHECK( xx.rule().prerequisites().size() == 2 );
  BOOST_CHECK( xx.rule().prerequisites()[0].object() == "x" );
  BOOST_CHECK( xx.rule().prerequisites()[1].object() == "y" );
  BOOST_CHECK( xx.rule().commands().size() == 1 );
  BOOST_CHECK( xx.rule().commands()[0] == "@echo command 3" );
  BOOST_CHECK( xx.rule().empty() == false );

  name = "yy";
  smart::builtin::target yy( ctx.target(name) );
  //std::clog<<yy.rule().commands().size()<<std::endl;
  //std::clog<<yy.rule().prerequisites().size()<<std::endl;
  BOOST_CHECK( yy.object() == "yy" );
  BOOST_CHECK( yy.refcount() == 2 );
  BOOST_CHECK( yy.rule().prerequisites().size() == 1 );
  BOOST_CHECK( yy.rule().prerequisites()[0].object() == "x" );
  BOOST_CHECK( yy.rule().commands().size() == 2 );
  BOOST_CHECK( yy.rule().commands()[0] == "@echo command 1" );
  BOOST_CHECK( yy.rule().commands()[1] == "@echo command 2" );
  BOOST_CHECK( yy.rule().empty() == false );

  code =
    "##############\n"
    "foo: \n"
    "\t@echo command 1\n"
    "\t@echo command 2\n"
    "bar: x\n"
    "\t@echo command 1\n"
    "\t@echo command 2\n"
    "\t@echo command 3\n"
    "x: \n"
    "";
  sm.compile( code );
  BOOST_CHECK( foo.rule().commands().size() == 2 );
  BOOST_CHECK( bar.rule().commands().size() == 3 );

  if ( fs::exists("foobar") ) fs::remove("foobar");
  if ( fs::exists("foo") ) fs::remove("foo");
  if ( fs::exists("bar") ) fs::remove("bar");
  try {
    smart::builtin::target::update_result uc( foobar.update( ctx ) );
    //std::clog<<"updated: "<<uc<<std::endl;
    BOOST_CHECK( uc.count_updated == 0 );
    BOOST_CHECK( uc.count_executed == 3 );
    BOOST_CHECK( uc.count_newer == 0 );
  }
  catch( const smart::make_error & e ) {
    std::clog<<e.what()<<std::endl;
  }
}

BOOST_AUTO_TEST_CASE( update_targets )
{
  smart::context ctx;
  smart::compiler sm( ctx );

  std::string code
    ( "##############\n"
      "foobar: foo bar\n"
      "\tcat $< > $@\n"
      "\tcat bar >> foobar\n"
      "foo: \t\n"
      "\techo foo > $@\n"
      "bar:\n"
      "\techo $@ > bar\n"
      //"\ttyn"
      "" );
  sm.compile( code );

  if ( fs::exists("foobar") ) fs::remove("foobar");
  if ( fs::exists("foo") ) fs::remove("foo");
  if ( fs::exists("bar") ) fs::remove("bar");
  BOOST_CHECK( !fs::exists("foobar") );
  BOOST_CHECK( !fs::exists("foo") );
  BOOST_CHECK( !fs::exists("bar") );

  smart::vm::type_string name( "foobar" );
  smart::builtin::target foobar( ctx.target(name) );
  try {
    smart::builtin::target::update_result uc( foobar.update( ctx ) );
    BOOST_CHECK( uc.count_updated == 3 );
    BOOST_CHECK( uc.count_executed == 3 );
    BOOST_CHECK( uc.count_newer == 2 );
  }
  catch( const smart::make_error & e ) { std::clog<<e.what()<<std::endl; }
  //catch( const smart::runtime_error & e ) { std::clog<<e.what()<<std::endl; }

  name = "foo"; smart::builtin::target foo( ctx.target(name) );
  name = "bar"; smart::builtin::target bar( ctx.target(name) );
  BOOST_CHECK( foobar.last_write_time() != 0 );
  BOOST_CHECK( foo.last_write_time() != 0 );
  BOOST_CHECK( bar.last_write_time() != 0 );
  
  BOOST_CHECK( fs::exists("foobar") );
  BOOST_CHECK( fs::exists("foo") );
  BOOST_CHECK( fs::exists("bar") );

  {
    std::string s;
    std::ifstream ifs("foobar");
    std::istream_iterator<std::string::value_type> it( ifs ), end;
    std::copy( it, end, std::back_inserter(s) );
    BOOST_CHECK( s == "foobar" );
  }
  {
    std::string s;
    std::ifstream ifs("foo");
    std::istream_iterator<std::string::value_type> it( ifs ), end;
    std::copy( it, end, std::back_inserter(s) );
    BOOST_CHECK( s == "foo" );
  }
  {
    std::string s;
    std::ifstream ifs("bar");
    std::istream_iterator<std::string::value_type> it( ifs ), end;
    std::copy( it, end, std::back_inserter(s) );
    BOOST_CHECK( s == "bar" );
  }

  std::time_t t1( foobar.last_write_time() );
  std::time_t t2( foo.last_write_time() );
  std::time_t t3( bar.last_write_time() );
  ::sleep( 0.5/*1*/ );
  try {
    smart::builtin::target::update_result uc2( foobar.update( ctx ) );
    BOOST_CHECK( uc2.count_updated == 0 );
    BOOST_CHECK( uc2.count_executed == 0 );
    BOOST_CHECK( uc2.count_newer == 0 );
  }
  catch( const smart::make_error & e ) { std::clog<<e.what()<<std::endl; }
  BOOST_CHECK( t1 == foobar.last_write_time() );
  BOOST_CHECK( t2 == foo.last_write_time() );
  BOOST_CHECK( t3 == bar.last_write_time() );

  fs::remove("foobar");
  fs::remove("foo");
  fs::remove("bar");
}

