/**								-*- c++ -*-
 *
 */

//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_DEBUG_XML
#include "../src/context.hpp"
#include "../src/compiler.hpp"

// #include "../src/context.cpp"
// #include "../src/compiler.cpp"
// #include "../src/string_table.cpp"
// #include "../src/vm_types.cpp"

int main( int argc, const char** argv )
{
  smart::context ctx;
  smart::compiler sm( ctx );
  sm.compile_file( "assignments.sm" );
  //sm.compile_file( "rules.sm" );
  return 0;
}
