/**								-*- c++ -*-
 *    Copyright 2009-01-07 DuzySoft.com, by Zhan Xin-Ming (Duzy Chan)
 *    All rights reserved by Zhan Xin-Ming (Duzy Chan)
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

// #include <boost/spirit/home/qi/nonterminal/grammar.hpp>
// #include <boost/spirit/home/qi/auxiliary/eol.hpp>
// #include <boost/spirit/home/qi/auxiliary/eoi.hpp>
// #include <boost/spirit/home/qi/auxiliary/eps.hpp>
// #include <boost/spirit/home/qi/auxiliary/attr.hpp>
// #include <boost/spirit/home/qi/char/char.hpp>
////#include <boost/spirit/home/qi.hpp>

// #include <boost/spirit/include/qi_grammar.hpp>
// #include <boost/spirit/include/qi_eol.hpp>
// #include <boost/spirit/include/qi_eoi.hpp>
// #include <boost/spirit/include/qi_eps.hpp>
// #include <boost/spirit/include/qi_attr.hpp>
// #include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>

namespace smart
{
  struct parse_tree
  {
    
  };//struct parse_tree
}//namespace smart

namespace smart
{
  template<typename Iterator>
  struct grammar : boost::spirit::qi::grammar<Iterator, parse_tree()>
  {
    grammar() : grammar::base_type( statements, "smart::grammar" )
    {
      using boost::spirit::qi::eoi;
      using boost::spirit::qi::eol;
      using boost::spirit::qi::eps;
      using boost::spirit::qi::lit;
      using boost::spirit::qi::ascii::char_;

      statements
        = *statement >> eoi
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
        >> -(eps( lit('=') | "+=" | ":=" | "?=" ))
        ;

      macro_value
        = *(char_ - char_("\n\r")/*eol*/)
        ;
    }

    boost::spirit::qi::rule<Iterator, parse_tree()> statements;
    boost::spirit::qi::rule<Iterator> statement;
    boost::spirit::qi::rule<Iterator> assignment;
    boost::spirit::qi::rule<Iterator> macro_name;
    boost::spirit::qi::rule<Iterator> macro_ref;
    boost::spirit::qi::rule<Iterator> macro_ref_name;
    boost::spirit::qi::rule<Iterator> macro_ref_args;
    boost::spirit::qi::rule<Iterator> macro_ref_pattern;
    boost::spirit::qi::rule<Iterator> macro_value;
    boost::spirit::qi::rule<Iterator> expandable;
    boost::spirit::qi::rule<Iterator> make_rule;
    boost::spirit::qi::rule<Iterator> make_rule_targets;
    boost::spirit::qi::rule<Iterator> make_rule_commands;
    boost::spirit::qi::rule<Iterator> make_rule_command;
    boost::spirit::qi::rule<Iterator> include_directive;
  };//struct grammar
}//namespace smart
