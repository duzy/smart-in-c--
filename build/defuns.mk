# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#	

  # $(eval sm_mod_dir_ := $(lastword $(MAKEFILE_LIST)) \
  #   $(dir $(sm_mod_dir_)) \
  #   )
define sm-module-dir
$(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
endef

define sm-new-module
$(if $1,$(info NewModule: $1)\
  $(eval SM_MODULE_NAME := $(strip $1)),)\
 $(eval SM_MODULE_DIR := $$(call sm-module-dir))
endef
