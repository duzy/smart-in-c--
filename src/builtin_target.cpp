/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include "builtin_target.hpp"
#include "builtin_make_rule.hpp"
#include "builtin_target_imp.hpp"
#include "context.hpp"
#include "exceptions.hpp"
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <algorithm>
#include <sstream>

namespace fs = boost::filesystem;

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

    long target::refcount() const
    {
      return _i->_usage;
    }
    
    vm::type_string target::object() const
    {
      return _i->_object;
    }

    bool target::exists() const
    {
      //return false;
      const std::string & s( _i->_object );
      return fs::exists( s );
    }

    std::time_t target::last_write_time() const
    {
      const std::string & s( _i->_object );
      if ( !fs::exists( s ) ) return std::time_t(0);
      return fs::last_write_time( s );
    }

    const make_rule & target::rule() const
    {
      return _i->_rule;
    }

    /**
     *  * Each target binds to one make-rule
     *  * New binding will overrides the previous commands
     *  * New binding combines prerequisites with the previous binding
     */
    void target::bind( const make_rule & r )
    {
      if ( _i->_rule.empty() ) {
        _i->_rule = r;
        return;
      }
      else {
	//!< If some other targets are referenced to the rule, we should make
	//!< a cloning of it.
	if ( 1 < _i->_rule.refcount() ) {
	  _i->_rule = _i->_rule.clone();
	}

        const std::vector<builtin::target> & ps( r.prerequisites() );
        std::for_each( ps.begin(), ps.end(), boost::bind(&make_rule::add_prerequisite, &_i->_rule, _1) );
        if ( !r.commands().empty() ) _i->_rule.set_commands( r.commands() );
      }
    }

    target::update_result target::update( context & ctx ) const
    {
      update_result uc = {0, 0, 0};
      make_rule r( _i->_rule );
      if ( r.empty() ) {
	r = ctx.find_rule( *this );
	if ( r.empty() ) {
	  //return uc;
	  std::ostringstream err;
	  err<<"no rule to make target '"<<_i->_object<<"'";
	  throw make_error( err.str() );
	}
      }

      bool isPhony( ctx.is_phony( *this ) );
      std::time_t lastWriteTime( this->last_write_time() );
      
      uc = r.update_prerequisites( ctx, lastWriteTime );

      //std::clog<<_i->_object<<":"<<uc<<std::endl;
      if ( isPhony || 0 < uc.count_updated || 0 < uc.count_newer || lastWriteTime == 0 /*|| !this->exists()*/ ) {
	bool b( lastWriteTime == 0 || 0 < uc.count_newer );

	r.execute_commands( ctx );

	if ( b /*&& this->exists()*/ ) {
	  if ( lastWriteTime < this->last_write_time() )
	    ++uc.count_updated;
	}
	++uc.count_executed;
	return uc;
      }

      return uc;
    }

    bool target::operator<( const target & o ) const
    {
      return _i->_object < o._i->_object;
    }
    
  }//namespace builtin
}//namespace smart
