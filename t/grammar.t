/**					-*- c++ -*-
 *
 */

//#define BOOST_SPIRIT_DEBUG
#include "../src/grammar.ipp"
#include <string>
#include <sstream>
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
  assert( 0 < iter->children.size() );
  if ( iter->children.size() == 2 )
    std::clog<<"'"<<get_value(iter->children[0])
	     <<"' = '"<<get_value(iter->children[1])
	     <<"'"
      ;
  else
    std::clog<<"'"<<get_value(iter->children[0])
	     <<"' = '<empty>'"
      ;
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
    default:
      std::clog<<"Unkown supported statement."<<std::endl;
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

  std::string str
    ("  \n\n \r\n"
     "FOO = foo\n"
     "BAR = bar\n"
     "FOOBAR := $(FOO)$(BAR)\n"
     "\n"
     "FOO = xx\\\nyy\\\nzz\n"
     "FF ="
     );

  using namespace boost::spirit;
  typedef classic::position_iterator<std::string::const_iterator> iter_t;
  typedef classic::node_iter_data_factory<> factory_t;
  typedef classic::tree_parse_info<iter_t, factory_t> parse_tree_info_t;

  iter_t beg(str.begin(), str.end()), end;

  parse_tree_info_t pt( classic::ast_parse<factory_t>(beg,end,g,s) );
  dump_parse_tree( pt.trees );
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
