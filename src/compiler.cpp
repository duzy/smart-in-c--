#include "compiler.hpp"
#include "context.hpp"
#include "string_table.hpp"
#include "macro_table.hpp"
#include "builtins.hpp"
#include "vm_types.hpp"
#include "expand.hpp"
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
    static vm::type_string expanded_macro_value( context & ctx, const TTreeIter & iter );

    template<typename TTreeIter>
    static vm::type_string get_macro_ref_name( context & ctx, const TTreeIter & iter )
    {
      assert( iter->value.id() == grammar::id_macro_ref );
      assert( iter->children.empty() || 2 <= iter->children.size() ); //!< '$(' ... ')'

      if ( iter->children.empty() ) return vm::type_string();
      if ( iter->children.size() == 2 || iter->children.size() == 3 ) {
        //!< $X, $(X), ${X}
        TTreeIter nodeName( iter->children.begin() + 1 );
        //std::string s(nodeName->value.begin(), nodeName->value.end());
        //return vm::type_string(s);
        return ctx.const_string( std::string(nodeName->value.begin(), nodeName->value.end()) );
      }

      vm::type_string name;

      TTreeIter child( iter->children.begin() + 1 ); //!< skip '$('
      TTreeIter const end( iter->children.end() - 1 ); //!< skip ')'
      for(; child != end; ++child) {
        switch( child->value.id().to_long() ) {
        case grammar::id_macro_ref:
          name += expanded_macro_value( ctx, child );
          break;
        default:
          //name += std::string( child->value.begin(), child->value.end() );
          name += ctx.const_string( std::string( child->value.begin(), child->value.end()) );
        }//switch
      }//for
      
      return name;
    }//get_macro_ref_name()

    template<typename TTreeIter>
    static vm::type_string unexpended_macro_value( context & ctx, const TTreeIter & iter )
    {
      vm::type_string value;
      if ( iter->children.empty() || iter->value.id() == grammar::id_macro_ref ) {
        //value = std::string( iter->value.begin(), iter->value.end() );
        //return value;
        return ctx.const_string( std::string(iter->value.begin(), iter->value.end()) );
      }

      TTreeIter child( iter->children.begin() );
      TTreeIter const end( iter->children.end() );
      for(; child != end; ++child ) {
        std::string s( child->value.begin(), child->value.end() );
        ctx.const_string(s);

        std::string t;
        if ( s == "\\" ) t = ( value.empty() ? "" : " " );
        else t += s;
        value += t;
      }//for
      
      return value;
    }//unexpended_macro_value()

    template<typename TTreeIter>
    static vm::type_string expanded_macro_value( context & ctx, const TTreeIter & iter )
    {
      //assert( iter->value.id() == grammar::id_macro_value ||
      //        iter->value.id() == grammar::id_macro_ref );

      if ( iter->value.id() == grammar::id_macro_ref ) {
        vm::type_string refName( get_macro_ref_name( ctx, iter ) );
        builtin::macro m( ctx.mtable()->get( refName ) );
        assert( refName == m.name() );
        //std::clog<<"ref: "<<m.name()<<" = "<<m.value()<<std::endl;
        return m.value();
        //return m.expand( ctx );
      }

      if ( iter->children.empty() ) {
        //std::string s( iter->value.begin(), iter->value.end() );
        //return vm::type_string( s );
        return ctx.const_string(std::string( iter->value.begin(), iter->value.end() ));
      }

      vm::type_string v;

      TTreeIter child( iter->children.begin() );
      TTreeIter const end( iter->children.end() );
      for(; child != end; ++child) {
        switch( child->value.id().to_long() ) {
        case grammar::id_macro_ref:
          v += expanded_macro_value( ctx, child );
          break;
        default:
          {
            std::string s( child->value.begin(), child->value.end() );
            ctx.const_string( s );

            if ( s == "\\" ) v += " ";
            else v += s;
          }
          break;
        }//switch
      }//for

      //std::clog<<"expand: "<<v<<std::endl;
      
      return v;
    }//expanded_macro_value()

    template<typename TTreeIter>
    static void compile_assignment( context & ctx, const TTreeIter & iter )
    {
      assert( iter->value.id() == grammar::id_assignment );
      assert( 0 < iter->children.size() );
      //assert( iter->children.size() < 3 );

      vm::type_string name( expanded_macro_value( ctx, iter->children.begin() ) );
      TTreeIter nodeValue( 1 < iter->children.size()
                           ? iter->children.begin() + 1
                           : iter->children.end() );

      builtin::macro m( ctx.mtable()->map(name) );
      //std::clog<<"macro: "<<m.name()<<" = "<<m.value()<<std::endl;

      char type( *(iter->value.begin()) );
      switch( type ) {

      case '=': //!< recursive expended
      case '?': //!< recursive if undefined
        {
          if ( type == '?' && m.origin() != builtin::macro::origin_undefined )
            break;
          m.set_origin( builtin::macro::origin_file );
          m.set_flavor( builtin::macro::flavor_recursive );
          if ( nodeValue != iter->children.end() ) {
            m.set_value( unexpended_macro_value(ctx, nodeValue) );
          }
          //std::clog<<"assignment: "<<m.name()<<" = "<<m.value()<<std::endl;
        }
        break;

      case ':': //!< simple expended
        {
          m.set_origin( builtin::macro::origin_file );
          m.set_flavor( builtin::macro::flavor_simple );
          if ( nodeValue != iter->children.end() ) {
            vm::type_string value( expanded_macro_value( ctx, nodeValue ) );
            m.set_value( value );
          }
          //std::clog<<"assignment: "<<m.name()<<" := "<<m.value()<<std::endl;
        }
        break;

      case '+':
        if ( nodeValue == iter->children.end() ) break;
        if ( m.flavor() == builtin::macro::flavor_simple ) { //!< :=
          vm::type_string value( expanded_macro_value( ctx, nodeValue ) );
          m.set_value( m.value() + value );
          //std::clog<<"assignment: "<<m.name()<<" += "<<value<<std::endl;
        }
        else { //!< =, or undefined
          m.set_value( m.value() + unexpended_macro_value(ctx, nodeValue) );
          //std::clog<<"assignment: "<<m.name()<<" += "<<m.value()<<std::endl;
        }
        break;

      default:
        {
          std::ostringstream err;
          err<<"invalid assignment";
          throw std::runtime_error( err.str() );
        }
        break;

      }//switch
    }//compile_assignment()

    template<typename TTreeIter>
    static void compile_make_rule( context & ctx, const TTreeIter & iter )
    {
      assert( iter->value.id() == grammar::id_make_rule );
      
    }//compile_make_rule()

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

  vm::type_string expand( const context & ctx, const vm::type_string & str )
  {
    vm::type_string v;
    
    return v;
  }

  vm::type_string expand( const context & ctx, const vm::type_string & str,
                          const std::vector<vm::type_string> & args )
  {
    vm::type_string v;
    return v;
  }

  //======================================================================

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
