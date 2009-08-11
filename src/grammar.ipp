/**                        -*- c++ -*-
 *
 */

#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/classic_ast.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>
#include <boost/spirit/include/classic_parse_tree_utils.hpp>

namespace smart
{
  using namespace boost::spirit::classic;

  struct grammar : boost::spirit::classic::grammar<grammar>
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
          =     *statement >> end_p
          ;

        statement
          =     assignment
          ;

        assignment
          =        discard_node_d[ *space_p ]
                >> macro_name
                >> (    root_node_d[ch_p('=')]
                   |    root_node_d[str_p("+=")]
                   |    root_node_d[str_p(":=")]
                   )
		>> leaf_node_d[ macro_value ]
                >> discard_node_d[ *(space_p | chset_p("\r\n")) ]
          ;

        macro_name
          =     lexeme_d[
                        graph_p
                    >>  *( ~chset_p("+:= \r\n") )
                ]
          ;

        macro_value
          =     !lexeme_d[
                        graph_p
                    >>  *( ~chset_p("\\\r\n") )
                    >>  *( ch_p('\\') >> eol_p >> *( ~chset_p("\\\r\n") ) )
                ]
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

  struct grammar_skip : boost::spirit::classic::grammar<grammar_skip>
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
