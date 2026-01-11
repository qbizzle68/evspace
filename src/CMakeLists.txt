if(BUILD_SHARED)
    # This is only needed on windows build but define it anyway as it won't hurt
    # and OS type is checked in header anyway.
    set(BUILD_TYPE SHARED)
    message(STATUS "Building shared library")
else()
    set(BUILD_TYPE STATIC)
endif()

add_library(evspace ${BUILD_TYPE}
    "angles.cpp"
    "rotation.cpp"
)

set_target_properties(evspace PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${EVSPACE_LIB_DIR})
set_target_properties(evspace PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${EVSPACE_LIB_DIR})

if(BUILD_SHARED)
    target_compile_definitions(evspace PRIVATE EVSPACE_SHARED_LIB)
    # Differentiates need of dllexport vs dllimport in Windows DLL builds.
    target_compile_definitions(evspace PRIVATE EVSPACE_BUILD)
endif()

if(NOTHROW_CONSTRUCTOR)
    target_compile_definitions(evspace PRIVATE EVSPACE_CONSTRUCTOR_NOTHROW)
endif(NOTHROW_CONSTRUCTOR)
 
target_include_directories(evspace PUBLIC ${evspace_library_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET evspace PROPERTY CXX_STANDARD 17)
endif()
