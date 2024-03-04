cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(key_finder CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(INCLUDE_DIR include)
set(SOURCE_DIR src)

set(includes
        ${INCLUDE_DIR}/set_intersection.hpp
        ${INCLUDE_DIR}/FileInputStream.h
        ${INCLUDE_DIR}/argparse/argparse.hpp
        ${MOD_MATH_LIB_DIR}/include/mod_math_lib.h)

set(sources
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/FileInputStream.cpp)

add_executable(key_finder ${sources} ${includes})

target_include_directories(key_finder PRIVATE ${MOD_MATH_LIB_DIR}/include)
target_include_directories(key_finder PRIVATE ${INCLUDE_DIR})

target_link_libraries(key_finder PRIVATE mod_math_lib)

set_target_properties(key_finder PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)
