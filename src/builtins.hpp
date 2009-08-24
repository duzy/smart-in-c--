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

    void call( context & ctx );

    void assign_macro( context & ctx );
    void expand_macro( context & ctx );

  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN__hpp____by_Duzy_Chan__
