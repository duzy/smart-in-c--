/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "builtin_make_rule.hpp"

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

    void make_rule::add_command( const vm::type_string & s )
    {
      _i->_commands.push_back( s );
    }

    void make_rule::set_commands( const std::vector<vm::type_string> & cmds )
    {
      _i->_commands = cmds;
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
