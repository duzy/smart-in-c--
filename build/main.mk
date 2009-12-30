# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#	

#$(info MakefileList: $(MAKEFILE_LIST))

## Smart Build directory, internal use only, must always contain a '/' tail.
SB_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
ifeq ($(SB_DIR)/conf.mk,)
  $(error "Can't find smart build system directory.")
endif

# Automate configuration for build parameters.
include $(SB_DIR)/conf.mk

# Predefined functions.
include $(SB_DIR)/defuns.mk

##################################################

d := $(wildcard $(SM_TOP_DIR)/smart.mk)
ifneq ($d,)
  $(call load-module,$d)
  $(if $(strip $(SM_MODULE_DIR)),,$(error "SM_MODULE_DIR must be set!"))
  include $(SB_DIR)/buildmod.mk
else
  $(info smart: ************************************************************)
  $(info smart:  You have to provide the root build script 'smart.mk' at top)
  $(info smart:  level directory of the project.)
  $(info smart: ************************************************************)
  $(error "Can't find the root build script 'smart.mk'.")
endif

d :=
