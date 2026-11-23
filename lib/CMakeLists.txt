add_library(mylib STATIC
    src/file.cpp
    include/file.h
)

target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
