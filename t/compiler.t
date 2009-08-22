/**								-*- c++ -*-
 *
 */

//#define BOOST_SPIRIT_DEBUG
//#define BOOST_SPIRIT_DEBUG_XML
#include "../src/context.hpp"
#include "../src/compiler.hpp"

int main( int argc, const char** argv )
{
  smart::context ctx;
  {
    std::string code
      ( "##############\n"
	"N = n\n"
	"N$(N)N = nnn\n"
	"##############\n"
	"L1 = i1\\\n"
	"   i2\\\n"
	"i3   \\\n"
	"i4\n"
	"L2 := i1\\\n"
	"   i2\\\n"
	"i3   \\\n"
	"i4\n"
	"" );
    smart::compiler sm( ctx );
    sm.compile( code );
    smart::builtin::macro m1( ctx.macro("N") );
    smart::builtin::macro m2( ctx.macro("NnN") );
    assert( m1.name() == "N" );
    assert( m1.value() == "n" );
    assert( m2.name() == "NnN" );
    assert( m2.value() == "nnn" );
    assert( m1.origin() == smart::builtin::macro::origin_file );
    assert( m2.origin() == smart::builtin::macro::origin_file );
    assert( m1.flavor() == smart::builtin::macro::flavor_recursive );
    assert( m2.flavor() == smart::builtin::macro::flavor_recursive );

    smart::builtin::macro m3( ctx.macro("L1") );
    smart::builtin::macro m4( ctx.macro("L2") );
    assert( m3.name() == "L1" );
    assert( m3.value() == "i1 i2 i3    i4" );
    assert( m3.origin() == smart::builtin::macro::origin_file );
    assert( m3.flavor() == smart::builtin::macro::flavor_recursive );
    assert( m4.name() == "L2" );
    assert( m4.value() == "i1 i2 i3    i4" );
    assert( m4.origin() == smart::builtin::macro::origin_file );
    assert( m4.flavor() == smart::builtin::macro::flavor_simple );
  }

//   {
//     smart::context ct;
//     smart::compiler sm( ct );
//     sm.compile_file( "assignments.sm" );
//     //sm.compile_file( "rules.sm" );
//   }
  return 0;
}
