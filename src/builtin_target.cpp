/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan��ղ������
 *    All rights reserved by Duzy Chan��ղ������
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "builtin_target.hpp"
#include "builtin_target_imp.hpp"
#include "builtin_make_rule.hpp"
#include <boost/ref.hpp>
#include <algorithm>

namespace smart
{
  namespace builtin
  {

    void intrusive_ptr_add_ref( target::imp *p )
    {
      target::imp::inref( p );
    }

    void intrusive_ptr_release( target::imp * & p )
    {
      target::imp::deref( p );
    }
    
    target::target()
      : vm::type_ext()
      , _i( new imp )
    {
    }
    
    target::target( const vm::type_string & str )
      : vm::type_ext()
      , _i( new imp(str) )
    {
    }
    
    vm::type_string target::object() const
    {
      return _i->_object;
    }

    struct get_rule_ptr {
      std::vector<make_rule*> vec;
      void operator()( make_rule & r ) { vec.push_back( &r ); }
    };
    std::vector<make_rule> target::rules() const
    {
      #if 1
      return _i->_rules;
      #else
      get_rule_ptr g;
      //std::for_each( _i->_rules.begin(), _i->_rules.end(), boost::ref(g) );
      get_rule_ptr & rg( g );
      std::for_each( _i->_rules.begin(), _i->_rules.end(), rg );
      return g.vec;
      #endif
    }

    void target::bind( const make_rule & r )
    {
      _i->_rules.push_back( r );
    }
    
  }//namespace builtin
}//namespace smart
