/**								-*- c++ -*-
 *
 */

//#define BOOST_SPIRIT_DEBUG
//#define BOOST_SPIRIT_DEBUG_XML
#include "../src/context.hpp"
#include "../src/compiler.hpp"
#include "../src/string_table.hpp"

void test_assignments()
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
	"##############\n"
	"" );

    smart::compiler sm( ctx );
    sm.compile( code );
    assert( ctx.stable()->size() == 10 );
    //assert( ctx.stable()->get("NnN").ptr != NULL );
    assert( ctx.stable()->get("N").ptr != NULL );
    assert( ctx.stable()->get("L1").ptr != NULL );
    assert( ctx.stable()->get("L2").ptr != NULL );
    assert( ctx.stable()->get("i1").ptr != NULL );
    assert( ctx.stable()->get("i2").ptr != NULL );
    assert( ctx.stable()->get("i3   ").ptr != NULL );
    assert( ctx.stable()->get("i4").ptr != NULL );
    //assert( *ctx.stable()->get("NnN").ptr == "NnN" );
    assert( *ctx.stable()->get("N").ptr == "N" );
    assert( *ctx.stable()->get("L1").ptr == "L1" );
    assert( *ctx.stable()->get("L2").ptr == "L2" );
    assert( *ctx.stable()->get("i1").ptr == "i1" );
    assert( *ctx.stable()->get("i2").ptr == "i2" );
    assert( *ctx.stable()->get("i3   ").ptr == "i3   " );
    assert( *ctx.stable()->get("i4").ptr == "i4" );

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
  {
    {
      smart::builtin::macro m0( ctx.macro("N2") );
      assert( m0.flavor() == smart::builtin::macro::flavor_undefined );
      assert( m0.origin() == smart::builtin::macro::origin_undefined );
      assert( m0.name() == "N2" );
      assert( m0.value() == "" );
    }

    std::string code
      ( "##############\n"
	"N ?= xxx\n"
	"N2 ?= n2\n"
	"##############\n"
	"V = v\n"
	"V1 = $(V)$(V)\n"
	"V2 := $(V)$(V)\n"
	"" );
    smart::compiler sm( ctx );
    sm.compile( code );
    {
      smart::builtin::macro m1( ctx.macro("N") );
      smart::builtin::macro m2( ctx.macro("N2") );
      assert( m1.name() == "N" );
      assert( m1.value() == "n" );
      assert( m1.origin() == smart::builtin::macro::origin_file );
      assert( m1.flavor() == smart::builtin::macro::flavor_recursive );
      assert( m2.name() == "N2" );
      assert( m2.value() == "n2" );
      assert( m2.origin() == smart::builtin::macro::origin_file );
      assert( m2.flavor() == smart::builtin::macro::flavor_recursive );
    }
    {
      smart::builtin::macro m1( ctx.macro("V1") );
      smart::builtin::macro m2( ctx.macro("V2") );
      assert( m1.flavor() == smart::builtin::macro::flavor_recursive );
      assert( m1.value() == "$(V)$(V)" );
      assert( m2.flavor() == smart::builtin::macro::flavor_simple );
      assert( m2.value() == "vv" );
    }
  }
  {
    std::string code
      ( "##############\n"
	"V1 += $(V)\n"
	"V2 += $(V)\n"
	"" );
    smart::compiler sm( ctx );
    sm.compile( code );
    {
      smart::builtin::macro m1( ctx.macro("V1") );
      smart::builtin::macro m2( ctx.macro("V2") );
      assert( m1.flavor() == smart::builtin::macro::flavor_recursive );
      assert( m1.value() == "$(V)$(V)$(V)" );
      assert( m2.flavor() == smart::builtin::macro::flavor_simple );
      assert( m2.value() == "vvv" );
    }
  }
}


int main( int argc, const char** argv )
{
//   {
//     smart::context ct;
//     smart::compiler sm( ct );
//     sm.compile_file( "assignments.sm" );
//     //sm.compile_file( "rules.sm" );
//   }

  test_assignments();
  return 0;
}
