# -*- mode: Makefile:gnu -*-

UNAME := $(shell uname)

#BOOST_DIR = /home/duzy/open/boost-trunk
BOOST_DIR = /home/duzy/open/boost_libraries
BOOST_LIB_DIR = $(BOOST_DIR)/stage-$V/lib

ifeq ($(UNAME),Linux)
  BOOST_LIB = boost_$1
else
  ifeq ($V,debug)
    BOOST_LIB = boost_$1-mgw44-mt-d
  else
    BOOST_LIB = boost_$1-mgw44-mt
  endif
endif
