/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan��ղ������
 *    All rights reserved by Duzy Chan��ղ������
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#ifndef __SMART_CONTEXT__HPP____by_Duzy_Chan__
#define __SMART_CONTEXT__HPP____by_Duzy_Chan__ 1
#	include "vm_fwd.hpp"
#	include "builtin_macro.hpp"
#	include "builtin_make_rule.hpp"
#	include "frame.hpp"
#	include <string>
#	include <boost/unordered_map.hpp>

namespace smart
{
  struct string_table;
  struct real_table;
  struct macro_table;
  struct rule_table;
  struct function_table;

  /**
   *  @brief Smart script running context
   */
  struct context
  {
    context();

    string_table * stable() const;

    vm::type_string const_string( const std::string & c );
    //vm::type_real const_number( double c );

    macro_table *mtable() const;
    builtin::macro macro( const vm::type_string & v );
    builtin::macro macro( const std::string & v );

    builtin::target target( const vm::type_string & v );
    builtin::target map_target( const vm::type_string & v );

    /**
     * setup $1, $2, $3, $4, ....
     */
    void setup_macro_args( const std::vector<vm::type_string> & args );
    void clear_macro_args();

    function_table *ftable() const;
    vm::type_string invoke( const vm::type_string&, const std::vector<vm::type_string>& );

    frame & current_frame();

  private:
    string_table *_string_table; //!< for string constants
    //real_table *_number_table; //!< for real number constants
    macro_table *_macro_table;
    rule_table *_rule_table;
    function_table *_function_table;

    typedef boost::unordered_map<vm::type_string, builtin::target> target_table;
    target_table _targets;

    typedef std::vector<builtin::make_rule> rules_t;
    rules_t _rules;


    typedef std::vector<vm::type_string> args_t;
    std::vector<args_t> _macroArgs;

    std::vector<frame> _frames;
  };//struct context

  void info( const vm::type_string & );
  void warning( const vm::type_string & );
  void error( const vm::type_string & );

}//namespace smart

/**
 *	Macro	- Expandable makefile variable
 *	Rule	- Target building rule
 *	Target	- A file to be built according a defined rule
 *	Prerequisite - Targets required by the currently building target
 *	Variable - Smart script variable: string, integer, float, array
 */

#endif//__SMART_CONTEXT__HPP____by_Duzy_Chan__
