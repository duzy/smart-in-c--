/**								-*- c++ -*-
 *
 */

//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_DEBUG_XML
#include "../src/context.hpp"
#include "../src/compiler.hpp"

int main( int argc, const char** argv )
{
  smart::context ctx;
  smart::compiler sm( ctx );
  sm.compile_file( "assignments.sm" );
  //sm.compile_file( "rules.sm" );
  return 0;
}
