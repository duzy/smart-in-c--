#ifndef __SMART_STRING_TABLE__HPP____by_Duzy_Chan__
#define __SMART_STRING_TABLE__HPP____by_Duzy_Chan__ 1

namespace smart
{

  struct string_table_entry
  {
    std::string * ptr;
  };//struct string_table_entry

  struct string_table
  {
    typedef string_table_entry entry;

    string_table();

    entry add( const std::string & );
    entry get( const std::string & );

  private:
    std::map<entry, int> _table;
    std::vector<std::string> _entries;
  };//struct string_table

}//namespace smart

#endif//__SMART_STRING_TABLE__HPP____by_Duzy_Chan__
