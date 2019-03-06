
project(dpa)
set(SOURCE_FILES dpa.cpp)

add_executable(dpa ${SOURCE_FILES})

add_subdirectory(module)
add_subdirectory(vos)
target_link_libraries(dpa vos mm cpu inter net proto)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
