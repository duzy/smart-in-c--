
include Makefile.conf

INCLUDES = -I$(BOOST_DIR)

CXXFLAGS = -std=gnu++0x $(INCLUDES)

#LOADLIBRES = -L$(BOOST_DIR)/stage/lib
LOADLIBRES =
LDLIBS = 
##################################################

V = debug
OUT_DIR = out/$(V)

SOURCES = $(wildcard src/*.cpp)
OBJECT_PAT = $(OUT_DIR)/objs/%.o
OBJECTS = $(SOURCES:%.cpp=$(OBJECT_PAT))
DEPEND_PAT = $(OUT_DIR)/deps/%.d
DEPENDS = $(SOURCES:%.cpp=$(DEPEND_PAT))
UNITS = $(wildcard t/*.t)
UNIT_PAT = $(OUT_DIR)/%.test
TESTS = $(UNITS:%.t=$(UNIT_PAT))

##################################################
PREPARE_OUTPUT_DIR = @[ -d `dirname $@` ] || mkdir -pv `dirname $@`

##################################################

TARGET = smart

PHONY = all
all: $(TARGET)

PHONY += test
test: $(TESTS)
	@for T in $(TESTS); do $$T; done

$(TARGET):$(OBJECTS)
	$(PREPARE_OUTPUT_DIR)
	$(LINK.cc) -o $@ $^ $(LOADLIBRES) $(LDLIBS)
$(OBJECTS):$(OBJECT_PAT):%.cpp
	$(PREPARE_OUTPUT_DIR)
	$(COMPILE.cc) -o $@ $<
$(DEPENDS):$(DEPEND_PAT):%.cpp
	$(PREPARE_OUTPUT_DIR)
	$(CXX) -MM -MT $(OUT_DIR)/objs/$*.o -MF $@ $<
$(TESTS):$(UNIT_PAT):%.t
	$(PREPARE_OUTPUT_DIR)
	$(LINK.cc) -x c++ -o $@ $^

include $(DEPENDS)