project(carcoder)
#cmake_minimum_required(VERSION 3.5)


set(SOURCE_FILES                                  #设置变量，表示所有的源文件
        vos_memory.cpp
        vos_main.cpp
        vos_cfg.cpp
        vos_log.cpp
        vos_api.cpp
        )

#include_directories(
#        ${PROJECT_SOURCE_DIR}/../../include/vos
#)

message("project path: ${PROJECT_SOURCE_DIR}")
add_library(vos SHARED ${SOURCE_FILES})         #生成动态库
add_library(vos_static STATIC ${SOURCE_FILES})  #生成静态库

set_target_properties(vos_static PROPERTIES OUTPUT_NAME "vos")
set_target_properties(vos PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(vos_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)

