# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming <duzy@duzy.info>
#

$(call sm-new-module,libsmart.a)

SM_COMPILE_LOG := libsmart.log
SM_MODULE_TYPE := static
SM_MODULE_SOURCES := $(wildcard src/*.cpp)
SM_MODULE_HEADERS := 
SM_MODULE_INCLUDES := \
  ../boost_libraries

