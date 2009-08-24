#include "builtins.hpp"
#include "context.hpp"
#include "macro_table.hpp"
#include "frame.hpp"
#include "expand.hpp"
#include <iostream>
namespace smart
{
  namespace builtin
  {

    void noop( context & ctx )
    {
    }

    void subst( context & ctx )
    {
    }

    void patsubst( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 4 ) {
	f[0] = vm::type_string();
	return;
      }

      builtin::pattern pat0( expand(ctx, f[1]) );
      builtin::pattern pat1( expand(ctx, f[2]) );
      f[0] = pat0.convert( pat1, expand(ctx, f[3]) );
    }

    void strip( context & ctx )
    {
    }

    void findstring( context & ctx )
    {
    }

    void filter( context & ctx )
    {
    }

    void filter_out( context & ctx )
    {
    }

    void sort( context & ctx )
    {
    }

    void word( context & ctx )
    {
    }

    void wordlist( context & ctx )
    {
    }

    void firstword( context & ctx )
    {
    }

    void lastword( context & ctx )
    {
    }

    /**
     *  @brief Expand macro with args.
     */
    void call( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 1 ) {
	f[0] = vm::type_string();
	return;
      }

      vm::type_string name( f[1] );
      builtin::macro m( ctx.mtable()->get( name ) );
      assert( name == m.name() );

      std::vector<vm::type_string> args;
      for( int n=2; n < f.size(); ++n ) args.push_back( f[n] );
      f[0] = m.expand( ctx, args );

      //std::clog<<"call: "<<f[0]<<std::endl;
    }

    void assign_macro( context & ctx )
    {
    }

    void expand_macro( context & ctx )
    {
    }

  }//namespace builtin
}//namespace smart
