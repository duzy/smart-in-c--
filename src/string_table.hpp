#ifndef __SMART_STRING_TABLE__HPP____by_Duzy_Chan__
#define __SMART_STRING_TABLE__HPP____by_Duzy_Chan__ 1

namespace smart
{
  struct string_table
  {
    typedef std::string * item;

    string_table();

    item add( const std::string & );
    item get( const std::string & );

  private:
    std::set<std::string> _table;
  };//struct string_table
}//namespace smart

#endif//__SMART_STRING_TABLE__HPP____by_Duzy_Chan__
