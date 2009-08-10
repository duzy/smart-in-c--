/**					-*- c++ -*-
 *
 */

#define BOOST_SPIRIT_DEBUG
#include "../src/grammar.ipp"
#include <string>
#include <stdexcept>

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
  std::string str("FOO = foo\n");

  typedef boost::spirit::position_iterator<std::string::const_iterator> iter_t;
  typedef boost::spirit::node_iter_data_factory<> fact_t;
  typedef boost::spirit::tree_parse_info<iter_t, fact_t> parse_tree_info_t;

  iter_t beg(str.begin(), str.end()), end;

  parse_tree_info_t pt( boost::spirit::ast_parse<fact_t>(beg,end,g,s) );
  if (pt.full) {
    
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
