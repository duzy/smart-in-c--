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
      id_macro_ref,
      id_macro_value,
      id_in_spaces,
    };//enum parser_id_e

    template<typename TScan>
    struct definition
    {
      rule<TScan, parser_tag<id_statements> > statements;
      rule<TScan, parser_tag<id_statement> > statement;
      rule<TScan, parser_tag<id_assignment> > assignment;
      rule<TScan, parser_tag<id_macro_name> > macro_name;
      rule<TScan, parser_tag<id_macro_ref> > macro_ref;
      rule<TScan, parser_tag<id_macro_value> > macro_value;
      rule<TScan, parser_tag<id_in_spaces> > in_spaces; //!< inline spaces

      definition( const smart::grammar & self )
      {
        statements
          =  *statement
             >> end_p
          ;

        statement
          =  assignment
          |  no_node_d[ space_p ]
          |  no_node_d[ eol_p ]
          ;

        assignment
          =  lexeme_d
             [
                 macro_name
                 >> no_node_d[ in_spaces/* *(space_p - eol_p) */ ]
                 >> (  root_node_d[ ch_p('=')   ]
                    |  root_node_d[ str_p("+=") ]
                    |  root_node_d[ str_p(":=") ]
                    )
                 >> no_node_d[ /*in_spaces*/*(space_p - eol_p) ]
                 >> (  no_node_d[ eol_p ]
                    |  (  macro_value
                          >> no_node_d[ !(eol_p | end_p) ]
                       )
                    )
             ]
          ;

        macro_name
          =  lexeme_d
             [
                +(  token_node_d
                    [
                       +(graph_p - ch_p('$'))
                    ]
                 |  macro_ref
                 )
             ]
          ;

        macro_ref
          =  lexeme_d
             [
                no_node_d[ str_p("$(") ]
                >> token_node_d[ +(graph_p - ch_p(')')) ]
                >> no_node_d[ ch_p(')') ]
             ]
          ;

        macro_value
          =  lexeme_d
             [
                //!< discard the heading spaces
                no_node_d[ in_spaces/* *(space_p - eol_p) */ ]
                >> token_node_d //!< the first line
                   [
                      *(graph_p - ch_p('\\'))
                   ]
                >> *(
		       no_node_d //!< more lines
                       [
                          in_spaces //*(space_p - eol_p)
                          >> ch_p('\\') >> eol_p
                          >> in_spaces //*(space_p - eol_p)
                       ]
                       >> token_node_d
                          [
                             *(graph_p - ch_p('\\'))
                          ]
                    )
             ]
          ;

        in_spaces
          = lexeme_d[ *(space_p - eol_p) ]
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
        BOOST_SPIRIT_DEBUG_RULE(macro_ref);
        BOOST_SPIRIT_DEBUG_RULE(macro_value);
        BOOST_SPIRIT_DEBUG_RULE(in_spaces);
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
          =   space_p
          |   comment_p("#")
          //|   confix_p( str_p("#"), *anychar_p, eol_p )
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
