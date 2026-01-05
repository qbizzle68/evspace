# User variables
CXX_STD := c++17
BUILD_SHARED := FALSE
EVSPACE_CONSTRUCTOR_THROW := TRUE

GXX = g++
CXXFLAGS_COMMON = -Wall -std=$(CXX_STD) -Iinclude
CXXFLAGS_RELEASE = $(CXXFLAGS_COMMON) -O3 -DNDEBUG
CXXFLAGS_DEBUG = $(CXXFLAGS_COMMON) -g -DDEBUG
CXXFLAGS_PROFILE = $(CXXFLAGS_COMMON) -O3 -pg

# Directories
BUILD_DIR = build
RELEASE_DIR = $(BUILD_DIR)/release
DEBUG_DIR = $(BUILD_DIR)/debug
PROFILE_DIR = $(BUILD_DIR)/profile

# Sources files
LIB_SOURCES = angles.cpp matrix.cpp rotation.cpp vector.cpp

# Object files
LIB_OBJ_RELEASE = $(LIB_SOURCES:%.cpp=$(RELEASE_DIR)/%.o)
LIB_OBJ_DEBUG = $(LIB_SOURCES:%.cpp=$(DEBUG_DIR)/%.o)
LIB_OBJ_PROFILE = $(LIB_SOURCES:%.cpp=$(PROFILE_DIR)/%.o)

# Targets
RELEASE_LIB = $(RELEASE_DIR)/libevspace.a
DEBUG_LIB = $(DEBUG_DIR)/libevspace.a
PROFILE_LIB = $(PROFILE_DIR)/libevspace.a

.PHONY: all release debug profile clean help

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

$(RELEASE_DIR) $(DEBUG_DIR) $(PROFILE_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

help:
	echo "Make help statement"
