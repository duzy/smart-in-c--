/**                        -*- c++ -*-
 *
 */

#include <boost/spirit.hpp>
#include <boost/spirit/tree/ast.hpp>
#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/tree/parse_tree_utils.hpp>
//#include <boost/spirit/utility/chset_operators.hpp>

namespace smart
{
  using namespace boost::spirit;

  struct grammar : boost::spirit::grammar<grammar>
  {
    enum parser_id_e {
      id_noop,
      id_statements,
      id_statement,
      id_assignment,
      id_macro_name,
      id_macro_value,
    };//enum parser_id_e

    template<typename TScan>
    struct definition
    {
      rule<TScan, parser_tag<id_statements> > statements;
      rule<TScan, parser_tag<id_statement> > statement;
      rule<TScan, parser_tag<id_assignment> > assignment;
      rule<TScan, parser_tag<id_macro_name> > macro_name;
      rule<TScan, parser_tag<id_macro_value> > macro_value;

      definition( const smart::grammar & self )
      {
        statements
          =     *statement
          ;

        statement
          =     assignment
          ;

        assignment
          =     macro_name
                >> (    root_node_d[ch_p('=')]
                   |    root_node_d[str_p("+=")]
                   |    root_node_d[str_p(":=")]
                   )
                >> leaf_node_d[ macro_value ]
          ;

        macro_name
          =     +( ~ch_p('=') )
          ;

        macro_value
          =     *( ~ch_p('\n') )
          ;

        debug();
      }//definition()

      void debug()
      {
#       ifdef BOOST_SPIRIT_DEBUG
        BOOST_SPIRIT_DEBUG_RULE(statements);
        BOOST_SPIRIT_DEBUG_RULE(statement);
        BOOST_SPIRIT_DEBUG_RULE(assignment);
        BOOST_SPIRIT_DEBUG_RULE(macro_name);
        BOOST_SPIRIT_DEBUG_RULE(macro_value);
#       endif
      }//debug()

      const rule<TScan, parser_tag<id_statements> > & start()
      {
        return statements;
      }
    };//struct definition
  };//struct grammar

  //============================================================

  struct grammar_skip : boost::spirit::grammar<grammar_skip>
  {
    template<typename TScan>
    struct definition
    {
      definition( const grammar_skip & self )
      {
        skip
          =     space_p
          |     comment_p("#")
          ;

#       ifdef BOOST_SPIRIT_DEBUG
        BOOST_SPIRIT_DEBUG_RULE(skip);
#       endif
      }

      rule<TScan> skip;

      const rule<TScan> & start() { return skip; }
    };//struct definition
  };//struct grammar_skip
  
}//namespace smart
