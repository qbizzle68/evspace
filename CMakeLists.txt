cmake_minimum_required (VERSION 3.23)

project ("evspace_library")
include(CTest)

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

option(NOTHROW_CONSTRUCTOR "Ensure allocating data buffers to not throw on eror." OFF)

add_subdirectory(tests)
