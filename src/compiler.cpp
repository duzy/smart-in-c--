#include "compiler.hpp"
#include "context.hpp"
#include "string_table.hpp"
#include "builtins.hpp"
#include "vm_types.hpp"
#include "grammar.ipp"

#include <fstream>
#include <sstream>
#include <stdexcept>

# ifdef BOOST_SPIRIT_DEBUG
#   include <iostream>
# endif
# ifdef BOOST_SPIRIT_DEBUG_XML
#   include <boost/spirit/include/classic_tree_to_xml.hpp>
# endif

#   include <iostream>

namespace smart
{
  namespace detail
  {

    template<typename TTreeIter>
    static std::string compute_macro_name( context & ctx, const TTreeIter & iter )
    {
      assert( iter->value.id() == grammar::id_macro_name ||
	      iter->value.id() == grammar::id_macro_ref );
      std::string name( iter->value.begin(), iter->value.end() );

      vm::type_string str( ctx.const_string( name ) );
      assert( 0 < ctx.stable()->size() );

      if ( iter->value.id() == grammar::id_macro_ref ) {
	std::clog<<"ref: "<<name<<std::endl;
      }
      else {
      }
      return name;
    }

    template<typename TTreeIter>
    static void compile_assignment( context & ctx, const TTreeIter & iter )
    {
      assert( iter->value.id() == grammar::id_assignment );
      assert( 0 < iter->children.size() );
      //assert( iter->children.size() < 3 );

      std::string name( compute_macro_name( ctx, iter->children.begin() ) );
      if ( 1 < iter->children.size() ) { //!< has value
	char type( *(iter->value.begin()) );
	std::string value( iter->children[1].value.begin(),
			   iter->children[1].value.end() );
	std::clog<<"assign: "<<name<<type<<value<<std::endl;
	switch( type ) {
	case '=':
	  break;
	case '+':
	  break;
	case ':':
	  break;
	default:
	  break;
	}
      }
    }

    template<typename TTreeIter>
    static void compile_make_rule( context & ctx, const TTreeIter & iter )
    {
      assert( iter->value.id() == grammar::id_make_rule );
      
    }

    template<typename TTreeIter>
    static void compile_statements( context & ctx, const TTreeIter & iter )
    {
      assert( iter->value.id() == grammar::id_statements );
      
      TTreeIter child( iter->children.begin() );
      TTreeIter const end( iter->children.end() );

      for(; child != end; ++child) {
	switch( child->value.id().to_long() ) {

	case grammar::id_assignment:
	  compile_assignment( ctx, child );
	  break;

	case grammar::id_make_rule:
	  compile_make_rule( ctx, child );
	  break;

	default:
	  {
	    std::ostringstream err;
	    err<<"Unimplemented statement: "<<iter->value.id().to_long();
	    throw std::runtime_error( err.str() );
	  }
	}//switch
      }//for
    }//compile_statements()

    template<typename TTree>
    static void compile_tree( context & ctx, const TTree & tree )
    {
      if ( tree.size() <= 0 ) return;
      compile_statements( ctx, tree.begin() );
    }//compile_tree()
  }//namespace detail

  //============================================================

  compiler::compiler( context & ctx )
    : _context( ctx )
  {
  }

  void compiler::compile_file( const std::string & filename )
  {
    std::ifstream ifs( filename.c_str() );
    if ( !ifs ) {
      std::ostringstream err;
      err<<"Can't open script '"<<filename<<"'";
      throw std::runtime_error( err.str() );
    }

    ifs.seekg( 0, ifs.end );
    int sz( ifs.tellg() );
    if ( 0 < sz ) {
      std::string code;
      code.resize( sz );
      ifs.seekg( 0, ifs.beg );
      ifs.read( &code[0], sz );

      compile( code.begin(), code.end() );
    }
  }

  void compiler::compile( const std::string & code )
  {
    compile( code.begin(), code.end() );
  }

  void compiler::compile( const std::string::const_iterator & codeBeg,
			  const std::string::const_iterator & codeEnd )
  {
    grammar g;
    grammar_skip s;

#   ifdef BOOST_SPIRIT_DEBUG
    BOOST_SPIRIT_DEBUG_GRAMMAR(g);
    BOOST_SPIRIT_DEBUG_GRAMMAR(s);
#   endif//BOOST_SPIRIT_DEBUG

    using namespace boost::spirit;
    typedef classic::position_iterator<std::string::const_iterator> iter_t;
    typedef classic::node_iter_data_factory<> factory_t;
    typedef classic::tree_parse_info<iter_t, factory_t> parse_tree_info_t;

    iter_t beg(codeBeg, codeEnd), end;
    parse_tree_info_t pt( classic::ast_parse<factory_t>(beg, end, g, s) );

    if ( !pt.full ) {
      std::ostringstream err;
      err<<"parse error at column "<<pt.stop.get_position().column
	 <<" on line "<<pt.stop.get_position().line
	;
      throw std::runtime_error( err.str() );
    }

#   ifdef BOOST_SPIRIT_DEBUG_XML
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
      std::string code( codeBeg, codeEnd );
      classic::tree_to_xml(std::clog, pt.trees, code, names);
    }
#   endif//BOOST_SPIRIT_DEBUG_XML

    detail::compile_tree( _context, pt.trees );
  }
}//namespace smart
