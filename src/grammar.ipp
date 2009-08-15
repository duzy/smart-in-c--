/**                                                                 -*- c++ -*-
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
      id_macro_ref_args,
      id_macro_ref_pattern,
      id_macro_value,
      id_make_rule,
      id_make_rule_targets,
      id_make_rule_prereqs,
      id_make_rule_commands,
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
      rule<TScan, parser_tag<id_macro_ref_args> > macro_ref_args;
      rule<TScan, parser_tag<id_macro_ref_pattern> > macro_ref_pattern;
      rule<TScan, parser_tag<id_macro_value> > macro_value;
      rule<TScan, parser_tag<id_make_rule> > make_rule;
      rule<TScan, parser_tag<id_make_rule_targets> > make_rule_targets;
      rule<TScan, parser_tag<id_make_rule_prereqs> > make_rule_prereqs;
      rule<TScan, parser_tag<id_make_rule_commands> > make_rule_commands;
      rule<TScan, parser_tag<id_in_spaces> > in_spaces; //!< inline spaces

      definition( const smart::grammar & self )
      {
        statements
          =  *statement
             >> end_p
          ;

        statement
          =  no_node_d[ *space_p ] >> assignment
          |  no_node_d[ *space_p ] /* looks spirit can't eat spaces between two rules */
             >> make_rule
          ;

        assignment
          =  lexeme_d
             [
                 macro_name
                 >> no_node_d[ in_spaces ]
                 >> (  root_node_d[ ch_p('=')   ]
                    |  root_node_d[ str_p("+=") ]
                    |  root_node_d[ str_p(":=") ]
                    )
                 >> no_node_d[ *(space_p - eol_p) ]
                 //>> no_node_d[ in_spaces ] //!< will eat \n while entering in_spaces
                 >> (  no_node_d[ (eol_p | end_p) ]
                    |  macro_value
                       >> no_node_d[ !(eol_p | end_p) ]
                    )
             ]
          ;

        macro_name
          =  lexeme_d
             [
                +(  token_node_d[ +(graph_p - ch_p('$'))]
                 |  macro_ref
                 )
             ]
             >> ( eps_p('=') | eps_p("+=") | eps_p(":=") )
          ;

        macro_ref
          =  lexeme_d
             [
                eps_p('$')
                >> (  no_node_d[ str_p("$(") ]  //!< $(...)
                      >> +(  token_node_d[ +(graph_p - chset_p("$:)")) ]
                          |  macro_ref //!< recursive
                          )
                      >> !( ( no_node_d[ space_p ] >> macro_ref_args )
                          | ( eps_p(':') >> macro_ref_pattern )
                          )
                      >> no_node_d[ ch_p(')') ]

                      //!<<<<<<<<<<<<<<<<< @{
                   |  no_node_d[ str_p("${") ]  // ${...}
                      >> +(  token_node_d[ +(graph_p - chset_p("$:}")) ]
                          |  macro_ref //!< recursive
                          )
                      >> no_node_d[ ch_p('}') ]
		   |  no_node_d[ str_p("${") ]
                      >> +(  token_node_d[ +(graph_p - chset_p("$:}")) ]
                          |  macro_ref //!< recursive
                          )
		      >> ( space_p | ':' )
                      >> +(  token_node_d[ +(anychar_p - chset_p("$=}")) ]
                          |  macro_ref //!< recursive
                          )
		      >> '='
                      >> +(  token_node_d[ +(anychar_p - chset_p("$}")) ]
                          |  macro_ref //!< recursive
                          )
                      >> no_node_d[ ch_p('}') ]
                      //!<<<<<<<<<<<<<<<<< @}

                   |  no_node_d[ str_p("$()") ]
                   |  no_node_d[ str_p("${}") ]
                   |  no_node_d[ ch_p('$') ] >> graph_p
                   )
             ]
          ;

        macro_ref_args
          =  lexeme_d
             [
                +(  token_node_d[ +(anychar_p - chset_p("$,)")) ]
                    |  macro_ref //!< recursive
                    )
                >> *(  no_node_d[ ch_p(',') ]
                       >> +(  token_node_d[ +(anychar_p - chset_p("$,)")) ]
                           |  macro_ref
                           )
                    )
             ]
          ;

        macro_ref_pattern
          =  lexeme_d
             [
                no_node_d[ ch_p(':') ]
                >> +(  token_node_d[ +(anychar_p - chset_p("$=)")) ]
                    |  macro_ref //!< recursive
                    )
                >> no_node_d[ ch_p('=') ]
                >> +(  token_node_d[ +(anychar_p - chset_p("$)")) ]
                    |  macro_ref //!< recursive
                    )
             ]
          ;

        //!< list
        macro_value
          =  lexeme_d
             [
                //!< discard the heading spaces
                no_node_d[ in_spaces ]
                >> *(  ~eps_p(eol_p) >> macro_ref
                    |  token_node_d[ +(anychar_p - chset_p("\\$\r\n")) ]
                    )
                >> *(
		       no_node_d //!< more lines
                       [
                          in_spaces
                          >> ch_p('\\') >> eol_p
                          >> in_spaces
                       ]
                       >> *(  ~eps_p(eol_p) >> macro_ref
                           |  token_node_d[ +(anychar_p - chset_p("\\$\r\n")) ]
                           )
                    )
             ]
          ;

        make_rule
          =  lexeme_d
             [
                make_rule_targets
                >> no_node_d[ *(space_p - eol_p) ] //!< spirit can't eat these spaces
                >> no_node_d[ ch_p(':') ]
                >> no_node_d[ *(space_p - eol_p) ] //!< spirit can't eat these spaces
                >> make_rule_prereqs
                >> no_node_d[ eol_p | end_p ]
                //>> !(eps_p('\t') >> make_rule_commands)
                >> !(no_node_d[ ch_p('\t') ] >> make_rule_commands)
             ]
          ;

        make_rule_targets
          =  lexeme_d
             [
                +( token_node_d[ +( anychar_p - chset_p(": \t\r\n") ) ]
                 | no_node_d[ +(space_p - eol_p) ]
                 | macro_ref
                 )
             ]
          ;

        make_rule_prereqs
          =  lexeme_d
             [
                *( token_node_d
                   [
                      //~eps_p( (*space_p >> eol_p) >> eol_p  ) >>
                      +( anychar_p - eol_p )
                   ]
                 | ~eps_p(chset_p("\t\r\n")) >> macro_ref
                 )
             ]
          ;

        make_rule_commands
          =  lexeme_d
             [
                token_node_d[ *(anychar_p - (eol_p|'\\')) ]
                >> no_node_d[ eol_p ]
                >> *( no_node_d[ ch_p('\t') ]
                      >> token_node_d[ *(anychar_p - (eol_p|'\\')) ]
                      >> ( no_node_d[ eol_p ]
                         | +( no_node_d[ ch_p('\\') >> eol_p ]
                              >> token_node_d[ *(anychar_p - (eol_p|'\\')) ]
                            )
                           >> no_node_d[ eol_p ]
                         )
                    )
             ]
          ;

        in_spaces
          =  lexeme_d[ *(space_p - eol_p) ]
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
        BOOST_SPIRIT_DEBUG_RULE(macro_ref_args);
        BOOST_SPIRIT_DEBUG_RULE(macro_ref_pattern);
        BOOST_SPIRIT_DEBUG_RULE(macro_value);
        BOOST_SPIRIT_DEBUG_RULE(make_rule);
        BOOST_SPIRIT_DEBUG_RULE(make_rule_targets);
        BOOST_SPIRIT_DEBUG_RULE(make_rule_prereqs);
        BOOST_SPIRIT_DEBUG_RULE(make_rule_commands);
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
          =   +space_p
          |   comment_p("#")
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
