# User variables
CXX_STD := c++17
# Don't define these unless they should be defined for building lib
# BUILD_SHARED := FALSE
# EVSPACE_CONSTRUCTOR_THROW := TRUE

$(info Compiling with -std=$(CXX_STD))
GXX = g++
CXXFLAGS_COMMON = -Wall -std=$(CXX_STD) -Iinclude
ifdef BUILD_SHARED
CXXFLAGS_COMMON += -DBUILD_SHARED
endif
ifdef EVSPACE_CONSTRUCTOR_NOTHROW
CXXFLAGS_COMMON += -DEVSPACE_CONSTRUCTOR_NOTHROW
endif
CXXFLAGS_RELEASE = $(CXXFLAGS_COMMON) -O3 -march=native -DNDEBUG
CXXFLAGS_DEBUG = $(CXXFLAGS_COMMON) -g -DDEBUG
CXXFLAGS_PROFILE = $(CXXFLAGS_COMMON) -O3 -march=native -pg
CXXFLAGS_TEST = $(CXXFLAGS_DEBUG)
GTEST_FLAGS = $(shell pkg-config --cflags gtest_main)
GTEST_LIBS = $(shell pkg-config --libs gtest_main)

# Directories
BUILD_DIR = build
RELEASE_DIR = $(BUILD_DIR)/release
DEBUG_DIR = $(BUILD_DIR)/debug
PROFILE_DIR = $(BUILD_DIR)/profile
TEST_DIR = $(BUILD_DIR)/test
TEST_SRC_DIR = tests

# Sources files
LIB_SOURCES = angles.cpp rotation.cpp
LIB_HEADERS := $(wildcard include/*.hpp)
TEST_SOURCES = vector_unit_test.cpp matrix_unit_test.cpp

# Object files
LIB_OBJ_RELEASE = $(LIB_SOURCES:%.cpp=$(RELEASE_DIR)/%.o)
LIB_OBJ_DEBUG = $(LIB_SOURCES:%.cpp=$(DEBUG_DIR)/%.o)
LIB_OBJ_PROFILE = $(LIB_SOURCES:%.cpp=$(PROFILE_DIR)/%.o)
TEST_OBJ = $(TEST_SOURCES:%.cpp=$(TEST_DIR)/%.o)

# Targets
RELEASE_LIB = $(RELEASE_DIR)/libevspace.a
DEBUG_LIB = $(DEBUG_DIR)/libevspace.a
PROFILE_LIB = $(PROFILE_DIR)/libevspace.a
TEST_BIN = $(TEST_DIR)/run_tests

.PHONY: all release debug profile test clean help

all: release

release: $(RELEASE_LIB)

$(RELEASE_LIB): $(LIB_OBJ_RELEASE)
	ar rcs $@ $^

$(RELEASE_DIR)/%.o: src/%.cpp | $(RELEASE_DIR)
	$(CXX) $(CXXFLAGS_RELEASE) -c $< -o $@

# Debug build
debug: $(DEBUG_LIB)

$(DEBUG_LIB): $(LIB_OBJ_DEBUG)
	ar rcs $@ $^

$(DEBUG_DIR)/%.o: src/%.cpp | $(DEBUG_DIR)
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

# Profile build
profile: $(PROFILE_LIB)

$(PROFILE_LIB): $(LIB_OBJ_PROFILE)
	ar rcs $@ $^

$(PROFILE_DIR)/%.o: src/%.cpp | $(PROFILE_DIR)
	$(CXX) $(CXXFLAGS_PROFILE) -c $< -o $@

# Test build
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) $(LIB_HEADERS) | $(TEST_DIR) $(DEBUG_LIB)
	$(CXX) $(CXXFLAGS_TEST) $(GTEST_FLAGS) $^ $(GTEST_LIBS) -Iinclude -L$(DEBUG_DIR) -levspace -o $@

$(TEST_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp | $(TEST_DIR)
	$(CXX) $(CXXFLAGS_TEST) $(GTEST_FLAGS) -I$(TEST_SRC_DIR) -Iinclude -c $< -o $@

$(RELEASE_DIR) $(DEBUG_DIR) $(PROFILE_DIR) $(TEST_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

help:
	echo "Make help statement"
