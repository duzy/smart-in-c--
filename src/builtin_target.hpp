/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#ifndef __SMART_BUILTIN_TARGET__HPP____by_Duzy_Chan__
#define __SMART_BUILTIN_TARGET__HPP____by_Duzy_Chan__ 1
#	include "vm_types.hpp"
#	include <boost/intrusive_ptr.hpp>
#	include <vector>
#	include <ostream>
#	include <istream>

namespace smart
{
  struct context;

  namespace builtin
  {
    struct make_rule;

    struct target : vm::type_ext
    {
      target();
      explicit target( const vm::type_string & );

      long refcount() const;

      vm::type_string object() const;

      bool exists() const;

      bool update( context & ) const;
      bool updated() const;

      bool is_phony() const;

      const std::vector<make_rule> & rules() const;

      void bind( const make_rule & );

      struct imp;

    private:
      boost::intrusive_ptr<imp> _i;
    };//struct target

    void intrusive_ptr_add_ref( target::imp *p );
    void intrusive_ptr_release( target::imp * & p );

    inline std::ostream & operator<<( std::ostream & os, const target & t )
    {
      return (os << t.object());
    }

    inline std::istream & operator>>( std::istream & is, target & t )
    {
      vm::type_string temp; is>>temp;
      t = target(temp);
      return is;
    }
    
  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN_TARGET__HPP____by_Duzy_Chan__
