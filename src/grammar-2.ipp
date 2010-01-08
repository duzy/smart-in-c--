/**								-*- c++ -*-
 *    Copyright 2009-01-07 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>

namespace smart
{
  struct parse_tree
  {
    
  };//struct parse_tree
}//namespace smart

namespace smart
{
  using boost::spirit::qi;

  template<typename Iterator, parse_tree>
  struct grammar : boost::spirit::qi::grammar<Iterator, parse_tree>
  {
    grammar() : base_type( statements, "smart::grammar" )
    {
      //using qi::

      statements
	= *statement >> end_p
	;

      statement
	= assignment
	//| make_rule
	//| macro_ref
	//| include_directive
	;

      assignment
	=  macro_name
	>> ( lit('=')
	     | lit("+=")
	     | lit(":=")
	     | lit("?=")
	     )
	>> ( macro_value
	     | eol
	     | eoi
	     )
	;

      macro_name
	= +(char_ - char_("$:=+?"))
	>> eps( lit('=') | "+=" | ":=" | "?=" )
	;

      macro_value
	= *(char_ - eol)
	;
    }

    qi::rule<Iterator> statements;
    qi::rule<Iterator> statement;
    qi::rule<Iterator> assignment;
    qi::rule<Iterator> macro_name;
    qi::rule<Iterator> macro_ref;
    qi::rule<Iterator> macro_ref_name;
    qi::rule<Iterator> macro_ref_args;
    qi::rule<Iterator> macro_ref_pattern;
    qi::rule<Iterator> macro_value;
    qi::rule<Iterator> expandable;
    qi::rule<Iterator> make_rule;
    qi::rule<Iterator> make_rule_targets;
    qi::rule<Iterator> make_rule_commands;
    qi::rule<Iterator> make_rule_command;
    qi::rule<Iterator> include_directive;
  };//struct grammar
}//namespace smart
