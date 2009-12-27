# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#

ifeq ($(SM_MODULE_NAME),)
  $(info smart: ************************************************************)
  $(info smart:  You have to specify 'SM_MODULE_NAME'.)
  $(info smart: ************************************************************)
  $(error "SM_MODULE_NAME unknown")
endif

d := $(wildcard $(SM_MODULE_SOURCES))
#d := $(SM_MODULE_SOURCES)
ifeq ($d,)
  $(error "Nothing to build.")
endif

ifeq ($(SM_MODULE_TYPE),static)
  $(info static module)
else
  ifeq ($(SM_MODULE_TYPE),dynamic)
    $(info dynamic module)
  else
    ifeq ($(SM_MODULE_TYPE),executable)
      $(info executable module)
    else
    $(info smart: ************************************************************)
    $(info smart:  You have to specify 'SM_MODULE_TYPE', it can be one of )
    $(info smart:  '$(SM_MODULE_TYPES_SUPPORTED)'.)
    $(info smart: ************************************************************)
    $(error "SM_MODULE_TYPE unknown")
    endif
  endif
endif

# SM_MODULE_TYPE :=
# SM_MODULE_NAME :=
# SM_MODULE_SOURCES :=
# SM_MODULE_HEADERS :=

d :=
