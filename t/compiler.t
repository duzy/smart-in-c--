/**								-*- c++ -*-
 *
 */

#define BOOST_SPIRIT_DEBUG
#include "../src/context.hpp"
#include "../src/compiler.hpp"

#include "../src/context.cpp"
#include "../src/compiler.cpp"

int main( int argc, const char** argv )
{
  smart::context ctx;
  smart::compiler sm( ctx );
  sm.compile_file( "rules.sm" );
  return 0;
}
