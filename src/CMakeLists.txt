add_library(libevs
    
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libevs PROPERTY CXX_STANDARD 20)
endif()

option(BUILD_DYNAMIC "Build a shared library instead of a static library." OFF)
if(BUILD_DYNAMIC)
    # This is only needed on windows build but define it anyway as it won't hurt
    # and OS type is checked in header anyway.
    target_compile_definitions(libevs PRIVATE EVSPACE_DLL)
endif()

# Differentiates need of dllexport vs dllimport in Windows DLL builds.
target_compile_definitions(libevs PRIVATE EVSPACE_BUILD)