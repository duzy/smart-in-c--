# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#	

V = debug
UNAME := $(shell uname)

# The project top level directory is where you type 'make' in.
SM_TOP_DIR := $(if $(PWD),$(PWD),$(shell pwd))
ifeq ($(SM_TOP_DIR),)
  $(info smart: ************************************************************)
  $(info smart:  I can't calculate the value of top level directory.) #'
  $(info smart: ************************************************************)
  $(error "Can't detect the value of project top level directory.")
endif

# The type of the platform the project is built on, the following platform is
# regonized by smart-build system: linux, cygwin, mingw.
SM_PLATFORM_TYPE :=

# The sub-type of the platform the project is built on,
# maybe: debian-5, ubuntu-44, ...
SM_PLATFORM_SUBTYPE :=

# The type of target which the smart build should generate, available value
# would be: static, dynamic, executable
SM_MODULE_TYPE :=
SM_MODULE_TYPES_SUPPORTED := static dynamic executable

# The name of the current compiling module, must be relative names.
SM_MODULE_NAME :=

# The source file list of the current compiling module, must be relative names.
SM_MODULE_SOURCES :=

SM_MODULE_HEADERS :=

# Compile command log, provide a log name to enable that.
SM_COMPILE_LOG :=

# The ouput directory for generated objects and files.
SM_OUT_DIR = $(SM_TOP_DIR)/out/$V



BOOST_DIR := $(HOME)/open/boost_libraries
BOOST_LIB_DIR := $(BOOST_DIR)/stage-$V/lib

