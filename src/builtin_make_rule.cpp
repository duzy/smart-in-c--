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

  }//namespace builtin
}//namespace smart
