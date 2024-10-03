option(BUILD_DYNAMIC "Build a shared library instead of a static library." OFF)
if(BUILD_DYNAMIC)
    # This is only needed on windows build but define it anyway as it won't hurt
    # and OS type is checked in header anyway.
    set(BUILD_TYPE SHARED)
else()
    set(BUILD_TYPE STATIC)
endif()

add_library(libevs ${BUILD_TYPE}
    "angles.cpp"
    "vector.cpp"
    "matrix.cpp"
    # set a variable for the include directory in the upper level
    #"../include/rotation.hpp"
    "rotation.cpp"
)

if(BUILD_DYNAMIC)
    target_compile_definitions(libevs PRIVATE EVSPACE_DLL)
    # Differentiates need of dllexport vs dllimport in Windows DLL builds.
    target_compile_definitions(libevs PRIVATE EVSPACE_BUILD)
endif()
 
# todo: why doesn't this work here?
#include_directories(${evspace_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libevs PROPERTY CXX_STANDARD 20)
endif()
