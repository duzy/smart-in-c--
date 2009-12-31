# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming <duzy@duzy.info>
#

#$(call sm-new-module, libsmart.a, static)
$(call sm-new-module, libsmart.so, dynamic)

SM_COMPILE_LOG := libsmart.log
SM_MODULE_SOURCES := $(wildcard src/*.cpp)
SM_MODULE_HEADERS := 

SM_MODULE_INCLUDES := -I$(SM_MODULE_DIR)/include \
  $(SM_MODULE_DIR)/../boost_libraries

SM_MODULE_COMPILE_FLAGS :=

SM_MODULE_LINK_FLAGS :=

SM_MODULE_LIB_PATH := \
  $(SM_MODULE_DIR)/../boost_libraries/stage-$V/lib

SM_MODULE_LIBS := \
  $(call BOOST_LIB,system) \
  $(call BOOST_LIB,filesystem) \
  $(call BOOST_LIB,program_options)
