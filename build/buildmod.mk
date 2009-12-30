# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#

# Build the current module according to these macros:
#	SM_COMPILE_LOG		: log filename(relative) of compile commands
#	SM_MODULE_TYPE		: the type of the module to be compiled
#	SM_MODULE_NAME		: the name of the module to be compiled
#	SM_MODULE_SOURCES	: the sources to be compiled into the module
#	SM_MODULE_HEADERS	: (unused)

ifeq ($(SM_MODULE_NAME),)
  $(info smart: ************************************************************)
  $(info smart:  You have to specify 'SM_MODULE_NAME'.)
  $(info smart: ************************************************************)
  $(error "SM_MODULE_NAME unknown")
endif

#d := $(wildcard $(SM_MODULE_SOURCES))
d := $(strip $(SM_MODULE_SOURCES))
ifeq ($d,)
  $(error "Nothing to build.")
endif

DEFAULT_GOAL := $(SM_OUT_DIR)/$(SM_MODULE_NAME)

ifeq ($(SM_MODULE_TYPE),static)
    $(info TODO: static module flags)
else
  ifeq ($(SM_MODULE_TYPE),dynamic)
    $(info TODO: dynamic module flags)
  else
    ifeq ($(SM_MODULE_TYPE),executable)
      $(info TODO: executable module flags)
    else
    $(info smart: ************************************************************)
    $(info smart:  You have to specify 'SM_MODULE_TYPE', it can be one of )
    $(info smart:  '$(SM_MODULE_TYPES_SUPPORTED)'.)
    $(info smart: ************************************************************)
    $(error "SM_MODULE_TYPE unknown")
    endif
  endif
endif

## C++ link command
link = $(CXX) -o $$@ $$^

## Generate the module build rule.
objs := $(SM_MODULE_SOURCES:%.cpp=$(SM_OUT_DIR)/%.o)
gen_module_cmd := @echo C++: $$@ \
  && $(link) && echo " generated."
$(eval $(SM_OUT_DIR)/$(SM_MODULE_NAME): $(objs) ; $(gen_module_cmd))
gen_module_cmd :=
objs :=

## Compute include path (-I switches).
SM_INCLUDES :=
append_include = $(eval SM_INCLUDES += -I$$(patsubst -I%,%,$$1))
$(foreach v,$(SM_MODULE_INCLUDES),$(call append_include,$v))
append_include :=

## Compute compile flags.
SM_COMPILE_FLAGS.cpp = $(SM_INCLUDES)

#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
SM_COMPILE.cpp = $(CXX) $(SM_COMPILE_FLAGS.cpp) -c

# num_of_sources := $(words $(SM_MODULE_SOURCES))
# $(info smart: $(num_of_sources) source files will be compiled.)
# num_of_sources :=

## Compile log command.
log = $(if $(SM_COMPILE_LOG),echo $1 >> $(SM_OUT_DIR)/$(SM_COMPILE_LOG),true)

## Compile command.
compile = $(SM_COMPILE.cpp) -o $$@ $$^

#gen_compile_cmd = $(compile)
gen_compile_cmd = @echo "C++: $(SM_MODULE_NAME) <= $2" \
  && $(call log,$(compile)) \
  && ( $(compile) || $(call log,"failed: $$^") )

mk_out_dir = $(if $(wildcard $1),,$(info mkdir: $1)$(shell mkdir -p $1))
gen_rule = $(eval $1: $2 ; $(gen_compile_cmd))

d := $(SM_OUT_DIR)
$(foreach v,$(SM_MODULE_SOURCES),$(call mk_out_dir,$d/$(dir $v)))
$(foreach v,$(SM_MODULE_SOURCES),$(call gen_rule,$(v:%.cpp=$d/%.o),$v))

#$(info $(abspath $(SM_MODULE_SOURCES)))
#$(info $(realpath $(SM_MODULE_SOURCES)))

gen_compile_cmd :=
gen_rule :=
d :=

# SM_COMPILE_LOG :=
# SM_MODULE_TYPE :=
# SM_MODULE_NAME :=
# SM_MODULE_SOURCES :=
# SM_MODULE_HEADERS :=

