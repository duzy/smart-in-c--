# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#	

# Load default build parameters.
include build/defparams.mk

ifeq ($(UNAME),Linux)
  BOOST_LIB = boost_$1
else
  ifeq ($V,debug)
    BOOST_LIB = boost_$1-mgw44-mt-d
  else
    BOOST_LIB = boost_$1-mgw44-mt
  endif
endif
$(warning smart: TODO: replace BOOST_LIB with another name.)

# Detect custome config file and apply it.
CUSTOM_CONFIG := $(wildcard custom-config)
ifneq ($(CUSTOM_CONFIG),)
  $(info smart: Custom config file '$(CUSTOM_CONFIG)' found, applying..)
  $(eval -include $(CUSTOM_CONFIG))
endif

# Check BOOST_DIR
d := $(wildcard $(BOOST_DIR))
ifeq ($d,)
  $(info smart: ************************************************************)
  $(info smart: Smart Make depends on Boost C++ libraries, please tell me it's)
  $(info smart: location via the environment variable 'BOOST_DIR', it's now)
  $(info smart: $(if $(BOOST_DIR),of value '$(BOOST_DIR)'.,empty.))
  $(info smart: )
  $(info smart: See http://www.boost.org for more information.)
  $(info smart: ************************************************************)
  $(error "Can't locate Boost library")
endif

d :=
