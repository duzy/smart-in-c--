/**                                                                 -*- c++ -*-
 *
 */

#include "../src/vm_types.hpp"
#include "../src/string_table.hpp"
#include <iostream>
#include <cassert>

int main(int argc, const char** argv )
{
  smart::string_table tab;
  {
    smart::string_table::entry ent1( tab.add("foobar") );
    smart::string_table::entry ent2( tab.add("foobar") );
    assert( tab.size() == 1 );
    assert( ent1.index.num == 0 );
    assert( ent2.index.num == 0 );
  }
  {
    smart::string_table::entry ent1( tab.add("foobar2") );
    smart::string_table::entry ent2( tab.add("foobar2") );
    assert( tab.size() == 2 );
    assert( ent1.index.num == 1 );
    assert( ent2.index.num == 1 );
  }
  {
    smart::string_table::index i1 = {0};
    smart::string_table::index i2 = {1};
    smart::string_table::entry ent1( tab.get(i1) );
    smart::string_table::entry ent2( tab.get(i2) );
    assert( ent1.ptr != NULL );
    assert( ent2.ptr != NULL );
    assert( *ent1.ptr == "foobar" );
    assert( *ent2.ptr == "foobar2" );
    assert( ent1.index.num == 0 );
    assert( ent2.index.num == 1 );
  }
  {
    smart::string_table::index i0 = {0};
    smart::vm::type_string s( tab.get(i0) );
    assert( s.refcount() == -1 );
    assert( std::string(s) == "foobar" );
  }
  return 0;
}
