/**                                                                 -*- c++ -*-
 *
 *
 */

#include "../src/macro_table.hpp"
#include <boost/test/unit_test.hpp>
#include <iostream>

//int main(int argc, const char** argv)
BOOST_AUTO_TEST_CASE( main )
{
  smart::macro_table tab;
  smart::vm::type_string name( "FOOBAR" );
  smart::vm::type_string value( "foobar" );
  {
    smart::builtin::macro m( tab.map(name) );
    m.set_value( value );
    BOOST_CHECK( m.name() == name );
    BOOST_CHECK( m.value() == value );
  }
  {
    smart::builtin::macro m( tab.get(name) );
    BOOST_CHECK( m.name() == name );
    BOOST_CHECK( m.value() == value );
  }
  {
    smart::builtin::macro m( tab.map(name) );
    BOOST_CHECK( m.name() == name );
    BOOST_CHECK( m.value() == value );
  }

  smart::builtin::macro m1( tab.map(name) );
  {
    smart::builtin::macro m2( tab.map(name) );
    smart::builtin::macro m3( tab.get(name) );
    BOOST_CHECK( m1.name() == name );
    BOOST_CHECK( m2.name() == name );
    BOOST_CHECK( m3.name() == name );
    BOOST_CHECK( m1.value() == value );
    BOOST_CHECK( m2.value() == value );
    BOOST_CHECK( m3.value() == value );
  }

  value = "foobar-";
  {
    smart::builtin::macro m( tab.map(name) );
    BOOST_CHECK( m.name() == name );
    BOOST_CHECK( m.value() == smart::vm::type_string("foobar") );
    m.set_value( value );
    BOOST_CHECK( m.value() == value );
    BOOST_CHECK( m1.value() == smart::vm::type_string("foobar-") );
  }
  {
    smart::builtin::macro m( tab.map(name) );
    BOOST_CHECK( m.name() == name );
    BOOST_CHECK( m.value() == value );
  }
  {
    smart::builtin::macro m( tab.get(name) );
    BOOST_CHECK( m.name() == name );
    BOOST_CHECK( m.value() == value );
  }
  //return 0;
}
