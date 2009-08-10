/**					-*- c++ -*-
 *
 */

//#define BOOST_SPIRIT_DEBUG
#include "../src/grammar.ipp"
#include <string>
#include <stdexcept>

template<typename TTreeIter>
std::string get_value( const TTreeIter & iter )
{
  return std::string(iter.value.begin(), iter.value.end());
}

template<typename TTreeIter>
void dump_assignment( const TTreeIter & iter )
{
  assert( iter->value.id() == smart::grammar::id_assignment );
  assert( iter->children.size() == 2 );
  //std::clog<<"assignment: "<<iter->children.size()<<std::endl;
  std::clog<<"assignment: "
	   <<get_value(iter->children[0])
	   <<" = "
	   <<get_value(iter->children[1])
	   <<std::endl;
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
void dump_statements( const TTreeIter & iter )
{
  assert( iter->value.id() == smart::grammar::id_statements );
  std::clog<<"statements: "<<iter->children.size()<<std::endl;
  TTreeIter child( iter->children.begin() );
  TTreeIter end( iter->children.end() );
  for(; child != end; ++child) {
    dump_statement( child );
  }
}

template<typename TTree>
void dump_parse_tree( const TTree & tree )
{
  std::clog<<"tree: "<<tree.size()<<std::endl;

  typedef typename TTree::const_iterator iterator_t;
  iterator_t node( tree.begin() );
  for(; node != tree.end(); ++node) {
    std::clog<<"node: "<<node->value.id().to_long()<<std::endl;

    switch( node->value.id().to_long() ) {
    case smart::grammar::id_statements:
      dump_statements( node );
      break;
    case smart::grammar::id_statement:
      dump_statement( node );
      break;
    case smart::grammar::id_assignment:
      dump_assignment( node );
      break;
    default:
      std::clog<<"Unkown supported statement."<<std::endl;
      break;
    }
  }
}

int main(int argc, const char** argv)
{
  smart::grammar g;
  smart::grammar_skip s;

# ifdef BOOST_SPIRIT_DEBUG
  BOOST_SPIRIT_DEBUG_GRAMMAR(g);
  BOOST_SPIRIT_DEBUG_GRAMMAR(s);
# endif

//   std::string str
//     ("FOO = foo\n"
//      "BAR = bar\n"
//      "FOOBAR = $(FOO)$(BAR)\n"
//      );
  std::string str("FOO = foo");

  typedef boost::spirit::position_iterator<std::string::const_iterator> iter_t;
  typedef boost::spirit::node_iter_data_factory<> fact_t;
  typedef boost::spirit::tree_parse_info<iter_t, fact_t> parse_tree_info_t;

  iter_t beg(str.begin(), str.end()), end;

  parse_tree_info_t pt( boost::spirit::ast_parse<fact_t>(beg,end,g,s) );
  if (pt.full) {
    dump_parse_tree( pt.trees );
  }
  else {
    //throw std::runtime_error("Parse error");
    std::clog
      <<"parse error: line "
      <<pt.stop.get_position().line<<", column "
      <<pt.stop.get_position().column
      <<std::endl
      ;
  }
  
  return 0;
}
