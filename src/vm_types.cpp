namespace smart
{
  namespace vm
  {
    
    type_string::type_string( const std::string & v )
      : is_constant_( 0 )
      , is_copied_( 0 )
    {
    }

    type_string::type_string( const string_table_entry & e )
      : is_constant_( 1 )
      , is_copied_( 0 )
    {
    }

    type_string::type_string( const type_string & o )
    {
      this->operator=( o );
    }

    type_string & type_string::operator=( const type_string & o )
    {
      is_constant_ = o.is_constant_;

      return *this;
    }

    type_string::~type_string()
    {
      if ( is_copied_ ) delete ptr_;
    }

    bool type_string::is_constant() const
    {
      return is_constant_;
    }
    
  }//namespace vm
}//namespace smart
