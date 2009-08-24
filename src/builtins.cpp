#include "builtins.hpp"
#include "context.hpp"
#include "macro_table.hpp"
#include "frame.hpp"
#include "expand.hpp"
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/classification.hpp>
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

    void if_f( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) return;
    }

    void or_f( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) return;
      f[0] = vm::type_string();
      for( int n=1; n < f.size(); ++n ) {
        vm::type_string s( expand(ctx, f[n]) );
        s.trim();
        if ( !s.empty() ) {
          f[0] = s;
          return;
        }
      }
    }

    void and_f( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) return;
      f[0] = vm::type_string();
      for( int n=1; n < f.size(); ++n ) {
        vm::type_string s( expand(ctx, f[n]) );
        s.trim();
        if ( s.empty() ) return;
      }
      f[0] = f.back();
    }

    void foreach_f( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      f[0] = vm::type_string();

      if ( f.size() < 4 ) return;
      vm::type_string var( expand(ctx, f[1]) );
      vm::type_string lst( expand(ctx, f[2]) );
      const std::string & str( lst );

      std::clog<<"text: "<<f[3]<<std::endl;

      macro m( ctx.mtable()->map(var) );
      if ( m.origin() == macro::origin_undefined )
        m.set_origin( macro::origin_automatic );

      vm::type_string v;

      typedef boost::split_iterator<std::string::const_iterator> iter_t;
      iter_t it( boost::make_split_iterator(str, boost::token_finder(boost::is_any_of(" \t"))) );
      iter_t const end;
      for(; it != end; ++it) {
	if ( it->empty() ) continue;
	std::string s( boost::copy_range<std::string>( *it ) );
        m.set_value( vm::type_string(s) );
        if ( !v.empty() ) v += " ";
        v += expand( ctx, f[3] );
      }//for

      if ( m.origin() == macro::origin_automatic ) {
        m.set_origin( macro::origin_undefined );
        m.set_value( vm::type_string() );
      }
      
      f[0] = v;
    }

    /**
     *  @brief Expand macro with args.
     */
    void call( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) {
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

    void value( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) {
	f[0] = vm::type_string();
	return;
      }

      builtin::macro m( ctx.mtable()->get( f[1] ) );
      assert( m.name() == f[1] );
      f[0] = m.value();
    }

    void origin( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) {
	f[0] = vm::type_string();
	return;
      }

      builtin::macro m( ctx.mtable()->get( f[1] ) );
      assert( m.name() == f[1] );
      f[0] = m.origin();
    }

    void flavor( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) {
	f[0] = vm::type_string();
	return;
      }

      builtin::macro m( ctx.mtable()->get( f[1] ) );
      assert( m.name() == f[1] );
      f[0] = m.flavor();
    }

    void info( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) return;
      
    }

    void warning( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) return;
    }

    void error( context & ctx )
    {
      frame & f ( ctx.current_frame() );
      if ( f.size() < 2 ) return;
    }

    void assign_macro( context & ctx )
    {
    }

    void expand_macro( context & ctx )
    {
    }

  }//namespace builtin
}//namespace smart
