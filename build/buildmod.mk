# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#

ifeq ($(SM_MODULE_NAME),)
  $(info smart: ************************************************************)
  $(info smart:  You have to specify 'SM_MODULE_NAME'.)
  $(info smart: ************************************************************)
  $(error "SM_MODULE_NAME unknown")
endif

#d := $(wildcard $(SM_MODULE_SOURCES))
d := $(SM_MODULE_SOURCES)
ifeq ($d,)
  $(error "Nothing to build.")
endif

DEFAULT_GOAL := $(SM_OUT_DIR)/$(SM_MODULE_NAME)
objs := $(SM_MODULE_SOURCES:%.cpp=$(SM_OUT_DIR)/%.o)

ifeq ($(SM_MODULE_TYPE),static)
    $(info TODO: dynamic module)
else
  ifeq ($(SM_MODULE_TYPE),dynamic)
    $(info TODO: dynamic module)
  else
    ifeq ($(SM_MODULE_TYPE),executable)
      $(info TODO: executable module)
    else
    $(info smart: ************************************************************)
    $(info smart:  You have to specify 'SM_MODULE_TYPE', it can be one of )
    $(info smart:  '$(SM_MODULE_TYPES_SUPPORTED)'.)
    $(info smart: ************************************************************)
    $(error "SM_MODULE_TYPE unknown")
    endif
  endif
endif

define gen_module
  @echo TODO: generate target $$@
endef
$(eval $(SM_OUT_DIR)/$(SM_MODULE_NAME): $(objs) ; $(gen_module))
gen_module :=

## Compute include path (-I switches).
SM_INCLUDES :=
append_include = $(eval SM_INCLUDES += -I$$(patsubst -I%,%,$$1))
$(foreach v,$(SM_MODULE_INCLUDES),$(call append_include,$v))
append_include :=

## Compute compile flags.
SM_COMPILE_FLAGS.cpp = $(SM_INCLUDES)

#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
SM_COMPILE.cpp = $(CXX) $(SM_COMPILE_FLAGS.cpp) -c

num_of_sources := $(words $(SM_MODULE_SOURCES))
$(info smart: Totally $(num_of_sources) source files to compile.)

define gen_compile_cmd
  @echo $(SM_COMPILE.cpp) -o $$@ $$^
endef

gen_rule = $(eval $1: $2 ; $(gen_compile_cmd))

d := $(SM_OUT_DIR)
$(foreach v,$(SM_MODULE_SOURCES),$(call gen_rule,$(v:%.cpp=$d/%.o),$v))

num_of_sources :=
gen_compile_cmd :=
gen_rule :=
objs :=
d :=

# SM_MODULE_TYPE :=
# SM_MODULE_NAME :=
# SM_MODULE_SOURCES :=
# SM_MODULE_HEADERS :=

