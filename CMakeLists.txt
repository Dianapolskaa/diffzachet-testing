cmake_minimum_required(VERSION 3.16)
project(variantNN CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()                 # лучше здесь, а не в tests/
add_subdirectory(lib)
add_subdirectory(tests)
