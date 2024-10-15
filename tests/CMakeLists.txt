option(SKIP_GTEST_SEARCH "Do not search for GTest package and download from source" OFF)
# Set the version of googletest if fetching. Use -DGTEST_GIT_TAG="vX.X.X"
set(GTEST_GIT_TAG "v1.15.2" CACHE STRING "Set the git tag for the googletest version when downloading from source")

if(NOT SKIP_GTEST_SEARCH)
    message(STATUS "Searching for GTest package")
    find_package(GTest)
    set(NEED_GTEST NOT ${GTest_FOUND})
else()
    message(STATUS "Skip search for GTest package")
    set(NEED_GTEST true)
endif()

if(${NEED_GTEST})
    message(STATUS "Fetching googletest ($CACHE{GTEST_GIT_TAG}) from source")
    include(FetchContent)
    FetchContent_Declare(
      googletest
      GIT_REPOSITORY    https://github.com/google/googletest.git
      GIT_TAG           $CACHE{GTEST_GIT_TAG}
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(evspace_unit_testing
    "angles_unit_test.cpp"
    "vector_unit_test.cpp"
    "matrix_unit_test.cpp"
    "rotation_unit_test.cpp"
    "reference_frame_unit_test.cpp"
)

target_include_directories(evspace_unit_testing PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${evspace_library_SOURCE_DIR}/include"
)

if(BUILD_SHARED)
    target_compile_definitions(evspace_unit_testing PRIVATE EVSPACE_SHARED_LIB)

    # this solves the nightmare of test executable unable to link with the evspace dll on windows
    if (WIN32)
        add_custom_command(
            TARGET evspace_unit_testing POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:evspace_unit_testing> $<TARGET_FILE_DIR:evspace_unit_testing>
            COMMAND_EXPAND_LISTS
        )
    endif ()
endif()

target_link_libraries(evspace_unit_testing
    GTest::gtest_main
    evspace
)

include(GoogleTest)
gtest_discover_tests(evspace_unit_testing)

target_precompile_headers(evspace_unit_testing PRIVATE
    <input_pch.hpp>
    <cmath>
)
