# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming <duzy@duzy.info>
#

#$(call sm-new-module, libsmart.a, static)
#$(call sm-new-module, libsmart.so, dynamic)
$(call sm-new-module, smart, executable)

SM_COMPILE_LOG := libsmart.log
SM_MODULE_SOURCES := $(wildcard src/*.cpp)
SM_MODULE_HEADERS := 

SM_MODULE_INCLUDES := \
  $(SM_MODULE_DIR)/include \
  $(BOOST_DIR)

SM_MODULE_COMPILE_FLAGS := \
  -DSMART_USE_GRAMMAR_1=1

SM_MODULE_LINK_FLAGS :=

SM_MODULE_LIB_PATH := \
  $(BOOST_LIB_DIR)

SM_MODULE_LIBS := \
  $(call BOOST_LIB,system) \
  $(call BOOST_LIB,filesystem) \
  $(call BOOST_LIB,program_options)
