#ifndef __SMART_FRAME__HPP____by_Duzy_Chan__
#define __SMART_FRAME__HPP____by_Duzy_Chan__ 1
#	include <vector>

namespace smart
{
  struct frame
  {
    std::size_t size() const { return _vars.size(); }

    /**
     *  @brief The number of args.
     *  The first var (f[0]) is used as the return value of a invocation.
     */
    std::size_t args_size() const { return _vars.size()-1; }

    void resize( std::size_t sz ) { _vars.resize(sz); }

    vm::type_string & front() { return _vars.front(); }

    vm::type_string & back() { return _vars.back(); }

    vm::type_string & operator[]( int n )
    {
    # if 0
      if ( _vars.size() <= n ) _vars.resize( n+1 );
    # endif
      return _vars[n];
    }

//     vm::type_string & operator[]( const vm::type_string & n )
//     {
//     }

  private:
    std::vector<vm::type_string> _vars;
  };//struct frame
}//namespace smart

#endif//__SMART_FRAME__HPP____by_Duzy_Chan__
