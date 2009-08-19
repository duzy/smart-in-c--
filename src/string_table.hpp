#ifndef __SMART_STRING_TABLE__HPP____by_Duzy_Chan__
#define __SMART_STRING_TABLE__HPP____by_Duzy_Chan__ 1
#	include <boost/flyweight.hpp>
#	include <boost/flyweight/no_tracking.hpp>
#	include <vector>

namespace smart
{

  struct string_table_index
  {
    int num;
  };//struct string_table_index

  struct string_table_entry
  {
    const std::string * ptr;
    string_table_index index;
  };//struct string_table_entry

  struct string_table
  {
    typedef string_table_index index;
    typedef string_table_entry entry;

    enum { max_size };

    string_table();

    int size() const;

    entry add( const std::string & );
    entry get( const std::string & );
    entry get( index i );

  private:
  # ifndef NO_FLYWEIGHT_STRING
    typedef boost::flyweights::flyweight
      < std::string, boost::flyweights::no_tracking > flyweight_string;
    std::vector<flyweight_string> _entries;
  # else//NO_FLYWEIGHT_STRING
    std::map<const std::string, int/* entry index */> _table;
    std::vector<const std::string*> _entries;
  # endif//NO_FLYWEIGHT_STRING
  };//struct string_table

}//namespace smart

#endif//__SMART_STRING_TABLE__HPP____by_Duzy_Chan__
