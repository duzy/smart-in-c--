/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan£¨Õ²ÐÀÃú£©
 *    All rights reserved by Duzy Chan£¨Õ²ÐÀÃú£©
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#ifndef __SMART_BUILTIN__hpp____by_Duzy_Chan__
#define __SMART_BUILTIN__hpp____by_Duzy_Chan__ 1
#	include "vm_fwd.hpp"

namespace smart
{
  struct context;

  namespace builtin
  {

    void noop( context & ctx );

    /**
     *  @brief Text Functions
     *  @{
     */
    void subst( context & ctx );
    void patsubst( context & ctx );
    void strip( context & ctx );
    void findstring( context & ctx );
    void filter( context & ctx );
    void filter_out( context & ctx );
    void sort( context & ctx );
    void word( context & ctx );
    void wordlist( context & ctx );
    void firstword( context & ctx );
    void lastword( context & ctx );
    /** @} */

    /**
     *  @brief File Name Functions
     */
    void dir( context & ctx );
    void notdir( context & ctx );
    void suffix( context & ctx );
    void basename( context & ctx );
    void addsuffix( context & ctx );
    void addprefix( context & ctx );
    void join( context & ctx ); //!< concates word by word
    void wildcard( context & ctx );
    void realpath( context & ctx );
    void abspath( context & ctx );
    /** @} */

    void if_f( context & ctx );
    void or_f( context & ctx );
    void and_f( context & ctx );
    
    void foreach_f( context & ctx );

    void call( context & ctx );

    void value( context & ctx );
    void origin( context & ctx );
    void flavor( context & ctx );

    /**
     *  @brief Functions That Controls Make
     *  @{ 
     */
    void info( context & ctx );
    void warning( context & ctx );
    void error( context & ctx );
    /** @} */

    void assign_macro( context & ctx );
    void expand_macro( context & ctx );

  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN__hpp____by_Duzy_Chan__
