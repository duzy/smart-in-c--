/**                                                                 -*- c++ -*-
 *
 */

#include "../src/vm_types.hpp"
#include "../src/string_table.hpp"
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE( main )
{
  smart::string_table tab;
  {
    smart::string_table::entry ent1( tab.add("foobar") );
    smart::string_table::entry ent2( tab.add("foobar") );
    BOOST_CHECK( tab.size() == 1 );
    BOOST_CHECK( ent1.index.num == 0 );
    BOOST_CHECK( ent2.index.num == 0 );
  }
  {
    smart::string_table::entry ent1( tab.add("foobar2") );
    smart::string_table::entry ent2( tab.add("foobar2") );
    BOOST_CHECK( tab.size() == 2 );
    BOOST_CHECK( ent1.index.num == 1 );
    BOOST_CHECK( ent2.index.num == 1 );
  }
  {
    smart::string_table::index i1 = {0};
    smart::string_table::index i2 = {1};
    smart::string_table::entry ent1( tab.get(i1) );
    smart::string_table::entry ent2( tab.get(i2) );
    BOOST_CHECK( ent1.ptr != NULL );
    BOOST_CHECK( ent2.ptr != NULL );
    BOOST_CHECK( *ent1.ptr == "foobar" );
    BOOST_CHECK( *ent2.ptr == "foobar2" );
    BOOST_CHECK( ent1.index.num == 0 );
    BOOST_CHECK( ent2.index.num == 1 );
  }
  {
    smart::string_table::index i0 = {0};
    smart::vm::type_string s( tab.get(i0) );
    BOOST_CHECK( s.refcount() == -1 );
    BOOST_CHECK( std::string(s) == "foobar" );
  }
}
