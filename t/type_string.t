/**                                                                 -*- c++ -*-
 *
 */

#include "../src/vm_types.hpp"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cassert>

//int main(int argc, const char** argv )
BOOST_AUTO_TEST_CASE( main )
{
  {
    smart::vm::type_string s0( "foobar" );
    smart::vm::type_string s1( s0 );
    smart::vm::type_string s2( s0 );
    smart::vm::type_string s3( s1 );
//     std::clog<<"s0: "<<std::string(s0)<<std::endl;
//     std::clog<<"s1: "<<std::string(s1)<<std::endl;
//     std::clog<<"s2: "<<std::string(s2)<<std::endl;
//     std::clog<<"s3: "<<std::string(s3)<<std::endl;
//     std::clog<<"refs: "<<s0.refcount()<<std::endl;
    BOOST_CHECK( s0 == s1 );
    BOOST_CHECK( s0 == s2 );
    BOOST_CHECK( s0 == s3 );
    BOOST_CHECK( std::string(s0) == "foobar" );
    BOOST_CHECK( std::string(s0) == std::string(s1) );
    BOOST_CHECK( std::string(s0) == std::string(s2) );
    BOOST_CHECK( std::string(s0) == std::string(s3) );
    BOOST_CHECK( s0.refcount() == 4 );
  }
  {
    smart::vm::type_string s0( "foobar" );
    smart::vm::type_string s1( "foobar" );
    BOOST_CHECK( s0.refcount() == 1 );
    BOOST_CHECK( s1.refcount() == 1 );
  }
  {// operator =
    smart::vm::type_string s0( "foo" );
    smart::vm::type_string s1( "bar" );
    BOOST_CHECK( s0.refcount() == 1 );
    BOOST_CHECK( s1.refcount() == 1 );
    BOOST_CHECK( s0 == "foo" );
    BOOST_CHECK( s1 == "bar" );
    s0 = "foo-";
    BOOST_CHECK( s0 == "foo-" );
    BOOST_CHECK( s0.refcount() == 1 );
    
    smart::vm::type_string s2( s1 );
    BOOST_CHECK( s1.refcount() == 2 );
    BOOST_CHECK( s1.refcount() == s2.refcount() );
    BOOST_CHECK( s1 == "bar" );
    BOOST_CHECK( s1 == s2 );
    BOOST_CHECK( s2 == "bar" );
    BOOST_CHECK( std::string(s1) == "bar" );
    BOOST_CHECK( std::string(s2) == "bar" );
    s2 = "bar-";
    BOOST_CHECK( s1 == "bar" );
    BOOST_CHECK( s2 == "bar-" );
    BOOST_CHECK( std::string(s1) == "bar" );
    BOOST_CHECK( std::string(s2) == "bar-" );
    BOOST_CHECK( s1.refcount() == 1 );
    BOOST_CHECK( s2.refcount() == 1 );
    BOOST_CHECK( s1 != s2 );
  }
  {// operator +=
    smart::vm::type_string s0( "foo" );
    smart::vm::type_string s1( "bar" );
    smart::vm::type_string s( s0 );
    BOOST_CHECK( s0.refcount() == 2 );
    BOOST_CHECK( s1.refcount() == 1 );
    BOOST_CHECK( s.refcount() == s0.refcount() );
    BOOST_CHECK( s == s0 );
    BOOST_CHECK( std::string(s) == "foo" );
    s += s1;
    BOOST_CHECK( s.refcount() == 1 );
    BOOST_CHECK( s0.refcount() == 1 );
    BOOST_CHECK( s1.refcount() == 1 );
    BOOST_CHECK( std::string(s) == "foobar" );
    BOOST_CHECK( std::string(s0) == "foo" );
    BOOST_CHECK( std::string(s1) == "bar" );
    //std::clog<<std::string(s)<<std::endl;
    s += "-";
    BOOST_CHECK( s.refcount() == 1 );
    BOOST_CHECK( std::string(s) == "foobar-" );
    smart::vm::type_string s2( s );
    BOOST_CHECK( s2 == s );
    BOOST_CHECK( s.refcount() == 2 );
    BOOST_CHECK( s.refcount() == s2.refcount() );
    BOOST_CHECK( std::string(s2) == "foobar-" );
    s2 += "-";
    BOOST_CHECK( s != s2 );
    BOOST_CHECK( s.refcount() == 1 );
    BOOST_CHECK( s2.refcount() == 1 );
    BOOST_CHECK( std::string(s) == "foobar-" );
    BOOST_CHECK( std::string(s2) == "foobar--" );
  }
  {// operator +
    smart::vm::type_string s0( "foo" );
    smart::vm::type_string s1( "bar" );
    smart::vm::type_string s( s0 + s1 );
    BOOST_CHECK( s0.refcount() == 1 );
    BOOST_CHECK( s1.refcount() == 1 );
    BOOST_CHECK( s.refcount() == 1 );
    BOOST_CHECK( std::string(s0) == "foo" );
    BOOST_CHECK( std::string(s1) == "bar" );
    BOOST_CHECK( std::string(s) == "foobar" );
    std::string t( "-" );
    s = s + t;
    BOOST_CHECK( std::string(s) == "foobar-" );
    s = t + s;
    BOOST_CHECK( std::string(s) == "-foobar-" );
    //std::clog<<s<<std::endl;
  }
  //return 0;
}

