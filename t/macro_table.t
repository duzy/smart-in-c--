/**                                                                 -*- c++ -*-
 *
 *
 */

#include "../src/macro_table.hpp"
#include <iostream>

int main(int argc, const char** argv)
{
  smart::macro_table tab;
  smart::vm::type_string name( "FOOBAR" );
  smart::vm::type_string value( "foobar" );
  {
    smart::builtin::macro m( tab.map(name) );
    m.set_value( value );
    assert( m.name() == name );
    assert( m.value() == value );
  }
  {
    smart::builtin::macro m( tab.get(name) );
    assert( m.name() == name );
    assert( m.value() == value );
  }
  {
    smart::builtin::macro m( tab.map(name) );
    assert( m.name() == name );
    assert( m.value() == value );
  }

  smart::builtin::macro m1( tab.map(name) );
  {
    smart::builtin::macro m2( tab.map(name) );
    smart::builtin::macro m3( tab.get(name) );
    assert( m1.name() == name );
    assert( m2.name() == name );
    assert( m3.name() == name );
    assert( m1.value() == value );
    assert( m2.value() == value );
    assert( m3.value() == value );
  }

  value = "foobar-";
  {
    smart::builtin::macro m( tab.map(name) );
    assert( m.name() == name );
    assert( m.value() == smart::vm::type_string("foobar") );
    m.set_value( value );
    assert( m.value() == value );
    assert( m1.value() == smart::vm::type_string("foobar-") );
  }
  {
    smart::builtin::macro m( tab.map(name) );
    assert( m.name() == name );
    assert( m.value() == value );
  }
  {
    smart::builtin::macro m( tab.get(name) );
    assert( m.name() == name );
    assert( m.value() == value );
  }
  return 0;
}
