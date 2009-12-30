# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming <duzy@duzy.info>
#

$(call sm-new-module, libsmart.a, static)

SM_COMPILE_LOG := libsmart.log
SM_MODULE_SOURCES := $(wildcard src/*.cpp)
SM_MODULE_HEADERS := 
SM_MODULE_INCLUDES := -I$(SM_MODULE_DIR)/include \
  $(SM_MODULE_DIR)/../boost_libraries


