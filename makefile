# User variables
CXX_STD := c++17

$(info Compiling with -std=$(CXX_STD))
CXX = g++
CXXFLAGS = -g -DDEBUG -MD -MP -std=$(CXX_STD) -Wall -Wextra -pedantic -Iinclude -Iexternal
ifdef EVSPACE_CONSTRUCTOR_NOTHROW
CXXFLAGS += -DEVSPACE_CONSTRUCTOR_NOTHROW
endif
GTEST_FLAGS = $(shell pkg-config --cflags gtest_main)
GTEST_LIBS = $(shell pkg-config --libs gtest_main)

# Directories
BUILD_DIR = build
TEST_DIR = $(BUILD_DIR)/test
TEST_SRC_DIR = tests
CXXFLAGS += -I$(TEST_SRC_DIR)

# Sources
TEST_SOURCES := $(wildcard $(TEST_SRC_DIR)/*.cpp)

# Object files
TEST_OBJ = $(TEST_SOURCES:$(TEST_SRC_DIR)%.cpp=$(TEST_DIR)%.o)

# Targets
TEST_BIN = $(TEST_DIR)/run_tests

-include $(TEST_OBJ:.o=.d)

.PHONY: all test clean

all: test

# Test build
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) | $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) $^ $(GTEST_LIBS) -o $@

$(TEST_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp | $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) -c $< -o $@

$(TEST_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo 'make [CXX_STD=c++17] [EVSPACE_CONSTRUCTOR_NOTHROW=] [{test|clean|help}]'
