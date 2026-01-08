#!/bin/bash

make clean > /dev/null
if [[ $? -ne 0 ]]; then
    echo "Error cleaning build directory, exiting"
fi

echo 'Building tests for C++17'
make test CXX_STD=c++17
RESULT_CXX17="$?"

make clean > /dev/null
if [[ $? -ne 0 ]]; then
    echo "Error cleaning build directory, exiting"
fi

echo 'Building tests for c++20'
make test CXX_STD=c++20
RESULT_CXX20="$?"

make clean > /dev/null
if [[ $? -ne 0 ]]; then
    echo "Error cleaning build directory, exiting"
fi

echo 'Building tests for c++23'
make test CXX_STD=c++23
RESULT_CXX23="$?"

if [[ "$RESULT_CXX17" -ne "0" ]] || [[ "$RESULT_CXX20" -ne "0" ]] || [[ "$RESULT_CXX23" -ne "0" ]]; then
    echo 'Error in one or more configurations'
else
    echo 'All configurations succeeded'
fi