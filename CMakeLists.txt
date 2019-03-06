cmake_minimum_required(VERSION 3.5)
project(carcoder)

# include directories
include_directories(
        ${PROJECT_SOURCE_DIR}/include/module
        ${PROJECT_SOURCE_DIR}/include/vos
        /usr/local/include
        /usr/include
)
add_subdirectory(src)