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
  $(eval SM_MODULE_NAME := $(strip $1))\
  $(eval SM_MODULE_SUFFIX := $$(suffix $(strip $1))),)\
$(if $2,$(eval SM_MODULE_TYPE := $(strip $2)),)\
$(eval SM_MODULE_DIR := $$(call sm-module-dir))
endef
 # $(if $(SM_MODULE_SUFFIX),\
 #   $(eval \
 #      ifeq ($$(SM_MODULE_SUFFIX),.a)
 #       SM_MODULE_TYPE := static
 #      else
 #        ifeq ($$(SM_MODULE_SUFFIX),.a)
 #         SM_MODULE_TYPE := dynamic
 #        endif
 #      endif
 #    ),)

## Load the build script for the specified module.
define load-module
$(if $1,\
  $(if $(wildcard $1),,$(error Module build script '$1' missed!))\
  $(eval $$(info smart: Load '$1'..)
    SM_MODULE_DIR:=
    SM_MODULE_TYPE:=
    SM_MODULE_NAME:=
    SM_MODULE_SOURCES:=
    SM_MODULE_HEADERS:=
    include $1),\
  $(error "Must specify the smart.mk file for the module."))
endef
