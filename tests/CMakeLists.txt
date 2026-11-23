find_package(Qt6 REQUIRED COMPONENTS Test)
set(CMAKE_AUTOMOC ON)

add_executable(mylib_tests test_file.cpp)
target_link_libraries(mylib_tests PRIVATE mylib Qt6::Test)
add_test(NAME mylib_tests COMMAND mylib_tests)
