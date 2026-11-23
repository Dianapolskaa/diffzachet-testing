add_library(mylib STATIC
    src/file.cpp
    include/mylib/file.h
)
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
