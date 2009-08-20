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
    std::clog<<"s0: "<<std::string(s0)<<std::endl;
    std::clog<<"s1: "<<std::string(s1)<<std::endl;
    std::clog<<"s2: "<<std::string(s2)<<std::endl;
    std::clog<<"s3: "<<std::string(s3)<<std::endl;
    std::clog<<"refs: "<<s0.refcount()<<std::endl;
    assert( s0 == s1 );
    assert( s0 == s2 );
    assert( s0 == s3 );
    assert( std::string(s0) == std::string(s1) );
    assert( std::string(s0) == std::string(s2) );
    assert( std::string(s0) == std::string(s3) );
    assert( s0.refcount() == 4 );
  }
  {
    smart::vm::type_string s0( "foobar" );
    assert( s0.refcount() == 1 );
  }
  return 0;
}

