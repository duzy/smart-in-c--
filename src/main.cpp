/**
 *    Copyright 2009-08-25 DuzySoft.com, by Duzy Chan��ղ������
 *    All rights reserved by Duzy Chan��ղ������
 *    Email: <duzy@duzy.info, duzy.chan@gmail.com>
 *
 *    $Id$
 *
 **/

#include <exception>

int main(int argc, const char** argv)
{
  std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
  return 0;
}
