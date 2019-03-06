project(carcoder)
#cmake_minimum_required(VERSION 3.5)


set(SOURCE_FILES                                  #设置变量，表示所有的源文件
        process.cpp
        )

#include_directories(
#        ${PROJECT_SOURCE_DIR}/../../include/modem
#)

#message("project path: ${PROJECT_SOURCE_DIR}")
add_library(inter SHARED ${SOURCE_FILES})         #生成动态库
add_library(inter_static STATIC ${SOURCE_FILES})  #生成静态库

set_target_properties(inter_static PROPERTIES OUTPUT_NAME "inter")
set_target_properties(inter PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(inter_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../../lib)