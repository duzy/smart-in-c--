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

objs := $(SM_MODULE_SOURCES:%.cpp=$(SM_OUT_DIR)/%.o)

ifeq ($(SM_MODULE_TYPE),static)
#  $(info objs: $(objs))
  $(eval $(SM_OUT_DIR)/$(SM_MODULE_NAME): $(objs))
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

# && \
#  echo $(CXX) -o $$@ $$<
define gen_compile_cmd
  @echo "$(SM_MODULE_NAME): $$@"
endef

define gen_rule
  $(eval $1: $2 ; $(gen_compile_cmd))
endef

d := $(SM_OUT_DIR)
$(foreach v,$(SM_MODULE_SOURCES),$(call gen_rule,$(v:%.cpp=$d/%.o),$v))

gen_compile_cmd :=
gen_rule :=
objs :=
d :=

# SM_MODULE_TYPE :=
# SM_MODULE_NAME :=
# SM_MODULE_SOURCES :=
# SM_MODULE_HEADERS :=

