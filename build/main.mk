# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#	

## Smart Build directory, internal use only, must always contain a '/' tail.
SB_DIR = 

# Automate configuration for build parameters.
include $(SB_DIR)build/conf.mk

##################################################

d := $(wildcard $(SM_TOP_DIR)/smart.mk)
ifneq ($d,)
  SM_MODULE_TYPE :=
  SM_MODULE_NAME :=
  SM_MODULE_SOURCES :=
  SM_MODULE_HEADERS :=
  $(eval include $d)
  $(eval include $(SB_DIR)build/buildmod.mk)
else
  $(info smart: ************************************************************)
  $(info smart:  You have to provide the root build script 'smart.mk' at top)
  $(info smart:  level directory of the project.)
  $(info smart: ************************************************************)
  $(error "Can't find the root build script 'smart.mk'.")
endif

d :=