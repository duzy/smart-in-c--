#ifndef __SMART_BUILTIN_MACRO__HPP____by_Duzy_Chan__
#define __SMART_BUILTIN_MACRO__HPP____by_Duzy_Chan__ 1
#	include "vm_types.hpp"
#	include <vector>

namespace smart
{
  struct context;

  namespace builtin
  {

    struct macro : vm::type_ext
    {
      macro();
      explicit macro( const vm::type_string & name,
                      const vm::type_string & value = vm::type_string() );

      macro( const macro & o );
      macro & operator=( const macro & o );

      virtual ~macro();

      vm::type_string name() const;

      /**
       *  @brief Unexpended value
       */
      vm::type_string value() const;
      void set_value( const vm::type_string & );

      vm::type_string expand( const context & ) const;
      vm::type_string expand( const context &, const std::vector<vm::type_string> & args ) const;

      /**
       *  $(subst FROM,TO,$(M))
       */
      vm::type_string subst( const std::vector<vm::type_string> & pats ) const;

      /**
       *  $(patsubst %.cpp,%.o,$(M))
       *  $(M:%.cpp=%.o)
       */
      vm::type_string patsubst( const std::vector<vm::type_string> & pats ) const;

      /**
       *  @brief Removes leading and trailing whitespaces from the expanded
       *         value of the macro and returns the result.
       */
      vm::type_string strip() const;

      /**
       *  $(findstring FIND,$(M))
       */
      vm::type_string findstring( const vm::type_string & s ) const;

      /**
       *  
       */
      vm::type_string filter() const;
      vm::type_string filter_out() const;

      vm::type_string sort() const;

      vm::type_string word( int n ) const;
      vm::type_string wordlist( int s, int e ) const;
      vm::type_string words() const;

      vm::type_string firstword() const;
      vm::type_string lastword() const;

      void assign( const vm::type_string & );
      void append( const vm::type_string & );

      static const vm::type_string origin_undefined;
      static const vm::type_string origin_default;
      static const vm::type_string origin_environment;
      static const vm::type_string origin_environment_override;
      static const vm::type_string origin_file;
      static const vm::type_string origin_command_line;
      static const vm::type_string origin_override;
      static const vm::type_string origin_automatic;
      /**
       *  @brief Tells where the macro come from.
       *        `undefined'
       *        `default'
       *        `environment'
       *        `environment override'
       *        `file'
       *        `command line'
       *        `override'
       *        `automatic'
       */
      vm::type_string origin() const;
      void set_origin( const vm::type_string & );

      static const vm::type_string flavor_undefined;
      static const vm::type_string flavor_recursive;
      static const vm::type_string flavor_simple;
      /**
       *  @brief The flavor of the macro
       *  @return One of the following:
       *        `undefined'
       *                if MACRO was never defined.
       *        `recursive'
       *                if MACRO is a recursively expanded variable.
       *        `simple'
       *                if MACRO is a simply expanded variable.
       */
      vm::type_string flavor() const;
      void set_flavor( const vm::type_string & );

    private:
      struct imp;
      imp *_i;
    };//struct macro

    //======================================================================

    /**
     *  @brief Patterns in the form of 'head%tail'
     */
    struct pattern
    {
      explicit pattern( const std::string & pat );
      std::string match( const std::string & s );
      vm::type_string convert( const pattern & pat1, const std::string & str );

      std::string head;
      std::string tail;
      bool is_valid;
    };//struct pattern
  
  }//namespace builtin
}//namespace smart

#endif//__SMART_BUILTIN_MACRO__HPP____by_Duzy_Chan__
