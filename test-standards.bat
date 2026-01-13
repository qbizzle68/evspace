@echo off
setlocal ENABLEDELAYEDEXPANSION

set BUILD_DIR=build

rem ===============================
rem C++17
rem ===============================
echo Building tests for C++17
rmdir /S /Q %BUILD_DIR% >nul 2>&1

cmake -S . -B %BUILD_DIR% -DCMAKE_CXX_STANDARD=17
if errorlevel 1 (
    echo CMake configure failed for C++17
    set RESULT_CXX17=1
) else (
    cmake --build %BUILD_DIR%
    if errorlevel 1 (
        echo Build failed for C++17
        set RESULT_CXX17=1
    ) else (
        ctest --test-dir %BUILD_DIR% --output-on-failure
        set RESULT_CXX17=!errorlevel!
    )
)

rem ===============================
rem C++20
rem ===============================
echo Building tests for C++20
rmdir /S /Q %BUILD_DIR% >nul 2>&1

cmake -S . -B %BUILD_DIR% -DCMAKE_CXX_STANDARD=20
if errorlevel 1 (
    echo CMake configure failed for C++20
    set RESULT_CXX20=1
) else (
    cmake --build %BUILD_DIR%
    if errorlevel 1 (
        echo Build failed for C++20
        set RESULT_CXX20=1
    ) else (
        ctest --test-dir %BUILD_DIR% --output-on-failure
        set RESULT_CXX20=!errorlevel!
    )
)

rem ===============================
rem C++23
rem ===============================
echo Building tests for C++23
rmdir /S /Q %BUILD_DIR% >nul 2>&1

cmake -S . -B %BUILD_DIR% -DCMAKE_CXX_STANDARD=23
if errorlevel 1 (
    echo CMake configure failed for C++23
    set RESULT_CXX23=1
) else (
    cmake --build %BUILD_DIR%
    if errorlevel 1 (
        echo Build failed for C++23
        set RESULT_CXX23=1
    ) else (
        ctest --test-dir %BUILD_DIR% --output-on-failure
        set RESULT_CXX23=!errorlevel!
    )
)

rem ===============================
rem Summary
rem ===============================
if not "%RESULT_CXX17%"=="0" (
    echo Error in C++17 configuration
    goto :fail
)
if not "%RESULT_CXX20%"=="0" (
    echo Error in C++20 configuration
    goto :fail
)
if not "%RESULT_CXX23%"=="0" (
    echo Error in C++23 configuration
    goto :fail
)

echo All configurations succeeded
exit /B 0

:fail
echo Error in one or more configurations
exit /B 1
