
include Makefile.conf

INCLUDES = -I$(BOOST_DIR)

CXXFLAGS = -std=gnu++0x $(INCLUDES)
#CXXFLAGS = $(INCLUDES)

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
UNIT_PAT = $(OUT_DIR)/objs/%.o
UNIT_OBJECTS = $(UNITS:%.t=$(UNIT_PAT))
TEST_PAT = $(OUT_DIR)/%.test
TESTS = $(UNITS:%.t=$(TEST_PAT))
TEST_DEPEND_PAT = $(OUT_DIR)/deps/%.d
TEST_DEPENDS = $(UNITS:%.t=$(TEST_DEPEND_PAT))

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
$(UNIT_OBJECTS):$(UNIT_PAT):%.t
	$(PREPARE_OUTPUT_DIR)
	$(COMPILE.cc) -xc++ -o $@ $<
$(TESTS):$(TEST_PAT):$(OUT_DIR)/objs/%.o
	$(PREPARE_OUTPUT_DIR)
	$(LINK.cc) -o $@ $^
$(TEST_DEPENDS):$(TEST_DEPEND_PAT):%.t
	$(PREPARE_OUTPUT_DIR)
	$(CXX) -xc++ -MM -MT $(OUT_DIR)/objs/$*.o -MF $@ $<

include $(DEPENDS)
include $(TEST_DEPENDS)
