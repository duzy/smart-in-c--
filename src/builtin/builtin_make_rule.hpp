/**
 *    Copyright 2009-08-25 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#ifndef __SMART_BUILTIN_MAKE_RULE__HPP____by_Duzy_Chan__
#define __SMART_BUILTIN_MAKE_RULE__HPP____by_Duzy_Chan__ 1
#	include "../vm/vm_types.hpp"
#	include "builtin_target.hpp"
#	include <vector>
#	include <ctime>

namespace smart
{
  struct context;

  namespace builtin
  {
    /**
     *  @brief A make rule decides what to make, when to make and how to make.
     */
    struct make_rule : vm::type_ext
    {
      explicit make_rule( bool valid = false );

      long refcount() const;

      const std::vector<builtin::target> & prerequisites() const;
      void add_prerequisite( const target & );

      /**
       *  @brief Update prerequisites that needs updating.
       */
      target::update_result update_prerequisites( context &, std::time_t compareTime=0, const vm::type_string & stem=vm::type_string() /*if pattern*/ ) const;

      const std::vector<vm::type_string> & commands() const;
      void set_commands( const std::vector<vm::type_string> & );
      void add_command( const vm::type_string & );

      int execute_commands( context & ) const;

      bool empty() const;
      bool is_valid() const;

      make_rule clone() const;

      struct imp;

    private:
      boost::intrusive_ptr<imp> _i;
    };//struct make_rule

    void intrusive_ptr_add_ref( make_rule::imp * p );
    void intrusive_ptr_release( make_rule::imp * & p );
    
  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN_MAKE_RULE__HPP____by_Duzy_Chan__
