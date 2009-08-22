/**					-*- c++ -*-
 *
 */

// BOOST_SPIRIT_DEBUG_FLAGS_NODES
// BOOST_SPIRIT_DEBUG_FLAGS_TREES
// BOOST_SPIRIT_DEBUG_FLAGS_CLOSURES
// BOOST_SPIRIT_DEBUG_FLAGS_ESCAPE_CHAR
// BOOST_SPIRIT_DEBUG_FLAGS_SLEX

//#define BOOST_SPIRIT_DEBUG
//#define BOOST_SPIRIT_DEBUG_FLAGS BOOST_SPIRIT_DEBUG_FLAGS_NODES
#include "../src/grammar.ipp"
#include <boost/spirit/include/classic_tree_to_xml.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <map>

template<typename TTreeNode>
std::string get_value( const TTreeNode & nd )
{
  return std::string(nd.value.begin(), nd.value.end());
}

template<typename TNode>
void dump_macro_name( const TNode & )
{
}

template<typename TNode>
std::string get_macro_value( const TNode & nd )
{
  //assert( nd.value.id() == smart::grammar::id_macro_value );
  if ( 1 < nd.children.size() ) {
    std::string str;
    typename TNode::children_t::const_iterator it( nd.children.begin() );
    for(;;) {
      str += get_value( *it++ );
      if ( it == nd.children.end() ) break;
      else str += " ";
    }
    return str;
  }
  else return get_value(nd);
}

template<typename TTreeIter>
void dump_assignment( const TTreeIter & iter )
{
  assert( iter->value.id() == smart::grammar::id_assignment );
  assert( 0 < iter->children.size() );
  assert( iter->children.size() < 3 );
  if ( iter->children.size() == 2 )
    std::clog<<"'"<<get_value(iter->children[0])
	     <<"' = '"<<get_macro_value(iter->children[1])
	     <<"'"
      ;
  else
    std::clog<<"'"<<get_value(iter->children[0])
	     <<"' = <empty>"
      ;
}

template<typename TTreeIter>
void dump_rule( const TTreeIter & iter )
{
  assert( iter->value.id() == smart::grammar::id_make_rule );
  std::clog<<get_value( *iter );
}

template<typename TTreeIter>
void dump_statement( const TTreeIter & iter )
{
  assert( iter->value.id() == smart::grammar::id_statement );
  switch( iter->value.id().to_long() ) {
  case smart::grammar::id_assignment:
    std::clog<<"assignment: "<<iter->children.size()<<std::endl;
    break;
  default:
    std::clog<<"Unknown statement"<<std::endl;
    break;
  }
}

template<typename TTreeIter>
void dump( TTreeIter & iter, const TTreeIter & end )
{
  for(; iter != end; ++iter) {
    switch( iter->value.id().to_long() ) {
    case smart::grammar::id_statements:
      std::clog<<"statements: ";
      dump_statements( iter );
      std::clog<<std::endl;
      break;
    case smart::grammar::id_statement:
      std::clog<<"statement: ";
      dump_statement( iter );
      std::clog<<std::endl;
      break;
    case smart::grammar::id_assignment:
      std::clog<<"assignment: ";
      dump_assignment( iter );
      std::clog<<std::endl;
      break;
    case smart::grammar::id_make_rule:
      std::clog<<"rule: ";
      dump_rule( iter );
      std::clog<<std::endl;
      break;
    default:
      std::clog<<"Unkown statement."<<std::endl;
      break;
    }
  }
}

template<typename TTreeIter>
void dump_statements( const TTreeIter & iter )
{
  assert( iter->value.id() == smart::grammar::id_statements );
  std::clog<<"statements: "<<iter->children.size()<<std::endl;
  TTreeIter child( iter->children.begin() );
  TTreeIter const end( iter->children.end() );
  dump( child, end );
}

template<typename TTree>
void dump_parse_tree( const TTree & tree )
{
  std::clog<<"tree: size = "<<tree.size()<<std::endl;

  typedef typename TTree::const_iterator iterator_t;
  iterator_t beg( tree.begin() ), end( tree.end() );
  dump( beg, end );
}

int main(int argc, const char** argv)
{
  smart::grammar g;
  smart::grammar_skip s;

# ifdef BOOST_SPIRIT_DEBUG
  BOOST_SPIRIT_DEBUG_GRAMMAR(g);
  BOOST_SPIRIT_DEBUG_GRAMMAR(s);
# endif

  std::string str;
  {
    std::string nm("assignments.sm");
    //std::string nm("rules.sm");
    std::ifstream ifs( nm.c_str() );
    if ( !ifs ) ifs.open( ("t/" + nm).c_str() );
    ifs.seekg( 0, ifs.end );
    int sz( ifs.tellg() );
    if ( 0 < sz ) {
      str.resize( sz );
      ifs.seekg( 0, ifs.beg );
      ifs.read( &str[0], sz );
      //std::clog<<str<<std::endl;
    }
  }
  //BOOST_CHECK( !str.empty() );

  using namespace boost::spirit;
  typedef classic::position_iterator<std::string::const_iterator> iter_t;
  typedef classic::node_iter_data_factory<> factory_t;
  typedef classic::tree_parse_info<iter_t, factory_t> parse_tree_info_t;

  iter_t beg(str.begin(), str.end()), end;

  parse_tree_info_t pt( classic::ast_parse<factory_t>(beg,end,g,s) );
  #if 0
  dump_parse_tree( pt.trees );
  {
    std::map<classic::parser_id, std::string> names;
    names[smart::grammar::id_statements] = "statements";
    names[smart::grammar::id_statement] = "statement";
    names[smart::grammar::id_assignment] = "assignment";
    names[smart::grammar::id_macro_name] = "macro_name";
    names[smart::grammar::id_macro_ref] = "macro_ref";
    names[smart::grammar::id_macro_ref_args] = "macro_ref_args";
    names[smart::grammar::id_macro_ref_pattern] = "macro_ref_pattern";
    names[smart::grammar::id_macro_value] = "macro_value";
    names[smart::grammar::id_make_rule] = "make_rule";
    names[smart::grammar::id_make_rule_targets] = "make_rule_targets";
    names[smart::grammar::id_make_rule_prereqs] = "make_rule_prereqs";
    names[smart::grammar::id_make_rule_commands] = "make_rule_commands";
    names[smart::grammar::id_make_rule_command] = "make_rule_command";
    names[smart::grammar::id_in_spaces] = "in_spaces";
    classic::tree_to_xml(std::cout, pt.trees, str, names);
  }
  #endif
  if (!pt.full) {
    std::ostringstream err;
    err
      <<"parse error: line "
      <<pt.stop.get_position().line<<", column "
      <<pt.stop.get_position().column
      ;
    throw std::runtime_error(err.str());
  }
  
  return 0;
}
