# -*- mode: Makefile:gnu -*-
#	Copyright(c) 2009, by Zhan Xin-ming, duzy@duzy.info
#

# Build the current module according to these macros:
#	SM_COMPILE_LOG		: log filename(relative) of compile commands
#	SM_MODULE_DIR		: the directory in which the module locates
#	SM_MODULE_TYPE		: the type of the module to be compiled
#	SM_MODULE_NAME		: the name of the module to be compiled
#	SM_MODULE_SOURCES	: the sources to be compiled into the module
#	SM_MODULE_HEADERS	: (unused)
#	
#	SM_MODULE_INCLUDES	: include pathes for compiling the module
#	SM_MODULE_COMPILE_FLAGS : module specific compile flags
#	SM_MODULE_LINK_FLAGS    : module link flags
#	SM_MODULE_LIB_PATH	: the search path of libs the module links to
#	SM_MODULE_LIBS		: libs (-l switches) the module links to

ifeq ($(SM_MODULE_NAME),)
  $(info smart: ************************************************************)
  $(info smart:  You have to specify 'SM_MODULE_NAME'.)
  $(info smart: ************************************************************)
  $(error "SM_MODULE_NAME unknown")
endif

#d := $(wildcard $(SM_MODULE_SOURCES))
d := $(strip $(SM_MODULE_SOURCES))
ifeq ($d,)
  $(error "Nothing to build, no sources specified.")
endif

ifneq ($(SM_MODULE_TYPE),static)
 ifneq ($(SM_MODULE_TYPE),dynamic)
  ifneq ($(SM_MODULE_TYPE),executable)
    $(info smart: ************************************************************)
    $(info smart:  You have to specify 'SM_MODULE_TYPE', it can be one of )
    $(info smart:  '$(SM_MODULE_TYPES_SUPPORTED)'.)
    $(info smart: ************************************************************)
    $(error "SM_MODULE_TYPE unknown: '$(SM_MODULE_TYPE)'.")
  endif
 endif
endif

#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
#LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

## set the default goal
DEFAULT_GOAL := $(SM_OUT_DIR)/$(SM_MODULE_NAME)

## Compile log command.
log = $(if $(SM_COMPILE_LOG),echo $1 >> $(SM_OUT_DIR)/$(SM_COMPILE_LOG),true)

## Compute lib path and libs for (-L and -l switches).
SM_LIBS := 
SM_LIB_PATH :=
append_lib_path = $(eval SM_LIB_PATH += -L$$(patsubst -L%,%,$$1))
append_lib = $(eval SM_LIBS += -l$$(patsubst -l%,%,$$1))
$(foreach v,$(SM_MODULE_LIB_PATH),$(call append_lib_path,$v))
$(foreach v,$(SM_MODULE_LIBS),$(call append_lib,$v))
append_lib_path :=
append_lib :=

## Compute the link flags.
SM_LINK_FLAGS.cpp := $(filter-out -shared,$(SM_MODULE_LINK_FLAGS))
ifneq ($(SM_MODULE_TYPE),static)
  ifeq ($(SM_MODULE_TYPE),dynamic)
    SM_LINK_FLAGS.cpp := -shared $(SM_LINK_FLAGS.cpp)
  endif
  SM_LINK_FLAGS.cpp += $(SM_LIB_PATH)
endif

## C++ link command
SM_LINK.cpp = $(CXX) $(SM_LINK_FLAGS.cpp)

## Archive command
SM_ARCHIVE = $(AR) crs

## Generate the module build rule.
ifeq ($(SM_MODULE_TYPE),static)
  link = $(SM_ARCHIVE) $$@ $$^
else
  link = $(SM_LINK.cpp) -o $$@ $$^ $(SM_LIBS)
endif
objs := $(SM_MODULE_SOURCES:%.cpp=$(SM_OUT_DIR)/%.o)
gen_module_cmd := @echo C++: $$@ && $(call log,$(link)) && $(link)
$(eval $(SM_OUT_DIR)/$(SM_MODULE_NAME): $(objs) ; $(gen_module_cmd))
gen_module_cmd :=
objs :=

## Compute include path (-I switches).
SM_INCLUDES :=
$(foreach v,$(SM_MODULE_INCLUDES),\
  $(eval SM_INCLUDES += -I$$(patsubst -I%,%,$$v)))

## Compute compile flags.
SM_COMPILE_FLAGS.cpp = $(SM_INCLUDES) $(SM_MODULE_COMPILE_FLAGS)

## The C++ compilation command.
SM_COMPILE.cpp = $(CXX) $(SM_COMPILE_FLAGS.cpp) -c

## Compile command.
compile = $(SM_COMPILE.cpp) -o $$@ $$^

#gen_compile_cmd = $(compile)
gen_compile_cmd = @echo "C++: $(SM_MODULE_NAME) <= $$^" \
  && $(call log,$(compile)) \
  && ( $(compile) || $(call log,"failed: $$^") )

#
gen_dep_cmd = @echo "mk: $$@" && \
  $(CXX) -MM -MT $$(@:%.d=%.o) -MF $$@ $$<

mk_out_dir = $(if $(wildcard $1),,$(info mkdir: $1)$(shell mkdir -p $1))

d := $(SM_OUT_DIR)
$(foreach v,$(SM_MODULE_SOURCES),$(call mk_out_dir,$d/$(dir $v)))

$(foreach v,$(SM_MODULE_SOURCES),\
  $(eval $(v:%.cpp=$d/%.o) : $(SM_MODULE_DIR)/$v ; $(gen_compile_cmd)))

$(foreach v,$(SM_MODULE_SOURCES),\
  $(eval $(v:%.cpp=$d/%.d) : $(SM_MODULE_DIR)/$v ; $(gen_dep_cmd)))

deps := $(SM_MODULE_SOURCES:%.cpp=$d/%.d)
include $(deps)

gen_compile_cmd :=
d :=

# SM_COMPILE_LOG :=
# SM_MODULE_TYPE :=
# SM_MODULE_NAME :=
# SM_MODULE_SOURCES :=
# SM_MODULE_HEADERS :=

