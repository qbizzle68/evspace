# CMakeList.txt : CMake project for evspace, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("evspace")

# Add source to this project's executable.
include_directories(${evspace_SOURCE_DIR}/include)
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
