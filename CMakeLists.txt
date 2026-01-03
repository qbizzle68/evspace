cmake_minimum_required (VERSION 3.23)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("evspace_library")

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(EVSPACE_LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

option(BUILD_SHARED "Build a shared library instead of a static library." OFF)
option(NOTHROW_CONSTRUCTOR "Ensure allocating data buffers to not throw on eror." OFF)

# Add source to this project's executable.
add_subdirectory(src)

# TODO: Add tests and install targets if needed.
option(SKIP_TESTING "Skip executing/building resources for all library tests" OFF)

if(NOT SKIP_TESTING)
    message(STATUS "Buliding with tests")
    # this has to be here or else it doesn't configure testing
    enable_testing()
    add_subdirectory(tests)
else()
    message(STATUS "Building without tests")
endif()
unset(SKIP_TESTING CACHE)
