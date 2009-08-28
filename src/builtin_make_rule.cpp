/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "builtin_make_rule.hpp"
#include <boost/ref.hpp>
#include <algorithm>
//#include <iostream>

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

    make_rule::make_rule()
      : _i( new imp )
    {
    }

    const std::vector<builtin::target> & make_rule::prerequisites() const
    {
      return _i->_prerequisites;
    }

    const std::vector<vm::type_string> & make_rule::commands() const
    {
      return _i->_commands;
    }

    void make_rule::add_prerequisite( const target & t )
    {
      _i->_prerequisites.push_back( t );
    }

    struct do_update_target
    {
      long & _uc;
      context & _ctx;
      do_update_target( context & ctx, long & uc ) : _uc(uc), _ctx(ctx) {}
      void operator()( const target & tar ) //const
      {
	//const_cast<long&>(_uc) += tar.update( _ctx );
	_uc += tar.update( _ctx );
      }
    };//struct do_update_target
    long make_rule::update_prerequisites( context & ctx ) const
    {
      long uc( 0 );
      do_update_target doUpdate( ctx, uc );
      do_update_target & dr( doUpdate );
      std::for_each( _i->_prerequisites.begin(), _i->_prerequisites.end(), dr );
      //std::clog<<uc<<std::endl;
      return uc;//doUpdate._uc;
    }

    void make_rule::add_command( const vm::type_string & s )
    {
      _i->_commands.push_back( s );
    }

    void make_rule::set_commands( const std::vector<vm::type_string> & cmds )
    {
      _i->_commands = cmds;
    }

    struct do_execute_command
    {
      context & _ctx;
      do_execute_command( context & ctx ) : _ctx(ctx) {}
      void operator()( const vm::type_string & cmd ) const
      {
	const std::string & s( cmd );
	system(s.c_str());
      }
    };//struct do_execute_command
    int make_rule::execute_commands( context & ctx ) const
    {
      do_execute_command exec( ctx );
      std::for_each( _i->_commands.begin(), _i->_commands.end(), exec );
      return 0;
    }

    bool make_rule::empty() const
    {
      return _i->_prerequisites.empty()
	&& _i->_orderonly.empty()
	&& _i->_commands.empty()
	;
    }

    long make_rule::refcount() const
    {
      return _i->_usage;
    }

    make_rule make_rule::clone() const
    {
      make_rule r;
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
