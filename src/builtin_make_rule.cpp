/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "builtin_make_rule.hpp"
#include "exceptions.hpp"
#include "expand.hpp"
#include <boost/ref.hpp>
#include <algorithm>
//#include <stdexcept>
#include <iostream>
#include <sstream>

namespace smart
{
  namespace builtin
  {
    struct make_rule::imp
    {
      long _usage;

      //std::vector<vm::type_string> _targets;
      std::vector<target> _prerequisites;
      std::vector<vm::type_string> _orderonly; //!< order-only prerequisites
      std::vector<vm::type_string> _commands;

      imp()
	: _usage( 0 )
	, _prerequisites()
	, _orderonly()
	, _commands()
      {
      }
    };//struct make_rule::imp

    void intrusive_ptr_add_ref( make_rule::imp * p )
    {
      ++p->_usage;
    }

    void intrusive_ptr_release( make_rule::imp * & p )
    {
      if ( 0 == p->_usage ) {
	delete p;
	p = 0;
      }
    }

    //======================================================================

    make_rule::make_rule( bool valid )
      : _i( valid ? new imp : NULL )
    {
    }

    const std::vector<builtin::target> & make_rule::prerequisites() const
    {
      if ( !_i ) {
	static std::vector<builtin::target> empty;
	return empty;
      }
      return _i->_prerequisites;
    }

    const std::vector<vm::type_string> & make_rule::commands() const
    {
      if ( !_i ) {
	std::vector<vm::type_string> empty;
	return empty;
      }
      return _i->_commands;
    }

    void make_rule::add_prerequisite( const target & t )
    {
      if ( !_i ) return;
      _i->_prerequisites.push_back( t );
    }

    struct do_update_target
    {
      target::update_result & _uc;
      context & _ctx;
      std::time_t _compare;
      do_update_target( context & ctx, target::update_result & uc, std::time_t t )
	: _uc(uc), _ctx(ctx), _compare(t) {}
      void operator()( const target & tar ) const
      {
	//const_cast<long&>(_uc) += tar.update( _ctx );
	target::update_result t( tar.update( _ctx ) );
	_uc.count_updated += t.count_updated;
	_uc.count_executed += t.count_executed;
	if ( _compare < tar.last_write_time() ) ++_uc.count_newer;
      }
    };//struct do_update_target
    target::update_result make_rule::update_prerequisites( context & ctx, std::time_t compareTime ) const
    {
      target::update_result uc = {0, 0, 0};
      if ( !_i ) return uc;
      do_update_target doUpdate( ctx, uc, compareTime );
      do_update_target & dr( doUpdate );
      std::for_each( _i->_prerequisites.begin(), _i->_prerequisites.end(), dr );
      return uc;
    }

    void make_rule::add_command( const vm::type_string & s )
    {
      if ( !_i ) return;
      _i->_commands.push_back( s );
    }

    void make_rule::set_commands( const std::vector<vm::type_string> & cmds )
    {
      if ( !_i ) return;
      _i->_commands = cmds;
    }

    struct do_execute_command
    {
      context & _ctx;
      do_execute_command( context & ctx ) : _ctx(ctx) {}
      void operator()( const vm::type_string & cmd ) const
      {
	vm::type_string ecmd( smart::expand(_ctx, cmd) );
	const std::string & s( ecmd );
	bool hasAt( false ), hasDash( false );
	for( int n=0; n < s.size(); ++n ) {
	  switch ( s[n] ) {
	  case '@': hasAt = true; break;
	  case '-': hasDash = true; break;
	  default:
	    {
	      std::string t( s.substr(n, s.size()) );
	      if ( !hasAt ) std::clog<<t<<std::endl;
	      int n( system( t.c_str() ) );
	      if ( n != 0 && !hasDash ) {
		std::ostringstream err;
		err<<"smart: Command error with exit code "<<n;
		throw smart::runtime_error( err.str() );
	      }
	      return;
	    }
	  }//switch
	}//for

	#if 0
	throw smart::runtime_error("unexpected execution point");
	#endif
      }
    };//struct do_execute_command
    int make_rule::execute_commands( context & ctx ) const
    {
      if ( !_i ) return 0;
      do_execute_command exec( ctx );
      std::for_each( _i->_commands.begin(), _i->_commands.end(), exec );
      return 0;
    }

    bool make_rule::empty() const
    {
      if ( !_i ) return true;
      return _i->_prerequisites.empty()
	&& _i->_orderonly.empty()
	&& _i->_commands.empty()
	;
    }

    bool make_rule::is_valid() const
    {
      return _i ? true : false;
    }

    long make_rule::refcount() const
    {
      if ( !_i ) return 0;
      return _i->_usage;
    }

    make_rule make_rule::clone() const
    {
      if ( !_i ) return make_rule( false );
      make_rule r( true );
      if ( !_i->_prerequisites.empty() )
	r._i->_prerequisites = _i->_prerequisites;
      if ( !_i->_orderonly.empty() )
	r._i->_orderonly = _i->_orderonly;
      if ( !_i->_commands.empty() )
	r._i->_commands = _i->_commands;
      return r;
    }

  }//namespace builtin
}//namespace smart
