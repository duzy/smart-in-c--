/**                                                                 -*- c++ -*-
 *
 */

#include "../src/vm_types.hpp"
#include <iostream>
#include <cassert>

int main(int argc, const char** argv )
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
    assert( s0 == s1 );
    assert( s0 == s2 );
    assert( s0 == s3 );
    assert( std::string(s0) == "foobar" );
    assert( std::string(s0) == std::string(s1) );
    assert( std::string(s0) == std::string(s2) );
    assert( std::string(s0) == std::string(s3) );
    assert( s0.refcount() == 4 );
  }
  {
    smart::vm::type_string s0( "foobar" );
    smart::vm::type_string s1( "foobar" );
    assert( s0.refcount() == 1 );
    assert( s1.refcount() == 1 );
  }
  {// operator =
    smart::vm::type_string s0( "foo" );
    smart::vm::type_string s1( "bar" );
    assert( s0.refcount() == 1 );
    assert( s1.refcount() == 1 );
    assert( s0 == "foo" );
    assert( s1 == "bar" );
    s0 = "foo-";
    assert( s0 == "foo-" );
    assert( s0.refcount() == 1 );
    
    smart::vm::type_string s2( s1 );
    assert( s1.refcount() == 2 );
    assert( s1.refcount() == s2.refcount() );
    assert( s1 == "bar" );
    assert( s1 == s2 );
    assert( s2 == "bar" );
    assert( std::string(s1) == "bar" );
    assert( std::string(s2) == "bar" );
    s2 = "bar-";
    assert( s1 == "bar" );
    assert( s2 == "bar-" );
    assert( std::string(s1) == "bar" );
    assert( std::string(s2) == "bar-" );
    assert( s1.refcount() == 1 );
    assert( s2.refcount() == 1 );
    assert( s1 != s2 );
  }
  {// operator +=
    smart::vm::type_string s0( "foo" );
    smart::vm::type_string s1( "bar" );
    smart::vm::type_string s( s0 );
    assert( s0.refcount() == 2 );
    assert( s1.refcount() == 1 );
    assert( s.refcount() == s0.refcount() );
    assert( s == s0 );
    assert( std::string(s) == "foo" );
    s += s1;
    assert( s.refcount() == 1 );
    assert( s0.refcount() == 1 );
    assert( s1.refcount() == 1 );
    assert( std::string(s) == "foobar" );
    assert( std::string(s0) == "foo" );
    assert( std::string(s1) == "bar" );
    //std::clog<<std::string(s)<<std::endl;
    s += "-";
    assert( s.refcount() == 1 );
    assert( std::string(s) == "foobar-" );
    smart::vm::type_string s2( s );
    assert( s2 == s );
    assert( s.refcount() == 2 );
    assert( s.refcount() == s2.refcount() );
    assert( std::string(s2) == "foobar-" );
    s2 += "-";
    assert( s != s2 );
    assert( s.refcount() == 1 );
    assert( s2.refcount() == 1 );
    assert( std::string(s) == "foobar-" );
    assert( std::string(s2) == "foobar--" );
  }
  {// operator +
    smart::vm::type_string s0( "foo" );
    smart::vm::type_string s1( "bar" );
    smart::vm::type_string s( s0 + s1 );
    assert( s0.refcount() == 1 );
    assert( s1.refcount() == 1 );
    assert( s.refcount() == 1 );
    assert( std::string(s0) == "foo" );
    assert( std::string(s1) == "bar" );
    assert( std::string(s) == "foobar" );
    std::string t( "-" );
    s = s + t;
    assert( std::string(s) == "foobar-" );
    s = t + s;
    assert( std::string(s) == "-foobar-" );
    //std::clog<<s<<std::endl;
  }
  return 0;
}

